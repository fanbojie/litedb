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

#ifndef LITEDB_MYSQLCONNECTION_H
#define LITEDB_MYSQLCONNECTION_H

#include <string>
#include "mysql.h"
#include "Connection.h"

namespace litedb
{
	class CMysqlConnection: public litedb::CConnection
	{
	public:
		CMysqlConnection();
		virtual ~CMysqlConnection();
		
		virtual void open();
		virtual void close();
        virtual void* getHandle()
        {
            return (void*)m_mysql;
        }
    private:
		MYSQL*	m_mysql;
	};
}
#endif
