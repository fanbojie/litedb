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

#ifndef LITEDB_MYSQLPINGREQUEST_H
#define LITEDB_MYSQLPINGREQUEST_H

#include "DatabaseRequest.h"

namespace litedb
{
    class CMysqlPingRequest: public litedb::CDatabaseRequest
    {
    public:
        CMysqlPingRequest();
        virtual ~CMysqlPingRequest();

        virtual litedb::CResultSet* execute();
    };
}
#endif
