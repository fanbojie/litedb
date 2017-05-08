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

#ifndef LITEDB_CONNECTIONWORKER_H
#define LITEDB_CONNECTIONWORKER_H

#include <queue>
#include "litebase/Thread.h"

namespace litebase
{
    namespace details
    {
        class CConVariable;
    }
}

namespace litedb
{
    class CSqlTask;
    class CConnection;

    class CConnectionWorker: public litebase::details::CThread
	{
	public:
        CConnectionWorker(litedb::CConnection* conn, std::queue<litedb::CSqlTask*>* reqQueue,
							litebase::details::CConVariable* condition);
		virtual ~CConnectionWorker();

    private:
		virtual void run();

	private:
        litedb::CConnection* m_conn;
		// 异步调用时的请求队列
		std::queue<litedb::CSqlTask*>*	m_queue;
		litebase::details::CConVariable* m_conditionVar;
	};
}
#endif
