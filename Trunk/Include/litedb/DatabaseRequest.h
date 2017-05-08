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

#ifndef LITEDB_DATABASEREQUEST_H
#define LITEDB_DATABASEREQUEST_H

#include <string>
#include "Config.h"
#include "Types.h"
#include "litebase/Noncopyable.h"
#include "ResultSet.h"

namespace litedb
{
	class CDatabaseRequest: public litebase::details::CNoncopyable
	{
	public:
		CDatabaseRequest();
		virtual ~CDatabaseRequest();

		void setCmdText(const std::string& cmd)
		{
			m_sql = cmd;
		}

        const std::string& getCmdText() const
        {
            return m_sql;
        }
		
		void setHandle(void* handle)
		{
			m_handle = handle;
		}

        virtual litedb::CResultSet* execute() = 0;

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

	protected:
		std::string m_sql;          // sql”Ôæ‰
		void*	    m_handle;       //  ˝æ›ø‚∑√Œ handle	
	};
}
#endif
