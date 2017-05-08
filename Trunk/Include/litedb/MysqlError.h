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

#ifndef LITEDB_MYSQLERROR_H
#define LITEDB_MYSQLERROR_H

#include <string>
#include "Error.h"

namespace litedb
{
	class CMysqlError: public CLiteDBError
	{
	public:
		CMysqlError(const std::string& msg, int errNum)
			: CLiteDBError(msg), m_errNum(errNum)
		{}
		unsigned int m_errNum;
	};

}
#endif
