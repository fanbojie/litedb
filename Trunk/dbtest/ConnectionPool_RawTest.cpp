#include "gtest/gtest.h"
#include "litedb/ConnectionPool.h"
#include "litedb/SqlTask.h"
#include "litedb/ResultSet.h"
#include "litedb/BaseDefine.h"
#include "litedb/Litedb.h"
#include <string>

using namespace std;
using namespace litedb;

class CConnectionPool_function: public testing::Test
{
protected:

    static void SetUpTestCase()
    {
        printf("Set up ConnectionPool Test...\n");
    }
    static void TearDownTestCase()
    {
        printf("TearDown ConnectionPool Test...\n");
    }
};

TEST_F(CConnectionPool_function, createTable_sync)
{    
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
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

    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 0);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 0);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, insertTable_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
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
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 0);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, selectTable_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

     string cmd = "select * from sys_user";
//    string cmd= "select ID, LOGIN_NAME, LOGIN_PASS from sys_user";

    pTask->setCmdText(cmd);
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 15);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int id = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(id, 1);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "system01");
        string pass = pResult->getFieldAsString("LOGIN_PASS");
        EXPECT_STREQ(pass.c_str(), "11d01e035210098d0abc2c4bb16187a8");
        string loginDate = pResult->getFieldAsString("LOGIN_DATE");
        EXPECT_STREQ(loginDate.c_str(), "2013-08-26 10:35:43");
        string ip = pResult->getFieldAsString("LOGIN_IP");
        EXPECT_STREQ(ip.c_str(), "");
        int reuse = pResult->getFieldAsInt32("IS_REUSE");
        EXPECT_EQ(reuse, 0);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string ownerCode = pResult->getFieldAsString("OWNER_CODE");
        EXPECT_STREQ(ownerCode.c_str(), "001");
        int sort = pResult->getFieldAsInt32("SORT");
        EXPECT_EQ(sort, 0);
        int stat = pResult->getFieldAsInt32("STAT");
        EXPECT_EQ(stat, 1);
        string phone = pResult->getFieldAsString("USER_PHONE");
        EXPECT_STREQ(phone.c_str(), "12345678901");
        int userType = pResult->getFieldAsInt32("USER_TYPE");
        EXPECT_EQ(userType, 0);
        int userLevel = pResult->getFieldAsInt32("USER_SECURITY_LEV");
        EXPECT_EQ(userLevel, 0);
        string createDate = pResult->getFieldAsString("CREATE_DATE");
        EXPECT_STREQ(createDate.c_str(), "2013-08-10 17:23:50");
        string userHeadPic = pResult->getFieldAsString("USER_HEAD_PIC");
        EXPECT_STREQ(userHeadPic.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, insertTable1_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "INSERT INTO `sys_user` VALUES ('2', 'ak123456', \
                 'e10adc3949ba59abbe56e057f20f883e', null, null, '0',\
                 '0', '001', null, '1', '13777904866', null, null, \
                 '2013-08-10 19:19:24', null);";

    pTask->setCmdText(cmd);
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 0);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, selectTable1_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "select * from sys_user";

    pTask->setCmdText(cmd);
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 15);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 2);
        int id = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(id, 1);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "system01");
        string pass = pResult->getFieldAsString("LOGIN_PASS");
        EXPECT_STREQ(pass.c_str(), "11d01e035210098d0abc2c4bb16187a8");
        string loginData = pResult->getFieldAsString("LOGIN_DATE");
        EXPECT_STREQ(loginData.c_str(), "2013-08-26 10:35:43");
        string ip = pResult->getFieldAsString("LOGIN_IP");
        EXPECT_STREQ(ip.c_str(), "");
        int reuse = pResult->getFieldAsInt32("IS_REUSE");
        EXPECT_EQ(reuse, 0);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string ownerCode = pResult->getFieldAsString("OWNER_CODE");
        EXPECT_STREQ(ownerCode.c_str(), "001");
        int sort = pResult->getFieldAsInt32("SORT");
        EXPECT_EQ(sort, 0);
        int stat = pResult->getFieldAsInt32("STAT");
        EXPECT_EQ(stat, 1);
        string phone = pResult->getFieldAsString("USER_PHONE");
        EXPECT_STREQ(phone.c_str(), "12345678901");
        int userType = pResult->getFieldAsInt32("USER_TYPE");
        EXPECT_EQ(userType, 0);
        int userLevel = pResult->getFieldAsInt32("USER_SECURITY_LEV");
        EXPECT_EQ(userLevel, 0);
        string createDate = pResult->getFieldAsString("CREATE_DATE");
        EXPECT_STREQ(createDate.c_str(), "2013-08-10 17:23:50");
        string userHeadPic = pResult->getFieldAsString("USER_HEAD_PIC");
        EXPECT_STREQ(userHeadPic.c_str(), "");
        while (pResult->nextRow())
        {
            int id = pResult->getFieldAsInt32("ID");
            EXPECT_EQ(id, 2);
            string name = pResult->getFieldAsString("LOGIN_NAME");
            EXPECT_STREQ(name.c_str(), "ak123456");
            string pass = pResult->getFieldAsString("LOGIN_PASS");
            EXPECT_STREQ(pass.c_str(), "e10adc3949ba59abbe56e057f20f883e");
            string loginData = pResult->getFieldAsString("LOGIN_DATE");
            EXPECT_STREQ(loginData.c_str(), "");
            string ip = pResult->getFieldAsString("LOGIN_IP");
            EXPECT_STREQ(ip.c_str(), "");
            int reuse = pResult->getFieldAsInt32("IS_REUSE");
            EXPECT_EQ(reuse, 0);
            int online = pResult->getFieldAsInt32("IS_ONLINE");
            EXPECT_EQ(online, 0);
            string ownerCode = pResult->getFieldAsString("OWNER_CODE");
            EXPECT_STREQ(ownerCode.c_str(), "001");
            int sort = pResult->getFieldAsInt32("SORT");
            EXPECT_EQ(sort, 0);
            int stat = pResult->getFieldAsInt32("STAT");
            EXPECT_EQ(stat, 1);
            string phone = pResult->getFieldAsString("USER_PHONE");
            EXPECT_STREQ(phone.c_str(), "13777904866");
            int userType = pResult->getFieldAsInt32("USER_TYPE");
            EXPECT_EQ(userType, 0);
            int userLevel = pResult->getFieldAsInt32("USER_SECURITY_LEV");
            EXPECT_EQ(userLevel, 0);
            string createDate = pResult->getFieldAsString("CREATE_DATE");
            EXPECT_STREQ(createDate.c_str(), "2013-08-10 19:19:24");
            string userHeadPic = pResult->getFieldAsString("USER_HEAD_PIC");
            EXPECT_STREQ(userHeadPic.c_str(), "");
        }
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, deleteTable_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "DELETE from sys_user where id = 1";
//    string cmd = "DELETE from sys_user";
    pTask->setCmdText(cmd);
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 0);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, selectTable2_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "select * from sys_user where ID=1";

    pTask->setCmdText(cmd);
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 15);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 0);
        int id = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(id, 0);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "");
        string pass = pResult->getFieldAsString("LOGIN_PASS");
        EXPECT_STREQ(pass.c_str(), "");
        string loginData = pResult->getFieldAsString("LOGIN_DATE");
        EXPECT_STREQ(loginData.c_str(), "");
        string ip = pResult->getFieldAsString("LOGIN_IP");
        EXPECT_STREQ(ip.c_str(), "");
        int reuse = pResult->getFieldAsInt32("IS_REUSE");
        EXPECT_EQ(reuse, 0);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string ownerCode = pResult->getFieldAsString("OWNER_CODE");
        EXPECT_STREQ(ownerCode.c_str(), "");
        int sort = pResult->getFieldAsInt32("SORT");
        EXPECT_EQ(sort, 0);
        int stat = pResult->getFieldAsInt32("STAT");
        EXPECT_EQ(stat, 0);
        string phone = pResult->getFieldAsString("USER_PHONE");
        EXPECT_STREQ(phone.c_str(), "");
        int userType = pResult->getFieldAsInt32("USER_TYPE");
        EXPECT_EQ(userType, 0);
        int userLevel = pResult->getFieldAsInt32("USER_SECURITY_LEV");
        EXPECT_EQ(userLevel, 0);
        string createDate = pResult->getFieldAsString("CREATE_DATE");
        EXPECT_STREQ(createDate.c_str(), "");
        string userHeadPic = pResult->getFieldAsString("USER_HEAD_PIC");
        EXPECT_STREQ(userHeadPic.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, selectTable3_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "select * from sys_user where ID=2";

    pTask->setCmdText(cmd);
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 15);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int id = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(id, 2);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "ak123456");
        string pass = pResult->getFieldAsString("LOGIN_PASS");
        EXPECT_STREQ(pass.c_str(), "e10adc3949ba59abbe56e057f20f883e");
        string loginData = pResult->getFieldAsString("LOGIN_DATE");
        EXPECT_STREQ(loginData.c_str(), "");
        string ip = pResult->getFieldAsString("LOGIN_IP");
        EXPECT_STREQ(ip.c_str(), "");
        int reuse = pResult->getFieldAsInt32("IS_REUSE");
        EXPECT_EQ(reuse, 0);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string ownerCode = pResult->getFieldAsString("OWNER_CODE");
        EXPECT_STREQ(ownerCode.c_str(), "001");
        int sort = pResult->getFieldAsInt32("SORT");
        EXPECT_EQ(sort, 0);
        int stat = pResult->getFieldAsInt32("STAT");
        EXPECT_EQ(stat, 1);
        string phone = pResult->getFieldAsString("USER_PHONE");
        EXPECT_STREQ(phone.c_str(), "13777904866");
        int userType = pResult->getFieldAsInt32("USER_TYPE");
        EXPECT_EQ(userType, 0);
        int userLevel = pResult->getFieldAsInt32("USER_SECURITY_LEV");
        EXPECT_EQ(userLevel, 0);
        string createDate = pResult->getFieldAsString("CREATE_DATE");
        EXPECT_STREQ(createDate.c_str(), "2013-08-10 19:19:24");
        string userHeadPic = pResult->getFieldAsString("USER_HEAD_PIC");
        EXPECT_STREQ(userHeadPic.c_str(), ""); 
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_function, dropTable_sync)
{
    CSqlTask* pTask = litedb_create_task(TASK_TYPE::TYPE_SYNC);
    if (pTask != NULL)
    {
        EXPECT_EQ(0, 0);
    }
    else
    {
        EXPECT_EQ(0, -1);
    }

    string cmd = "drop Table sys_user";
    pTask->setCmdText(cmd);

    int result = pTask->execute();
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 0);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 0);
        int online = pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string name = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(name.c_str(), "");
    }

    pTask->release();
}
