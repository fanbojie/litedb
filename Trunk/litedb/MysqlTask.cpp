#include "MysqlTask.h"
#include "errmsg.h"
#include "litebase/Trace.h"
#include "litebase/TimeMeasure.h"
#include "ConnectionPool.h"
#include "Connection.h"
#include "DatabaseRequest.h"
#include "MysqlPreparedRequest.h"
#include "MysqlRawRequest.h"
#include "ResultSet.h"
#include "Error.h"
#include "MysqlError.h"
#include "BaseDefine.h"

using namespace std;
using namespace litedb;

litedb::CMysqlTask::CMysqlTask()
{
}

litedb::CMysqlTask::~CMysqlTask()
{
}

void litedb::CMysqlTask::setCmdText( const std::string& cmd )
{
    size_t pos = cmd.find("?");
    if (pos != string::npos)
    {
        m_request = new CMysqlPreparedRequest();
    }
    else
    {
        m_request = new CMysqlRawRequest();
    }

    if (m_request != NULL)
    {
        m_request->setCmdText(cmd);
    }
}

int litedb::CMysqlTask::execute()
{
    CConnection* pConn = NULL;
    int retryCnt = 0;
    unsigned long cost = 0;

    litebase::details::CTimeMeasure execCost;
    if (m_request == NULL)
    {
        TRACE_ERR(0, "request has not create, taskId=%d.", m_taskId);
        return -1;
    }

    if (m_type == TASK_TYPE::TYPE_SYNC)
    {
        if (m_connPool != NULL)
        {
            pConn = m_connPool->getConnection();
            if (pConn == NULL)
            {
                TRACE_ERR(0, "no free connection, taskId=%d type=%d.", m_taskId, m_type);
                return -1;
            }
            else
            {
                m_conn = pConn;
                m_request->setHandle(m_conn->getHandle());
            }
        }
        else
        {
            TRACE_ERR(0, "connection pool is not init, taskId=%d type=%d.", 
                m_taskId, m_type);
            return -1;
        }
    }
    else
    {
        if (m_conn != NULL)
        {
            m_request->setHandle(m_conn->getHandle());
        }
        else
        {
            TRACE_ERR(0, "async connection is not set, taskId=%d type=%d.", 
                m_taskId, m_type);
            return -1;
        }
    }

    cost = execCost.getCostTime();
    if (cost>500)
    {
        TRACE_WARNING("taskId=%d cost=%d", m_taskId, cost);
    }

RETRY:
    try
    {
        m_response = m_request->execute();
    }
    catch (CMysqlError const &e)
    {
        TRACE_ERR(0, "mysql error, taskId=%d errno=%d err=%s.", m_taskId, e.m_errNum, e.what());
        //对于特定错误码，要进行重连
        if (retryCnt<=3 && handleError(e.m_errNum))
        {
            retryCnt++;
            goto RETRY;
        }
        else
        {
            goto ERR;
        }
    }
    catch (CLiteDBError const &e)
    {
        TRACE_ERR(0, "litedb error, taskId=%d err=%s.", m_taskId, e.what());
        goto ERR;    	
    }
    catch (...)
    {
        TRACE_ERR(0, "other error, taskId=%d.", m_taskId);
        goto ERR;
    }
    
    if (m_type == TASK_TYPE::TYPE_SYNC)
    {
        pConn->unlock();
    }

    cost = execCost.getCostTime();
    if (cost>500)
    {
        TRACE_WARNING("taskId=%d sql=%s cost=%d", 
            m_taskId, m_request->getCmdText().c_str(), cost);
    }

    return 0;

ERR:
    if (m_type == TASK_TYPE::TYPE_SYNC)
    {
        pConn->unlock();
    }

    return -1;
}

bool litedb::CMysqlTask::handleError( int err )
{
    switch(err)
    {
    case CR_SERVER_GONE_ERROR:
    case CR_SERVER_LOST:
    case CR_INVALID_CONN_HANDLE:
    case CR_SERVER_LOST_EXTENDED:
        {
            try
            {
                m_conn->close();
                m_conn->open();           
            }
            catch (CMysqlError const &err)
            {
                TRACE_ERR(0, "open connection failed, mysql error, taskId=%d errno=%d err=%s.", 
                    m_taskId, err.m_errNum, err.what());
                return false;
            }
            catch (CLiteDBError const &err)
            {
                TRACE_ERR(0, "open connection failed, litedb error, taskId=%d err=%s.", 
                    m_taskId, err.what());
                return false;
            }
            catch (...)
            {
                TRACE_ERR(0, "other error, taskId=%d.", m_taskId);
                return false;
            }
            
            m_request->setHandle(m_conn->getHandle());
            return true;
        }
    default:
        {
            return false;
        }
    }
}
