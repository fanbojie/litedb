#include "MysqlRawRequest.h"
#include "litebase/Trace.h"
#include "MysqlRawResultSet.h"
#include "Error.h"
#include "MysqlError.h"

using namespace std;
using namespace litedb;

litedb::CMysqlRawRequest::CMysqlRawRequest()
{
}

litedb::CMysqlRawRequest::~CMysqlRawRequest()
{
}

litedb::CResultSet* litedb::CMysqlRawRequest::execute()
{
	MYSQL* mysql = static_cast<MYSQL*>(m_handle);
	if (mysql == NULL)
	{
		throw CLiteDBError("mysql is not open.");
	}

	if (0 != mysql_real_query(mysql, m_sql.c_str(), static_cast<unsigned long>(m_sql.size())))
	{
		string msg = "exec sql: " + m_sql;
        msg += mysql_error(mysql);
		throw CMysqlError(msg, mysql_errno(mysql));
	}

    MYSQL_RES* result = NULL;
    uint64 rowCnt = 0;
    uint32 fieldCnt = 0;
    result = mysql_store_result(mysql);
    rowCnt = mysql_affected_rows(mysql);
    fieldCnt = mysql_field_count(mysql);
    if (result != NULL)
    {
        // 返回结果集
        return new CMysqlRawResultSet(result, rowCnt, fieldCnt);
    }
    else
    {
        if (fieldCnt != 0)
        {
            string msg = "store result error, exec sql: " + m_sql;
            msg += mysql_error(mysql);
            throw CMysqlError(msg, mysql_errno(mysql));
        }
        else
        {
            // 此sql操作无结果集(update、insert等)
            return new CMysqlRawResultSet(result, rowCnt, fieldCnt);
        }
    }
}

