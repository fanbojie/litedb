#include "Utility.h"

size_t litedb::CUtility::sizeForMysqlType( MYSQL_FIELD* field )
{
    switch (field->type)
    {
    case MYSQL_TYPE_NULL:
        return 0;
    case MYSQL_TYPE_TINY:
        return 1;
    case MYSQL_TYPE_YEAR:
    case MYSQL_TYPE_SHORT:
        return 2;
    case MYSQL_TYPE_INT24:
    case MYSQL_TYPE_LONG:
    case MYSQL_TYPE_FLOAT:
        return 4;
    case MYSQL_TYPE_DOUBLE:
    case MYSQL_TYPE_LONGLONG:
    case MYSQL_TYPE_BIT:
        return 8;

    case MYSQL_TYPE_TIMESTAMP:
    case MYSQL_TYPE_DATE:
    case MYSQL_TYPE_TIME:
    case MYSQL_TYPE_DATETIME:
        return sizeof(MYSQL_TIME);

    case MYSQL_TYPE_TINY_BLOB:
    case MYSQL_TYPE_MEDIUM_BLOB:
    case MYSQL_TYPE_LONG_BLOB:
    case MYSQL_TYPE_BLOB:
    case MYSQL_TYPE_STRING:
    case MYSQL_TYPE_VAR_STRING:
        return field->max_length + 1;

    case MYSQL_TYPE_DECIMAL:
    case MYSQL_TYPE_NEWDECIMAL:
        return 64;

    case MYSQL_TYPE_GEOMETRY:
    default:
        return 0;
    }
}

