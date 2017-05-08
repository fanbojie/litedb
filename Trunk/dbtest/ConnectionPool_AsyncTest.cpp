#include "gtest/gtest.h"
#include "litedb/ConnectionPool.h"
#include "litedb/SqlTask.h"
#include "litedb/ResultSet.h"
#include "litedb/BaseDefine.h"
#include "litedb/Litedb.h"
#include <string>

using namespace std;
using namespace litedb;

class CConnectionPool_Asyncfunction: public testing::Test
{
protected:

    static void SetUpTestCase()
    {
        printf("Set up ConnectionPool Async Test...\n");
    }
    static void TearDownTestCase()
    {
        printf("TearDown ConnectionPool Async Test...\n");
    }
};

TEST_F(CConnectionPool_Asyncfunction, createTable_async)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_ASYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "CREATE TABLE `sys_user` ( \
                 `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '自增ID', \
                 `LOGIN_NAME` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '登录名称', \
                 `LOGIN_PASS` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '登录密码', \
                 `LOGIN_DATE` datetime DEFAULT NULL COMMENT '最后登录时间',    \
                 `LOGIN_IP` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '最后登录IP',\
                 `IS_REUSE` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '复用标记', \
                 `IS_ONLINE` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '在线状态',\
                 `OWNER_CODE` varchar(90) COLLATE utf8_bin NOT NULL COMMENT '组织编码',  \
                 `SORT` bigint(20) unsigned DEFAULT NULL COMMENT '排序码',  \
                 `STAT` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '状态', \
                 `USER_PHONE` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '用户手机号码',\
                 `USER_TYPE` tinyint(2) unsigned DEFAULT NULL COMMENT '用户类型',        \
                 `USER_SECURITY_LEV` tinyint(2) unsigned DEFAULT NULL COMMENT '用户安全级别',\
                 `CREATE_DATE` datetime DEFAULT NULL COMMENT '创建日期',  \
                 `USER_HEAD_PIC` char(255) COLLATE utf8_bin DEFAULT NULL COMMENT '用户自定义图像', \
                 PRIMARY KEY (`ID`),  \
                 UNIQUE KEY `LOGIN_NAME` (`LOGIN_NAME`)\
                 ) ENGINE=InnoDB AUTO_INCREMENT=1383 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='用户'";

    pTask->setCmdText(cmd);
    litedb_push_task(pTask);
}

TEST_F(CConnectionPool_Asyncfunction, insertTable_async)
{
    sleep(3);
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_ASYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "INSERT INTO `sys_user` VALUES \
                 ('1', 'system01', '11d01e035210098d0abc2c4bb16187a8', \
                 '2013-08-26 10:35:43', null, '0', '0', '001', null, '1', \
                 '12345678901', null, null, '2013-08-10 17:23:50', null)";

    pTask->setCmdText(cmd);
    litedb_push_task(pTask);
}

TEST_F(CConnectionPool_Asyncfunction, dropTable_async)
{
    sleep(5);
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_ASYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "drop table sys_user";

    pTask->setCmdText(cmd);
    litedb_push_task(pTask);
}
