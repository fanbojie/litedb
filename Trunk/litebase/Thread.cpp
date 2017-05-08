#include "Thread.h"
#include <stdio.h>

litebase::details::CThread::CThread()
: m_stopFlag(false)
, m_running(false)
, m_tid(0)
{
}

litebase::details::CThread::~CThread()
{
}

void litebase::details::CThread::start()
{
#ifdef WIN32
    _beginthreadex(NULL, 0, &threadProc, (void*)this, 0, &m_tid);
#else
    pthread_create(&m_tid, NULL, &threadProc, (void*)this);
#endif
}

void litebase::details::CThread::stop()
{
    m_stopFlag = true;
}

void litebase::details::CThread::resume()
{
}

THREADPROC_RET litebase::details::CThread::threadProc( void *arg )
{
    litebase::details::CThread* pThread = (litebase::details::CThread*)(arg);
    pThread->run();
    return 0;
}
