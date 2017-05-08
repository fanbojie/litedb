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

#ifndef LITEDB_MYSQLPREPAREDREQUEST_H
#define LITEDB_MYSQLPREPAREDREQUEST_H

#include <vector>
#include "Types.h"
#include "mysql.h"
#include "DatabaseRequest.h"
#include "ParamStatement.h"

namespace litedb
{
	class CMysqlPreparedRequest: public litedb::CDatabaseRequest
	{
	public:
		CMysqlPreparedRequest();
		virtual ~CMysqlPreparedRequest();

		virtual litedb::CResultSet* execute();

		virtual void prepareParameter();
        
        void clearParameter();

        virtual void setBool(int index, bool value);
        virtual void setUInt8(int index, uint8 value);
		virtual void setUInt16(int index, uint16 value);
		virtual void setUInt32(int index, uint32 value);
		virtual void setUInt64(int index, uint64 value);
		virtual void setInt8(int index, int8 value);
		virtual void setInt16(int index, int16 value);
		virtual void setInt32(int index, int32 value);
		virtual void setInt64(int index, int64 value);
		virtual void setFloat(int index, float value);
		virtual void setDouble(int index, double value);
		virtual void setString(int index, const std::string& value);
		virtual void setNull(int index);
	private:
        void bindParameters();
        void _setBool(int index, bool value);
        void _setUInt8(int index, uint8 value);
        void _setUInt16(int index, uint16 value);
        void _setUInt32(int index, uint32 value);
        void _setUInt64(int index, uint64 value);
        void _setInt8(int index, int8 value);
        void _setInt16(int index, int16 value);
        void _setInt32(int index, int32 value);
        void _setInt64(int index, int64 value);
        void _setFloat(int index, float value);
        void _setDouble(int index, double value);
        void _setString(int index, const char* value);
        void _setNull(int index);
		void setValue(MYSQL_BIND* param, enum_field_types type, 
						const void* value, uint32 len, bool isUnsigned);
	private:
        std::vector<litedb::ParamStatement> m_param;
		MYSQL_STMT* m_stmt;
		MYSQL_BIND* m_bind;
		int			m_paramCount;
	};
}
#endif
