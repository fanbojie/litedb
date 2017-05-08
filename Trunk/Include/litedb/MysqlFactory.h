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

#ifndef LITEDB_MYSQLFACTORY_H
#define LITEDB_MYSQLFACTORY_H

#include "DatabaseFactory.h"

namespace litedb
{
	class CMysqlFactory: public litedb::CDatabaseFactory
	{
	public:
		CMysqlFactory();
		virtual ~CMysqlFactory();
		
		virtual litedb::CConnection* createConnection();
		virtual litedb::CDatabaseRequest* createRequest(int type);
		virtual litedb::CSqlTask* createTask();
	};
}
#endif
