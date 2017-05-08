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

#ifndef LITEDB_MYSQLRAWREQUEST_H
#define LITEDB_MYSQLRAWREQUEST_H

#include "DatabaseRequest.h"

namespace litedb
{
	class CMysqlRawRequest: public litedb::CDatabaseRequest
	{
	public:
		CMysqlRawRequest();
		virtual ~CMysqlRawRequest();

		virtual litedb::CResultSet* execute();
	};
}
#endif
