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
                 `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '����ID', \
                 `LOGIN_NAME` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '��¼����', \
                 `LOGIN_PASS` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '��¼����', \
                 `LOGIN_DATE` datetime DEFAULT NULL COMMENT '����¼ʱ��',    \
                 `LOGIN_IP` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '����¼IP',\
                 `IS_REUSE` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '���ñ��', \
                 `IS_ONLINE` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '����״̬',\
                 `OWNER_CODE` varchar(90) COLLATE utf8_bin NOT NULL COMMENT '��֯����',  \
                 `SORT` bigint(20) unsigned DEFAULT NULL COMMENT '������',  \
                 `STAT` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '״̬', \
                 `USER_PHONE` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '�û��ֻ�����',\
                 `USER_TYPE` tinyint(2) unsigned DEFAULT NULL COMMENT '�û�����',        \
                 `USER_SECURITY_LEV` tinyint(2) unsigned DEFAULT NULL COMMENT '�û���ȫ����',\
                 `CREATE_DATE` datetime DEFAULT NULL COMMENT '��������',  \
                 `USER_HEAD_PIC` char(255) COLLATE utf8_bin DEFAULT NULL COMMENT '�û��Զ���ͼ��', \
                 PRIMARY KEY (`ID`),  \
                 UNIQUE KEY `LOGIN_NAME` (`LOGIN_NAME`)\
                 ) ENGINE=InnoDB AUTO_INCREMENT=1383 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='�û�'";

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
