#include "MysqlPreparedResultSet.h"
#include <stdlib.h>
#include "litebase/Trace.h"
#include "mysql_time.h"

using namespace std;
using namespace litedb;

litedb::CMysqlPreparedResultSet::CMysqlPreparedResultSet( MYSQL_RES* result, MYSQL_STMT* stmt, MYSQL_BIND* bind, 
                                                         my_bool* isNull, unsigned long* length,
                                                         uint64 rowCnt, uint32 fieldCnt )
: litedb::CResultSet(rowCnt, fieldCnt) 
, m_fields(NULL)
, m_result(result)
, m_stmt(stmt)
, m_rBind(bind)
, m_isNull(isNull)
, m_length(length)
{
    if (m_result != NULL)
    {
        m_fields = mysql_fetch_fields(m_result);
    }

    if (m_stmt != NULL)
    {
        int result = mysql_stmt_fetch(m_stmt);
        if (result == -1)
        {
            TRACE_ERR(0, "stmt fetch error, errno=%d err=%s.",
               mysql_stmt_errno(m_stmt), mysql_stmt_error(m_stmt));
        }
        else
        {
            m_rowNum = mysql_stmt_num_rows(m_stmt);
            m_fieldNum = mysql_stmt_field_count(m_stmt);
            m_rowCnt = mysql_stmt_affected_rows(m_stmt);
        }
    }
}

litedb::CMysqlPreparedResultSet::~CMysqlPreparedResultSet()
{
    if (m_stmt->bind_result_done)
    {
        delete[] m_stmt->bind->length;
        delete[] m_stmt->bind->is_null;
    }

    mysql_stmt_free_result(m_stmt);

    mysql_stmt_close(m_stmt);
    m_stmt = NULL;

    if (m_result != NULL)
    {
        mysql_free_result(m_result);
    }

    for (unsigned i=0; i<m_fieldCnt; ++i)
    {
        free(m_rBind[i].buffer);
    }

    delete[] m_rBind;
    m_rBind = NULL;
}

int32 litedb::CMysqlPreparedResultSet::getFieldAsInt32( const std::string &fieldName )
{
    if (m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt; i++)
        {
            if (m_fields[i].org_name == fieldName && !*m_rBind[i].is_null)
            {
                return cast2Int32(&m_rBind[i]); 
            }
            else if (m_fields[i].org_name == fieldName)
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

int64 litedb::CMysqlPreparedResultSet::getFieldAsInt64( const std::string &fieldName )
{
    if (m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt; i++)
        {
            if (m_fields[i].org_name == fieldName && !*m_rBind[i].is_null)
            {
                return cast2Int64(&m_rBind[i]);   
            }
            else if (m_fields[i].org_name == fieldName)
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

uint32 litedb::CMysqlPreparedResultSet::getFieldAsUInt32( const std::string &fieldName )
{
    if (m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt; i++)
        {
            if (m_fields[i].org_name == fieldName && !*m_rBind[i].is_null)
            {
                return cast2UInt32(&m_rBind[i]); 
            }
            else if (m_fields[i].org_name == fieldName)
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

uint64 litedb::CMysqlPreparedResultSet::getFieldAsUInt64( const std::string &fieldName )
{
    if (m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt; i++)
        {
            if (m_fields[i].org_name == fieldName && !*m_rBind[i].is_null)
            {
                return cast2UInt64(&m_rBind[i]);   
            }
            else if (m_fields[i].org_name == fieldName)
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


std::string litedb::CMysqlPreparedResultSet::getFieldAsString( const std::string &fieldName )
{
    if (m_fields != NULL)
    {
        for (unsigned i=0; i<m_fieldCnt; i++)
        {
            if (m_fields[i].org_name == fieldName && !*m_rBind[i].is_null)
            {
                return string(static_cast<char*>(m_rBind[i].buffer), m_rBind[i].buffer_length);
            }
            else if (m_fields[i].org_name == fieldName)
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

bool litedb::CMysqlPreparedResultSet::nextRow()
{
    if (m_stmt == NULL)
    {
        return false;
    }

    if (!mysql_stmt_fetch(m_stmt))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int32 litedb::CMysqlPreparedResultSet::cast2Int32( MYSQL_BIND* bind )
{
    switch (bind->buffer_type)
    {
    case MYSQL_TYPE_TINY:
        return (bind->is_unsigned ? *reinterpret_cast<uint8*>(bind->buffer) : *reinterpret_cast<int8*>(bind->buffer));
    case MYSQL_TYPE_YEAR:
    case MYSQL_TYPE_SHORT:
        return (bind->is_unsigned ? *reinterpret_cast<uint16*>(bind->buffer) : *reinterpret_cast<int16*>(bind->buffer));
    case MYSQL_TYPE_INT24:
    case MYSQL_TYPE_LONG:
    case MYSQL_TYPE_FLOAT:
        return (bind->is_unsigned ? *reinterpret_cast<int32*>(bind->buffer) : *reinterpret_cast<uint32*>(bind->buffer));
    case MYSQL_TYPE_DOUBLE:
    case MYSQL_TYPE_LONGLONG:
    case MYSQL_TYPE_BIT:
        return (bind->is_unsigned ? *reinterpret_cast<uint64*>(bind->buffer) : *reinterpret_cast<int64*>(bind->buffer));
    default:
        return 0;
    }
}

int64 litedb::CMysqlPreparedResultSet::cast2Int64( MYSQL_BIND* bind )
{
    switch (bind->buffer_type)
    {
    case MYSQL_TYPE_TINY:
        return (bind->is_unsigned ? *reinterpret_cast<uint8*>(bind->buffer) : *reinterpret_cast<int8*>(bind->buffer));
    case MYSQL_TYPE_YEAR:
    case MYSQL_TYPE_SHORT:
        return (bind->is_unsigned ? *reinterpret_cast<uint16*>(bind->buffer) : *reinterpret_cast<int16*>(bind->buffer));
    case MYSQL_TYPE_INT24:
    case MYSQL_TYPE_LONG:
    case MYSQL_TYPE_FLOAT:
        return (bind->is_unsigned ? *reinterpret_cast<int32*>(bind->buffer) : *reinterpret_cast<uint32*>(bind->buffer));
    case MYSQL_TYPE_DOUBLE:
    case MYSQL_TYPE_LONGLONG:
    case MYSQL_TYPE_BIT:
        return (bind->is_unsigned ? *reinterpret_cast<uint64*>(bind->buffer) : *reinterpret_cast<int64*>(bind->buffer));
    default:
        return 0;
    }
}

uint32 litedb::CMysqlPreparedResultSet::cast2UInt32( MYSQL_BIND* bind )
{
    switch (bind->buffer_type)
    {
    case MYSQL_TYPE_TINY:
        return (bind->is_unsigned ? *reinterpret_cast<uint8*>(bind->buffer) : *reinterpret_cast<int8*>(bind->buffer));
    case MYSQL_TYPE_YEAR:
    case MYSQL_TYPE_SHORT:
        return (bind->is_unsigned ? *reinterpret_cast<uint16*>(bind->buffer) : *reinterpret_cast<int16*>(bind->buffer));
    case MYSQL_TYPE_INT24:
    case MYSQL_TYPE_LONG:
    case MYSQL_TYPE_FLOAT:
        return (bind->is_unsigned ? *reinterpret_cast<int32*>(bind->buffer) : *reinterpret_cast<uint32*>(bind->buffer));
    case MYSQL_TYPE_DOUBLE:
    case MYSQL_TYPE_LONGLONG:
    case MYSQL_TYPE_BIT:
        return (bind->is_unsigned ? *reinterpret_cast<uint64*>(bind->buffer) : *reinterpret_cast<int64*>(bind->buffer));
    default:
        return 0;
    }
}

uint64 litedb::CMysqlPreparedResultSet::cast2UInt64( MYSQL_BIND* bind )
{
    switch (bind->buffer_type)
    {
    case MYSQL_TYPE_TINY:
        return (bind->is_unsigned ? *reinterpret_cast<uint8*>(bind->buffer) : *reinterpret_cast<int8*>(bind->buffer));
    case MYSQL_TYPE_YEAR:
    case MYSQL_TYPE_SHORT:
        return (bind->is_unsigned ? *reinterpret_cast<uint16*>(bind->buffer) : *reinterpret_cast<int16*>(bind->buffer));
    case MYSQL_TYPE_INT24:
    case MYSQL_TYPE_LONG:
    case MYSQL_TYPE_FLOAT:
        return (bind->is_unsigned ? *reinterpret_cast<int32*>(bind->buffer) : *reinterpret_cast<uint32*>(bind->buffer));
    case MYSQL_TYPE_DOUBLE:
    case MYSQL_TYPE_LONGLONG:
    case MYSQL_TYPE_BIT:
        return (bind->is_unsigned ? *reinterpret_cast<uint64*>(bind->buffer) : *reinterpret_cast<int64*>(bind->buffer));
    default:
        return 0;
    }
}
