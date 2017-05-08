#include "MysqlRawResultSet.h"
#include <stdlib.h>
#include "litebase/Trace.h"

litedb::CMysqlRawResultSet::CMysqlRawResultSet(MYSQL_RES* result, uint64 rowCnt, uint32 fieldCnt)
: litedb::CResultSet(rowCnt, fieldCnt) 
, m_currentRow(NULL)
, m_fields(NULL)
, m_result(result)
{
    if (m_result != NULL)
    {
        // 返回结果集
        m_currentRow = mysql_fetch_row(m_result); 
        m_fields = mysql_fetch_fields(m_result);
        m_fieldNum = mysql_num_fields(m_result);
        m_rowNum = mysql_num_rows(m_result);
    }
    else
    {
/*        TRACE_INFO("exec no result sql operator.");*/
    }
}

litedb::CMysqlRawResultSet::~CMysqlRawResultSet()
{
    if (m_result != NULL)
    {
        mysql_free_result(m_result);
        m_result = NULL;
    }
}

int32 litedb::CMysqlRawResultSet::getFieldAsInt32( const std::string &fieldName )
{
    if (m_currentRow != NULL && m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt;++i)
        {
            if (m_fields[i].org_name == fieldName && m_currentRow[i] != NULL)
            {               
                return atoi(m_currentRow[i]);
            }
            else if (m_fields[i].org_name == fieldName && m_currentRow[i] == NULL)
            {
                TRACE_WARNING("tableName=%s fieldName=%s value is null.",
                    m_fields[i].org_table, fieldName.c_str());
                return 0;
            }
            else
            {

            }
        }

        TRACE_WARNING("has no field %s.", fieldName.c_str());
    }
    else
    {
        TRACE_WARNING("the operator has no result, return default value, fieldName=%s.", fieldName.c_str());
    }

    return 0;
}

int64 litedb::CMysqlRawResultSet::getFieldAsInt64( const std::string &fieldName )
{
    if (m_currentRow != NULL && m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt;++i)
        {
            if (m_fields[i].org_name == fieldName && m_currentRow[i] != NULL)
            {
                return atoll(m_currentRow[i]);
            }
            else if (m_fields[i].org_name == fieldName && m_currentRow[i] == NULL)
            {
                TRACE_WARNING("tableName=%s fieldName=%s value is null.",
                    m_fields[i].org_table, fieldName.c_str());
                return 0;
            }
            else
            {

            }
        }

        TRACE_WARNING("has no field %s.", fieldName.c_str());
    }       
    else
    {
        TRACE_WARNING("the operator has no result, return default value, fieldName=%s.", fieldName.c_str());
    }

    return 0;
}


uint32 litedb::CMysqlRawResultSet::getFieldAsUInt32( const std::string &fieldName )
{
    if (m_currentRow != NULL && m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt;++i)
        {
            if (m_fields[i].org_name == fieldName && m_currentRow[i] != NULL)
            {
                return strtoul(m_currentRow[i], NULL, 10);
            }
            else if (m_fields[i].org_name == fieldName && m_currentRow[i] == NULL)
            {
                TRACE_WARNING("tableName=%s fieldName=%s value is null.",
                    m_fields[i].org_table, fieldName.c_str());
                return 0;
            }
            else
            {

            }
        }

        TRACE_WARNING("has no field %s.", fieldName.c_str());
    }       
    else
    {
        TRACE_WARNING("the operator has no result, return default value, fieldName=%s.", fieldName.c_str());
    }

    return 0;
}

uint64 litedb::CMysqlRawResultSet::getFieldAsUInt64( const std::string &fieldName )
{
    if (m_currentRow != NULL && m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt;++i)
        {
            if (m_fields[i].org_name == fieldName && m_currentRow[i] != NULL)
            {
                return strtoull(m_currentRow[i], NULL, 10);
            }
            else if (m_fields[i].org_name == fieldName && m_currentRow[i] == NULL)
            {
                TRACE_WARNING("tableName=%s fieldName=%s value is null.",
                    m_fields[i].org_table, fieldName.c_str());
                return 0;
            }
            else
            {

            }
        }

        TRACE_WARNING("has no field %s.", fieldName.c_str());
    }       
    else
    {
        TRACE_WARNING("the operator has no result, return default value, fieldName=%s.", fieldName.c_str());
    }

    return 0;
}

std::string litedb::CMysqlRawResultSet::getFieldAsString( const std::string &fieldName )
{
    if (m_currentRow != NULL && m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt;++i)
        {
            if (m_fields[i].org_name == fieldName && m_currentRow[i] != NULL)
            {
                return m_currentRow[i];
            }
            else if (m_fields[i].org_name == fieldName && m_currentRow[i] == NULL)
            {
                TRACE_WARNING("tableName=%s fieldName=%s value is null.",
                    m_fields[i].org_table, fieldName.c_str());
                return "";
            }
            else
            {

            }
        }

        TRACE_WARNING("has no field %s.", fieldName.c_str());
    }       
    else
    {
        TRACE_WARNING("the operator has no result, return default value, fieldName=%s.", fieldName.c_str());
    }

    return "";
}

bool litedb::CMysqlRawResultSet::nextRow()
{
    if (m_result == NULL)
    {
        return false;
    }

    MYSQL_ROW row;
    row = mysql_fetch_row(m_result);
    if (row == NULL)
    {
        return false;
    }

    m_currentRow = row;
    return true;
}
