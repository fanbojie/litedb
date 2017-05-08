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

#ifndef LITEDB_MYSQLTASK_H
#define LITEDB_MYSQLTASK_H

#include <string>
#include "SqlTask.h"

namespace litedb
{
	class CMysqlTask: public litedb::CSqlTask
	{
	public:
		CMysqlTask();
		virtual ~CMysqlTask();
        virtual void setCmdText(const std::string& cmd);		
		virtual int execute();
    
    private:
        bool handleError(int err);

	};
}

#endif
