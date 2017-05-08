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

#ifndef LITEDB_SQLTASK_H
#define LITEDB_SQLTASK_H

#include <string>
#include "Types.h"
#include "Config.h"
#include "litebase/Noncopyable.h"

namespace litedb
{
    class CResultSet;
    class CDatabaseRequest;
    class CConnectionPool;
    class CConnection;

	class LITEDB_DECL CSqlTask: public litebase::details::CNoncopyable
	{
	public:
		CSqlTask();
		virtual ~CSqlTask();

        void init(int type, int taskId, litedb::CConnectionPool* pool = NULL);

 		void call();

        virtual void setCmdText(const std::string& cmd) = 0;
        virtual int execute() = 0;

        int getTaskId()
        {
            return m_taskId;
        }

		litedb::CDatabaseRequest* getRequest()
		{
			return m_request;
		}

		litedb::CResultSet* getResult()
		{
			return m_response;
		}

		void setRequest(litedb::CDatabaseRequest* request)
		{
			m_request = request;
		}

        void setConn(litedb::CConnection* conn)
        {
            m_conn = conn;
        }

 		void setConnPool(litedb::CConnectionPool* conns)
 		{
 			m_connPool = conns;
 		}

        void release();

        void setParamAsUInt8(int index, uint8 value);
        void setParamAsUInt16(int index, uint16 value);
        void setParamAsUInt32(int index, uint32 value);
        void setParamAsUInt64(int index, uint64 value);
        void setParamAsInt8(int index, int8 value);
        void setParamAsInt16(int index, int16 value);
        void setParamAsInt32(int index, int32 value);
        void setParamAsInt64(int index, int64 value);
        void setParamAsFloat(int index, float value);
        void setParamAsDouble(int index, double value);
        void setParamAsString(int index, const std::string& value);
        void setParamAsNull(int index);

	protected:
        int m_type;                 // 同步task还是异步task
        int m_taskId;
        litedb::CConnection*        m_conn;
		litedb::CConnectionPool*	m_connPool;
		litedb::CDatabaseRequest*   m_request;
		litedb::CResultSet*	        m_response;
	};
}
#endif
