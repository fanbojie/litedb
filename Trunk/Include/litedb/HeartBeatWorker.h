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

#ifndef LITEDB_HEARTBEATWORKER_H
#define LITEDB_HEARTBEATWORKER_H

#include "litebase/Thread.h"

namespace litedb
{
    class CConnectionPool;
    class CHeartBeatWorker: public litebase::details::CThread
    {
    public:
        CHeartBeatWorker(litedb::CConnectionPool* pool);
        virtual ~CHeartBeatWorker();

    private:
        virtual void run();
    private:
        litedb::CConnectionPool* m_pool;
    };
}
#endif
