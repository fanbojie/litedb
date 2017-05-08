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

#ifndef LITEDB_CONNECTION_H
#define LITEDB_CONNECTION_H

#include <string>
#include <queue>
#include "Config.h"
#include "litebase/Noncopyable.h"
#include "litebase/Mutex.h"
#include "ConnectionInfo.h"

namespace litebase
{
    namespace details
    {
        class CConVariable;
        class CThread;
    }
}

namespace litedb
{
    class CSqlTask;
    class CConnectionWorker;

    class CConnection: public litebase::details::CNoncopyable
	{
	public:
		CConnection();
		virtual ~CConnection();
		void init(const litedb::CConnectionInfo& connInfo);
		void init(const litedb::CConnectionInfo& connInfo, 
				std::queue<litedb::CSqlTask*>* request,
				litebase::details::CConVariable* condition);

		virtual void open() = 0;
		virtual void close() = 0;
        virtual void* getHandle() = 0;

        int tryLock()
		{
			return m_mutex.trylock();
		}

        void unlock()
        {
            m_mutex.unlock();
        }

        bool isClose()
        {
            return m_isClose;
        }

        bool isWork();

	protected:
        bool                        m_isClose;    
        litebase::details::CThread* m_worker;    // 异步调用工作线程        
		litedb::CConnectionInfo     m_connectionInfo;
		litebase::details::CMutex   m_mutex;      // 连接锁
	};
}
#endif
