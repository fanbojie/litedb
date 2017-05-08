#include "MysqlPingRequest.h"
#include "mysql.h"

using namespace std;
using namespace litedb;

litedb::CMysqlPingRequest::CMysqlPingRequest()
{
}

litedb::CMysqlPingRequest::~CMysqlPingRequest()
{
}

CResultSet* litedb::CMysqlPingRequest::execute()
{
    MYSQL* mysql = static_cast<MYSQL*>(m_handle);
    if (mysql != NULL)
    {
        mysql_ping(mysql);
    }
    return NULL;
}
