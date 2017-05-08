//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2014-02-14        fan_bojie            Create
//

#ifndef LITEDB_MYSQLPREPAREDRESULTSET_H
#define LITEDB_MYSQLPREPAREDRESULTSET_H

#include <string>
#include "ResultSet.h"
#include "mysql.h"

namespace litedb
{
    class CMysqlPreparedResultSet: public litedb::CResultSet
    {
    public:
        CMysqlPreparedResultSet(MYSQL_RES* result, MYSQL_STMT* stmt, MYSQL_BIND* bind, my_bool* isNull, 
            unsigned long* length, uint64 rowCount, uint32 fieldCount);
        virtual ~CMysqlPreparedResultSet();

        virtual int32 getFieldAsInt32(const std::string &fieldName);
        virtual int64 getFieldAsInt64(const std::string &fieldName);
        virtual uint32 getFieldAsUInt32(const std::string &fieldName);
        virtual uint64 getFieldAsUInt64(const std::string &fieldName);
        virtual std::string getFieldAsString(const std::string &fieldName); 
        virtual bool nextRow();

    private:
        int32 cast2Int32(MYSQL_BIND* bind);
        uint32 cast2UInt32(MYSQL_BIND* bind);
        uint64 cast2UInt64(MYSQL_BIND* bind);
        int64 cast2Int64(MYSQL_BIND* bind);

    private:
        MYSQL_FIELD* m_fields;      // 列信息
        MYSQL_RES* m_result;        // 数据库返回的结果集
        MYSQL_STMT* m_stmt;
        MYSQL_BIND* m_rBind;
        my_bool* m_isNull;
        unsigned long* m_length;
    };
}
#endif
