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

#ifndef LITEDB_CONNECTIONINFO_H
#define LITEDB_CONNECTIONINFO_H

#include <string>
#include <vector>
#include <stdlib.h>
#include "litebase/Utility.h"

namespace litedb
{
	struct CConnectionInfo
	{
        CConnectionInfo() {};
		explicit CConnectionInfo(const std::string& info)
		{
			std::vector<std::string> connectionStr;
			litebase::utility::CUtility::parseString(info, ";", connectionStr);
			if (connectionStr.size() != 6)
			{
				return;
			}
			
			m_type = atoi(connectionStr[0].c_str());
			m_host = connectionStr[1];
			m_port = connectionStr[2];
			m_user = connectionStr[3];
			m_password = connectionStr[4];
			m_database = connectionStr[5];
		}
		
        CConnectionInfo& operator=(const CConnectionInfo& info)
        {
            m_type = info.m_type;
            m_user = info.m_user;
            m_password = info.m_password;
            m_database = info.m_database;
            m_host = info.m_host;
            m_port = info.m_port;
            return *this;
        }

		int m_type;
		std::string m_user;
		std::string m_password;
		std::string m_database;
		std::string m_host;
		std::string m_port;
	};
}
#endif
