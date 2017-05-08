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

#ifndef LITEDB_UTILITY_H
#define LITEDB_UTILITY_H

#include "mysql.h"

namespace litedb
{
    class CUtility
    {
    public:
        static size_t sizeForMysqlType(MYSQL_FIELD* field);
    };
}
#endif
