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

// ���ݿ��ʼ��
// ������
//      connStr:�����ַ��� "type;host;port;username;password;database"
//      �磺"1;172.6.1.246;3306;dh;123456;litedb" ����mysql��typeΪ1
//      size:���ӳش�С[5-100]
// ����ֵ��0 �ɹ� -1 ʧ��
LITEDB_API int litedb_init(const char* connStr, int size);

// �ر����ݿ�
LITEDB_API void litedb_uninit();

// ����sql����
// ������
//      typeΪ�������ͣ�ͬ������Ϊ0,�첽����Ϊ1
LITEDB_API litedb::CSqlTask* litedb_create_task(int type);

// �첽��������£�push���񵽵��ȶ���
LITEDB_API void litedb_push_task(litedb::CSqlTask* task);

#endif
