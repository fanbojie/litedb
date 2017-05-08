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

#ifndef LITEDB_ERROR_H
#define LITEDB_ERROR_H

#include "Config.h"
#include <stdexcept>
#include <string>

namespace litedb
{
	class LITEDB_DECL CLiteDBError: public std::runtime_error
	{
	public:
		explicit CLiteDBError(const std::string& msg);
	};
}
#endif
