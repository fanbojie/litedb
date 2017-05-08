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

#ifndef LITEDB_BASEDEFINE_H
#define LITEDB_BASEDEFINE_H

namespace litedb
{
	namespace DB_TYPE
	{
		enum
		{
			TYPE_SQLITE3,
			TYPE_MYSQL,
			TYPE_ORACLE,
			TYPE_ODBC,
			TYPE_POSTGRESQL,
			TYPE_DB2,
		};
	}

	namespace REQ_TYPE
	{
		enum
		{
			TYPE_RAW,
			TYPE_PREPARED,
            TYPE_PING,		
		};
	}

    namespace TASK_TYPE
    {
        enum
        {
            TYPE_SYNC,
            TYPE_ASYNC,
        };
    }
}
#endif
