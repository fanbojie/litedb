#include "MysqlPreparedRequest.h"
#include <string.h>
#include <stdlib.h>
#include "litebase/Trace.h"
#include "MysqlPreparedResultSet.h"
#include "MysqlError.h"
#include "Utility.h"

using namespace std;
using namespace litedb;

litedb::CMysqlPreparedRequest::CMysqlPreparedRequest()
: m_stmt(NULL)
, m_bind(NULL)
{
}

litedb::CMysqlPreparedRequest::~CMysqlPreparedRequest()
{
	delete[] m_bind;
	m_bind = NULL;
}

litedb::CResultSet* litedb::CMysqlPreparedRequest::execute()
{
    prepareParameter();

	if (mysql_stmt_bind_param(m_stmt, m_bind))
	{
		string errMsg = mysql_stmt_error(m_stmt);
		int errNo = mysql_stmt_errno(m_stmt);
        clearParameter();
		throw CMysqlError(errMsg, errNo);
	}

    if (mysql_stmt_execute(m_stmt))
    {
        string errMsg = mysql_stmt_error(m_stmt);
        int errNo = mysql_stmt_errno(m_stmt);
        clearParameter();
        throw CMysqlError(errMsg, errNo);
    }

    clearParameter();

    MYSQL_RES* result = NULL;
    uint64 rowCnt = 0;
    uint32 fieldCnt = 0;
	result = mysql_stmt_result_metadata(m_stmt);
    rowCnt = mysql_stmt_affected_rows(m_stmt);
	fieldCnt = mysql_stmt_field_count(m_stmt);

    if (result != NULL)
    {
        if (m_stmt->bind_result_done)
        {
            delete[] m_stmt->bind->length;
            delete[] m_stmt->bind->is_null;
        }

        MYSQL_BIND* rBind = new MYSQL_BIND[fieldCnt];
        my_bool* isNull = new my_bool[fieldCnt];
        unsigned long* length = new unsigned long[fieldCnt];
        memset(isNull, 0, sizeof(my_bool)*fieldCnt);
        memset(rBind, 0, sizeof(MYSQL_BIND)*fieldCnt);
        memset(length, 0, sizeof(unsigned long)*fieldCnt);

        if (mysql_stmt_store_result(m_stmt))
        {
            delete[] rBind;
            delete[] isNull;
            delete[] length;
            throw CMysqlError(mysql_stmt_error(m_stmt), mysql_stmt_errno(m_stmt));
        }

        uint32 i = 0;
        MYSQL_FIELD* field = mysql_fetch_field(result);
        while(field)
        {
            size_t size = CUtility::sizeForMysqlType(field);
            rBind[i].buffer_type = field->type;
            rBind[i].buffer = malloc(size);
            memset(rBind[i].buffer, 0, size);
            rBind[i].buffer_length = size;
            rBind[i].length = &length[i];
            rBind[i].is_null = &isNull[i];
            rBind[i].error = NULL;
            rBind[i].is_unsigned = field->flags & UNSIGNED_FLAG;
            ++i;
            field = mysql_fetch_field(result);
        }

        if (mysql_stmt_bind_result(m_stmt, rBind))
        {
            for (unsigned i=0; i<fieldCnt; ++i)
            {
                free(rBind[i].buffer);
            }
            delete[] rBind;
            rBind = NULL;
            delete[] isNull;
            isNull = NULL;
            delete[] length;
            length = NULL;
            throw CMysqlError(mysql_stmt_error(m_stmt), mysql_stmt_errno(m_stmt));
        }

        return new CMysqlPreparedResultSet(result, m_stmt, rBind, isNull, length, rowCnt, fieldCnt);       
    }
    else
    {
        if (fieldCnt != 0)
        {
            // 失败
            string errMsg = mysql_stmt_error(m_stmt);
            int errNo = mysql_stmt_errno(m_stmt);
            throw CMysqlError(errMsg, errNo);
        }
        else
        {
            // 此sql操作无结果集
            return new CMysqlPreparedResultSet(result, m_stmt, NULL, NULL, NULL, rowCnt, fieldCnt);
        }
    }
}

void litedb::CMysqlPreparedRequest::setBool( int index, bool value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }

    m_param[index].data.boolean = value;
    m_param[index].type = litedb::TYPE_BOOL;
}

void litedb::CMysqlPreparedRequest::setUInt8( int index, uint8 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.ui8 = value;
    m_param[index].type = litedb::TYPE_UI8;
}

void litedb::CMysqlPreparedRequest::setUInt16( int index, uint16 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.ui16 = value;
    m_param[index].type = litedb::TYPE_UI16;
}

void litedb::CMysqlPreparedRequest::setUInt32( int index, uint32 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.ui32 = value;
    m_param[index].type = litedb::TYPE_UI32;
}

void litedb::CMysqlPreparedRequest::setUInt64( int index, uint64 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.ui64 = value;
    m_param[index].type = litedb::TYPE_UI64;
}

void litedb::CMysqlPreparedRequest::setInt8( int index, int8 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.i8 = value;
    m_param[index].type = litedb::TYPE_I8;
}

void litedb::CMysqlPreparedRequest::setInt16( int index, int16 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.i16 = value;
    m_param[index].type = litedb::TYPE_I16;
}

void litedb::CMysqlPreparedRequest::setInt32( int index, int32 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.i32 = value;
    m_param[index].type = litedb::TYPE_I32;
}

void litedb::CMysqlPreparedRequest::setInt64( int index, int64 value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.i64 = value;
    m_param[index].type = litedb::TYPE_I64;
}

void litedb::CMysqlPreparedRequest::setFloat( int index, float value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.f = value;
    m_param[index].type = litedb::TYPE_FLOAT;
}

void litedb::CMysqlPreparedRequest::setDouble( int index, double value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].data.d = value;
    m_param[index].type = litedb::TYPE_DOUBLE;
}

void litedb::CMysqlPreparedRequest::setString( int index, const std::string& value )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }
    m_param[index].str = value;
    m_param[index].type = litedb::TYPE_STRING;
}

void litedb::CMysqlPreparedRequest::setNull( int index )
{
    if (index >= (int)m_param.size())
    {
        m_param.resize(index+1);
    }

    m_param[index].type = litedb::TYPE_NULL;
}

void litedb::CMysqlPreparedRequest::setValue( MYSQL_BIND* param, enum_field_types type, 
											 const void* value, uint32 len, bool isUnsigned )
{
	param->buffer_type = type;
	delete [] static_cast<char *>(param->buffer);
	param->buffer = new char[len];
	param->buffer_length = 0;
	param->is_null_value = 0;
	param->length = NULL;               // Only != NULL for strings
	param->is_unsigned = isUnsigned;

	memcpy(param->buffer, value, len);
}

void litedb::CMysqlPreparedRequest::prepareParameter()
{
	MYSQL* mysql = static_cast<MYSQL*>(m_handle);
	if (mysql == NULL)
	{
		throw CLiteDBError("mysql is not open.");
	}

	m_stmt = mysql_stmt_init(mysql);
	if (m_stmt == NULL)
	{
		throw CMysqlError(mysql_error(mysql), mysql_errno(mysql));
	}

	if (mysql_stmt_prepare(m_stmt, m_sql.c_str(), static_cast<unsigned long>(m_sql.length())))
	{
		int error = mysql_stmt_errno(m_stmt);
		string msg = mysql_stmt_error(m_stmt);
		mysql_stmt_close(m_stmt);
		m_stmt = NULL;
		throw CMysqlError(msg, error);
	}

	m_paramCount = mysql_stmt_param_count(m_stmt);
	m_bind = new MYSQL_BIND[m_paramCount];
	memset(m_bind, 0, sizeof(MYSQL_BIND)*m_paramCount);
	/// "If set to 1, causes mysql_stmt_store_result() to update the metadata MYSQL_FIELD->max_length value."
 	my_bool bool_tmp = 1;
 	mysql_stmt_attr_set(m_stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &bool_tmp);
    bindParameters();
}

void litedb::CMysqlPreparedRequest::clearParameter()
{
    for (int i=0; i<m_paramCount; ++i)
    {
        delete m_bind[i].length;
        m_bind[i].length = NULL;
        delete[] (char*)m_bind[i].buffer;
        m_bind[i].buffer = NULL;
    }
}

void litedb::CMysqlPreparedRequest::bindParameters()
{
    int i = 0;
    for (; i<(int)m_param.size(); i++)
    {
        switch(m_param[i].type)
        {
        case TYPE_BOOL:
            _setBool(i, m_param[i].data.boolean);
            break;
        case TYPE_UI8:
            _setUInt8(i, m_param[i].data.ui8);
            break;
        case TYPE_UI16:
            _setUInt16(i, m_param[i].data.ui8);
            break;
        case TYPE_UI32:
            _setUInt32(i, m_param[i].data.ui32);
            break;
        case TYPE_UI64:
            _setUInt64(i, m_param[i].data.ui64);
            break;
        case TYPE_I8:
            _setInt8(i, m_param[i].data.i8);
            break;
        case TYPE_I16:
            _setInt16(i, m_param[i].data.i16);
            break;
        case TYPE_I32:
            _setInt32(i, m_param[i].data.i32);
            break;
        case TYPE_I64:
            _setInt64(i, m_param[i].data.i64);
            break;
        case TYPE_FLOAT:
            _setFloat(i, m_param[i].data.f);
            break;
        case TYPE_DOUBLE:
            _setDouble(i, m_param[i].data.d);
            break;
        case TYPE_STRING:
            _setString(i, m_param[i].str.c_str());
            break;
        case TYPE_NULL:
            _setNull(i);
            break;
        }
    }

    if (i<m_paramCount)
    {
        TRACE_ERR(0, "parameter count error, paramCnt=%d inputCnt=%d.",
            m_paramCount, i);
    }
}

void litedb::CMysqlPreparedRequest::_setBool( int index, bool value )
{
    _setUInt8(index, value ? 1 : 0);
}

void litedb::CMysqlPreparedRequest::_setUInt8( int index, uint8 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_TINY, &value, sizeof(uint8), true);
}

void litedb::CMysqlPreparedRequest::_setUInt16( int index, uint16 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_SHORT, &value, sizeof(uint16), true);
}

void litedb::CMysqlPreparedRequest::_setUInt32( int index, uint32 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_LONG, &value, sizeof(uint32), true);
}

void litedb::CMysqlPreparedRequest::_setUInt64( int index, uint64 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_LONGLONG, &value, sizeof(uint64), true);
}

void litedb::CMysqlPreparedRequest::_setInt8( int index, int8 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_TINY, &value, sizeof(int8), false);
}

void litedb::CMysqlPreparedRequest::_setInt16( int index, int16 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_SHORT, &value, sizeof(int16), false);
}

void litedb::CMysqlPreparedRequest::_setInt32( int index, int32 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_LONG, &value, sizeof(int32), false);
}

void litedb::CMysqlPreparedRequest::_setInt64( int index, int64 value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_LONGLONG, &value, sizeof(int64), false);
}

void litedb::CMysqlPreparedRequest::_setFloat( int index, float value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_FLOAT, &value, sizeof(float), true);
}

void litedb::CMysqlPreparedRequest::_setDouble( int index, double value )
{
    MYSQL_BIND* param = &m_bind[index];
    setValue(param, MYSQL_TYPE_DOUBLE, &value, sizeof(double), true);
}

void litedb::CMysqlPreparedRequest::_setString( int index, const char* value )
{
    MYSQL_BIND* param = &m_bind[index];
    size_t len = strlen(value) + 1;
    param->buffer_type = MYSQL_TYPE_VAR_STRING;
    delete [] static_cast<char *>(param->buffer);
    param->buffer = new char[len];
    param->buffer_length = len;
    param->is_null_value = 0;
    delete param->length;
    param->length = new unsigned long(len-1);

    memcpy(param->buffer, value, len);
}

void litedb::CMysqlPreparedRequest::_setNull( int index )
{
    MYSQL_BIND* param = &m_bind[index];
    param->buffer_type = MYSQL_TYPE_NULL;
    delete [] static_cast<char *>(param->buffer);
    param->buffer = NULL;
    param->buffer_length = 0;
    param->is_null_value = 1;
    delete param->length;
    param->length = NULL;
}
