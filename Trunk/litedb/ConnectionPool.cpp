#include "ConnectionPool.h"
#include <stdio.h>
#include <limits.h>
#include "litebase/ScopeLock.h"
#include "litebase/Trace.h"
#include "MysqlFactory.h"
#include "MysqlError.h"
#include "BaseDefine.h"
#include "Connection.h"
#include "SqlTask.h"
#include "DatabaseRequest.h"
#include "HeartBeatWorker.h"


using namespace std;
using namespace litedb;
using namespace litebase::details;

litedb::CConnectionPool::CConnectionPool()
: m_poolSize(0)
, m_taskId(0)
, m_factory(NULL)
, m_pingWorker(NULL)
{
    for (int i=0; i<TYPE_MAX; i++)
    {
        m_connections[i] = NULL;
    }
}

litedb::CConnectionPool::~CConnectionPool()
{
    close();
}

void litedb::CConnectionPool::init( int size )
{
	if (size < 5 || size > 100)
	{
		m_poolSize = 5;
	}
	else
	{
		m_poolSize = size;
	}

	for (int i=0; i<TYPE_MAX; i++)
	{
		m_connections[i] = new vector<CConnection*>();
	}
}

int litedb::CConnectionPool::open( const std::string& connStr )
{
    LogConfig   config;
    config.fileCounts = 20;
    config.fileSize = 10;
    config.level = LOG_INFO;
    config.outputType = 3;
    config.saveDir = "DbLog";

    int logInit = TRACE_INIT("litedb", config);
    if (logInit != 0)
    {
        printf("init log failed.\n");
        goto CLOSE;
    }

    TRACE_INFO("start to open connection pool(%s).", connStr.c_str());

	m_connectionInfo = CConnectionInfo(connStr);
	
	if (initFactory() != 0)
	{
        TRACE_ERR(0, "create factory failed, type=%d.", m_connectionInfo.m_type);
		goto CLOSE;
	}

    TRACE_INFO("init pool, size=%d type=%d host=%s port=%s user=%s pwd=%s database=%s.",
        m_poolSize, m_connectionInfo.m_type, m_connectionInfo.m_host.c_str(), 
        m_connectionInfo.m_port.c_str(), m_connectionInfo.m_user.c_str(), 
        m_connectionInfo.m_password.c_str(), m_connectionInfo.m_database.c_str());

	try
	{
		// 初始化连接池
		for (int i=0; i<m_poolSize; i++)
		{
			CConnection* pSynConn = m_factory->createConnection();
            if (pSynConn != NULL)
            {
                pSynConn->init(m_connectionInfo);
                pSynConn->open();
                m_connections[0]->push_back(pSynConn);
            }
            else
            {
                TRACE_ERR(0, "create sync connection failed.");
                goto CLOSE;
            }

			CConnection* pAsynConn = m_factory->createConnection();
            if (pAsynConn != NULL)
            {
                pAsynConn->init(m_connectionInfo, &m_taskQueue, &m_condition);
                pAsynConn->open();	
                m_connections[1]->push_back(pAsynConn);
            }
            else
            {
                TRACE_ERR(0, "create async connection failed.");
                goto CLOSE;
            }
		}
	}
	catch (CMysqlError const &e)
	{
        TRACE_ERR(0, "open connection failed, mysql error, errno=%d err=%s.", e.m_errNum, e.what());
		goto CLOSE;
	}
    catch (CLiteDBError const &e)
    {
        TRACE_ERR(0, "open connection failed, litedb error, err=%s.", e.what());
        goto CLOSE;
    }
	catch (...)
	{
        TRACE_ERR(0, "other error.");
		goto CLOSE;
	}
	
    // 起一个单独线程定时做keepAlive
    m_pingWorker = new CHeartBeatWorker(this);
    m_pingWorker->start();

    TRACE_INFO("open connection pool success.");
    return 0;

CLOSE:
	close();
	return -1;
}

void litedb::CConnectionPool::close()
{
    {
        CScopeLock lock(m_condition.getMutex());
        while(!m_taskQueue.empty())
        {
            CSqlTask* pTask = m_taskQueue.front();
            delete pTask;
            m_taskQueue.pop();
        }
    }

    if (m_pingWorker != NULL)
    {
        m_pingWorker->stop();
//         delete m_pingWorker;
//         m_pingWorker = NULL;
    }

    // 要注意关闭时是否还有任务在执行，防止连接的多线程问题
	for (int i=0; i<TYPE_MAX; i++)
	{
        if (m_connections[i] == NULL)
        {
            continue;
        }

        TRACE_INFO("start to close connection pool.");

        unsigned int count = 0;
        while(1)
        {
            vector<CConnection*>::iterator iter = m_connections[i]->begin();
            for (; iter!=m_connections[i]->end();++iter)
            {
                // close之后不释放lock，防止任务执行
                if (!(*iter)->isClose() && (*iter)->tryLock() == 0)
                {
                    count++;
                    (*iter)->close();
                }
            }

            if (count == m_connections[i]->size())
            {
                TRACE_INFO("connection(%d) has all close.", i);
                break;
            }
        }
//         m_connections[i]->clear();
// 		delete m_connections[i];
//         m_connections[i] = NULL;
	}

    while(1)
    {
        if (m_connections[TYPE_ASYNC] == NULL)
        {
            break;
        }

        int count = 0;
        vector<CConnection*>::iterator iter = m_connections[TYPE_ASYNC]->begin();
        for (; iter!=m_connections[TYPE_ASYNC]->end();++iter)
        {
            // 保证异步连接的工作线程退出
            if ((*iter)->isWork())
            {
                count++;
                CScopeLock lock(m_condition.getMutex());
                m_condition.notifyAll();
            }
        }

        if (count == 0)
        {
            TRACE_INFO("async connect work thread all stop.");
            break;
        }
    }

    for (int i=0; i<TYPE_MAX; i++)
    {
        m_connections[i] = NULL;
    }

    delete m_factory;
    m_factory = NULL;
}

litedb::CConnection* litedb::CConnectionPool::getConnection()
{
	// 获取空闲的同步连接
    if (m_connections[0] != NULL)
    {
        TRACE_INFO("begin");
        int i = 0;
        while(1)
        {
            i++;
            // 直到获取空闲连接，TODO 是否有问题
            vector<CConnection*>::iterator iter = m_connections[0]->begin();
            for (; iter!=m_connections[0]->end(); ++iter)
            {
                if ((*iter)->tryLock() == 0)
                {
                    TRACE_INFO("try times=%d.", i);
                    TRACE_INFO("end.");
                    return (*iter);
                }
            }
        }
    }

	return NULL;
}

void litedb::CConnectionPool::pushTask( litedb::CSqlTask* task )
{
	CScopeLock lock(m_condition.getMutex());
	m_taskQueue.push(task);
	m_condition.notifyAll();
}

litedb::CSqlTask* litedb::CConnectionPool::createTask(int type)
{
    if (type != TASK_TYPE::TYPE_SYNC && type!= TASK_TYPE::TYPE_ASYNC)
    {
        TRACE_ERR(0, "error task type=%d", type);
        return NULL;
    }

	CSqlTask* pTask = m_factory->createTask();
    if (pTask != NULL)
    {
        pTask->init(type, generateTaskId(), this);
    }
    else
    {
        TRACE_ERR(0, "create task failed, type=%d.", type);
    }

    return pTask;
}

int litedb::CConnectionPool::initFactory()
{
	switch(m_connectionInfo.m_type)
	{
		case DB_TYPE::TYPE_MYSQL:
		{
			m_factory = new CMysqlFactory;
			break;
		}
		case DB_TYPE::TYPE_SQLITE3:
		{
			break;
		}
		case DB_TYPE::TYPE_ORACLE:
		{
			break;
		}
		case DB_TYPE::TYPE_ODBC:
		{
			break;
		}
		case DB_TYPE::TYPE_POSTGRESQL:
		{
			break;
		}
		case DB_TYPE::TYPE_DB2:
		{
			break;
		}
		default:
		{
			break;
		}
	}

    return (m_factory != NULL ? 0 : -1);
}

void litedb::CConnectionPool::keepAlive()
{
    // 同步连接心跳
    if (m_connections[0] == NULL 
        || m_connections[1] == NULL)
    {
        TRACE_WARNING("connections has closed.");
        return;
    }

    vector<CConnection*>::iterator iter = m_connections[0]->begin();
    for (; iter!=m_connections[0]->end(); ++iter)
    {
        if ((*iter)->tryLock() == 0)
        {
            CDatabaseRequest* pRequest = m_factory->createRequest(REQ_TYPE::TYPE_PING);
            pRequest->setHandle((*iter)->getHandle());
            pRequest->execute();
            delete pRequest;
            pRequest = NULL;
            (*iter)->unlock();
        }
    }

    // 异步连接心跳
    iter = m_connections[1]->begin();
    for (; iter!=m_connections[1]->end(); ++iter)
    {
        CDatabaseRequest* pRequest = m_factory->createRequest(REQ_TYPE::TYPE_PING);
        CSqlTask* pTask = m_factory->createTask();
        pTask->setRequest(pRequest);
        pTask->init(TASK_TYPE::TYPE_ASYNC, 0, this);
        pushTask(pTask);
    }
}

int litedb::CConnectionPool::generateTaskId()
{
    CScopeLock  lock(m_idMutex);
    if (m_taskId > INT_MAX)
    {
        m_taskId = 0;
    }

    return ++m_taskId;
}
