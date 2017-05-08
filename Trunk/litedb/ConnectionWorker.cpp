#include "ConnectionWorker.h"
#include "litebase/ScopeLock.h"
#include "litebase/ConditionVariable.h"
#include "Connection.h"
#include "SqlTask.h"

using namespace std;
using namespace litebase::details;

litedb::CConnectionWorker::CConnectionWorker(CConnection* conn, std::queue<litedb::CSqlTask*>* reqQueue,
                                             litebase::details::CConVariable* condition)
                                             : m_conn(conn)
                                             , m_queue(reqQueue)
                                             , m_conditionVar(condition)
{
}

litedb::CConnectionWorker::~CConnectionWorker()
{
}

void litedb::CConnectionWorker::run()
{
    m_running = true;
    CSqlTask* pTask = NULL;
    while(!m_stopFlag)
    {
        {
            CScopeLock lock(m_conditionVar->getMutex());
            while(m_queue->empty())
            {
                m_conditionVar->wait();
                // ֹͣʱ�˳��߳�
                if (m_stopFlag)
                {
                    m_running = false;
                    return;
                }
            }

            pTask = m_queue->front();
            m_queue->pop();
        }

        // �첽������ʵ����Ҫlock��������Ϊ�˷�ֹcloseʱ���߳�����
        if (m_conn->tryLock() == 0)
        {
            pTask->setConn(m_conn);
            pTask->call();
            pTask->release();
            m_conn->unlock();
        }
    }

    m_running = false;
}

