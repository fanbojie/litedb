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

#ifndef	LITEBASE_UTILITY_H
#define LITEBASE_UTILITY_H

#include "Config.h"
#include <string>
#include <vector>

namespace litebase
{
	namespace utility
	{
		class LITEBASE_DECL CUtility
		{
		public:
			static void parseString(const std::string& str, const std::string& token, std::vector<std::string> &retValue);
			static std::string int2Str(int integer);
            static void splitString(const std::string& str, const std::string &endStr, const std::string& delims, std::vector<std::string> &retValue);
		};
	}
}
#endif
