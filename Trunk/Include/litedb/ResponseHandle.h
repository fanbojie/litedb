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

#ifndef LITEDB_RESPONSEHANDLE_H
#define LITEDB_RESPONSEHANDLE_H

namespace litedb
{
	class LITEDB_DECL CResponseHandle
	{
	public:
		CResponseHandle();
		virtual ~CResponseHandle();

        virtual void sendRequestReply(litedb::CResultSet* resultSet)
	};
}
#endif
