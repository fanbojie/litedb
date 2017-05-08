#include "HeartBeatWorker.h"
#include "ConnectionPool.h"

litedb::CHeartBeatWorker::CHeartBeatWorker(litedb::CConnectionPool* pool)
: m_pool(pool)
{

}

litedb::CHeartBeatWorker::~CHeartBeatWorker()
{

}

void litedb::CHeartBeatWorker::run()
{
    m_running = true;
    while(!m_stopFlag)
    {
        // ´ý²âÊÔ£¬Ã¿¸ô30·ÖÖÓ£¬´¥·¢ÐÄÌø
        sleep(1800);
        if (m_pool != NULL)
        {
            m_pool->keepAlive();
        }
    }
    m_running = false;
}
