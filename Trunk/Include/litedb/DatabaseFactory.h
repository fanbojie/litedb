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

#ifndef LITEDB_DATABASEFACTORY_H
#define LITEDB_DATABASEFACTORY_H

#include "litebase/Noncopyable.h"

namespace litedb
{
    class CConnection;
    class CDatabaseRequest;
    class CSqlTask;

	// ���󹤳���ÿһ�����ݿⶼ���Լ��Ĺ���������������ض���
	class CDatabaseFactory: public litebase::details::CNoncopyable
	{
	public:
        CDatabaseFactory() {};
        virtual ~CDatabaseFactory() {};
		virtual litedb::CConnection* createConnection() = 0;
		virtual litedb::CDatabaseRequest* createRequest(int type) = 0;
		virtual litedb::CSqlTask* createTask() = 0;
	};
}
#endif
