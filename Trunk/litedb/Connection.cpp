#include "Connection.h"
#include "litebase/Trace.h"
#include "ConnectionWorker.h"

using namespace std;
using namespace litebase::details;

litedb::CConnection::CConnection()
: m_isClose(false)
, m_worker(NULL)
{
}

litedb::CConnection::~CConnection()
{
    delete m_worker;
    m_worker = NULL;
}

void litedb::CConnection::init( const litedb::CConnectionInfo& connInfo )
{
	m_connectionInfo = connInfo;
}

void litedb::CConnection::init( const litedb::CConnectionInfo& connInfo, 
							    queue<litedb::CSqlTask*>* taskQueue, 
							   litebase::details::CConVariable* condition )
{
	m_connectionInfo = connInfo;
	m_worker = new CConnectionWorker(this, taskQueue, condition);
    if (m_worker != NULL)
    {
        m_worker->start();
    }
    else
    {
        TRACE_ERR(0, "create connection worker failed.");
    }
}

bool litedb::CConnection::isWork()
{
    if (m_worker != NULL)
    {
        return m_worker->isRunning();
    }

    return false;
}
