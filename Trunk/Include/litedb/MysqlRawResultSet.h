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

#ifndef LITEDB_MYSQLRAWRESULTSET_H
#define LITEDB_MYSQLRAWRESULTSET_H

#include <string>
#include "ResultSet.h"
#include "mysql.h"

namespace litedb
{
	class CMysqlRawResultSet: public litedb::CResultSet
	{
	public:
		CMysqlRawResultSet(MYSQL_RES* result, uint64 rowCnt, uint32 fieldCnt);
		virtual ~CMysqlRawResultSet();
        
        virtual int32 getFieldAsInt32(const std::string &fieldName);
        virtual int64 getFieldAsInt64(const std::string &fieldName);
        virtual uint32 getFieldAsUInt32(const std::string &fieldName);
        virtual uint64 getFieldAsUInt64(const std::string &fieldName);
        virtual std::string getFieldAsString(const std::string &fieldName); 
        virtual bool nextRow();

    private:
        MYSQL_ROW  m_currentRow;    // 当前行
        MYSQL_FIELD* m_fields;      // 列信息
		MYSQL_RES* m_result;        // 数据库返回的结果集
	};
}
#endif
