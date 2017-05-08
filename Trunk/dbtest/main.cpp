#include <string>
#include <unistd.h>
// #include "litedb/ConnectionPool.h"
#include "litedb/SqlTask.h"
#include "litedb/ResultSet.h"
#include "litedb/BaseDefine.h"
#include "litedb/Litedb.h"
#include "gtest/gtest.h"

using namespace litedb;
using namespace std;

class GlobalEnviroment : public testing::Environment
{
public:
	virtual void SetUp()
	{
        /*int thread_num = 64;
        int thread_recv_priority = 1;

        Dahua::NetFramework::CNetThread::SetRcvPriority( thread_recv_priority );
        Dahua::NetFramework::CNetThread::CreateThreadPool( thread_num, true );*/
	}

	virtual void TearDown()
	{
		printf("Litedb Test End.....\n");
	}
};

int main(int argc, char **argv)
{
    int ret = litedb_init("1;172.26.1.24;3306;dh;123456;litedb", 5);
    if (ret != 0)
    {
        printf("init litedb error.\n");
        return ret;
    }
    
    testing::AddGlobalTestEnvironment(new GlobalEnviroment);
    testing::InitGoogleTest(&argc, argv);
    int times = 0;
    while(1)
    {
//         if (times > 1000)
//         {
//             break;
//         }

        ret = RUN_ALL_TESTS();
        sleep(10);
        break;
    }

    times = 0;
    while(1)
    {
        ret = RUN_ALL_TESTS();
        sleep(30000);
    }




//     string cmd = "CREATE TABLE `sys_user` ( \
//                  `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '自增ID', \
//                  `LOGIN_NAME` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '登录名称', \
//                  `LOGIN_PASS` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '登录密码', \
//                  `LOGIN_DATE` datetime DEFAULT NULL COMMENT '最后登录时间',    \
//                  `LOGIN_IP` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '最后登录IP',\
//                  `IS_REUSE` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '复用标记', \
//                  `IS_ONLINE` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '在线状态',\
//                  `OWNER_CODE` varchar(90) COLLATE utf8_bin NOT NULL COMMENT '组织编码',  \
//                  `SORT` bigint(20) unsigned DEFAULT NULL COMMENT '排序码',  \
//                  `STAT` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '状态', \
//                  `USER_PHONE` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '用户手机号码',\
//                  `USER_TYPE` tinyint(2) unsigned DEFAULT NULL COMMENT '用户类型',        \
//                  `USER_SECURITY_LEV` tinyint(2) unsigned DEFAULT NULL COMMENT '用户安全级别',\
//                  `CREATE_DATE` datetime DEFAULT NULL COMMENT '创建日期',  \
//                  `USER_HEAD_PIC` char(255) COLLATE utf8_bin DEFAULT NULL COMMENT '用户自定义图像', \
//                  PRIMARY KEY (`ID`),  \
//                  UNIQUE KEY `LOGIN_NAME` (`LOGIN_NAME`)\
//                  ) ENGINE=InnoDB AUTO_INCREMENT=1383 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='用户'";
// 
//     // 同步操作
//     CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
//     if (pTask != NULL)
//     {
//         pTask->setCmdText(cmd);
//         int exeResult = pTask->execute();
//         if (exeResult != 0)
//         {
//             printf("execute task failed.\n");
//         }
// 
//         pTask->release();
//         pTask = NULL;
//     }
// 
//     cmd = "INSERT INTO `sys_user` VALUES \
//           ('1', 'system01', '11d01e035210098d0abc2c4bb16187a8', \
//           '2013-08-26 10:35:43', null, '0', '0', '001', null, '1', \
//           '12345678901', null, null, '2013-08-10 17:23:50', null)";
// 
// 
//     // 异步操作
//     pTask = litedb_create_task(TASK_TYPE::TYPE_ASYNC);
//     if (pTask != NULL)
//     {
//         pTask->setCmdText(cmd);
//         litedb_push_task(pTask);
//     }

    litedb_uninit();
    return 0;
}

