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

#ifndef LITEDB_H
#define LITEDB_H

#include "Config.h"

#ifdef __cplusplus
#define LITEDB_API extern "C" LITEDB_DECL
#else
#define C_API LITEDB_DECL
#endif

namespace litedb
{
    class CSqlTask;
}

// 数据库初始化
// 参数：
//      connStr:连接字符串 "type;host;port;username;password;database"
//      如："1;172.6.1.246;3306;dh;123456;litedb" 其中mysql的type为1
//      size:连接池大小[5-100]
// 返回值：0 成功 -1 失败
LITEDB_API int litedb_init(const char* connStr, int size);

// 关闭数据库
LITEDB_API void litedb_uninit();

// 创建sql任务
// 参数：
//      type为任务类型，同步任务为0,异步任务为1
LITEDB_API litedb::CSqlTask* litedb_create_task(int type);

// 异步调用情况下，push任务到调度队列
LITEDB_API void litedb_push_task(litedb::CSqlTask* task);

#endif
