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

#ifndef LITEDB_CONNECTIONPOOL_H
#define LITEDB_CONNECTIONPOOL_H

#include <queue>
#include <string>
#include "Config.h"
#include "litebase/Noncopyable.h"
#include "litebase/ConditionVariable.h"
#include "litebase/Singleton.h"
#include "ConnectionInfo.h"

namespace litebase
{
    namespace details
    {
        class CThread;
    }
}

namespace litedb
{
    class CDatabaseRequest;
    class CDatabaseFactory;
    class CSqlTask;
    class CConnection;

    class LITEDB_DECL CConnectionPool: public litebase::details::CSingleton<CConnectionPool>
	{
        enum CONN_TYPE
        {
            TYPE_SYNC,
            TYPE_ASYNC,
            TYPE_MAX,
        };

        friend class litebase::details::CSingleton<CConnectionPool>;
    private:
        CConnectionPool();

    public:
		~CConnectionPool();

		void init(int size);

		// 初始化数据库连接池
		int open(const std::string& connStr);
		// 关闭连接池
		void close();

		// 获取可用连接
		litedb::CConnection* getConnection();
		
		// 获取一个任务
		litedb::CSqlTask* createTask(int type);

		// 异步调用时把sql请求push到队列中
		void pushTask(litedb::CSqlTask* task);

        void keepAlive();

	private:
		int initFactory();
        int generateTaskId();

	private:
        int m_poolSize;
        int m_taskId;
        litebase::details::CMutex           m_idMutex;
		litedb::CDatabaseFactory*           m_factory;
        litebase::details::CThread*         m_pingWorker;    
		std::queue<litedb::CSqlTask*>       m_taskQueue;
		litebase::details::CConVariable	    m_condition;
		std::vector<litedb::CConnection*>*  m_connections[TYPE_MAX];
		litedb::CConnectionInfo	            m_connectionInfo;
	};
}
#endif
