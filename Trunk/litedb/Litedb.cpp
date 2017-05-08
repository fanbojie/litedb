#include "Litedb.h"
#include "ConnectionPool.h"
#include "SqlTask.h"

LITEDB_API int litedb_init( const char* connStr, int size )
{
    litedb::CConnectionPool::getInstance().init(size);
    return litedb::CConnectionPool::getInstance().open(connStr);
}

LITEDB_API litedb::CSqlTask* litedb_create_task( int type )
{
    return litedb::CConnectionPool::getInstance().createTask(type);
}

LITEDB_API void litedb_push_task( litedb::CSqlTask* task )
{
    litedb::CConnectionPool::getInstance().pushTask(task);
}

LITEDB_API void litedb_uninit()
{
    litedb::CConnectionPool::getInstance().close();
}
