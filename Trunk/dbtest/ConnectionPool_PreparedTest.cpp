#include "gtest/gtest.h"
#include "litedb/ConnectionPool.h"
#include "litedb/SqlTask.h"
#include "litedb/ResultSet.h"
#include "litedb/BaseDefine.h"
#include "litedb/Litedb.h"
#include <string>

using namespace std;
using namespace litedb;

class CConnectionPool_Preparedfunction: public testing::Test
{
protected:

    static void SetUpTestCase()
    {
        printf("Set up ConnectionPool Prepared Test...\n");
    }
    static void TearDownTestCase()
    {
        printf("TearDown ConnectionPool Prepared Test...\n");
    }
};


TEST_F(CConnectionPool_Preparedfunction, createTable_sync)
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

    string cmd = "CREATE TABLE `adm_dev` ( \
        `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '自增ID', \
        `DEVICE_CODE` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '设备编码', \
        `DEVICE_NAME` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '设备名称',  \
        `DEVICE_SN` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '设备标识码',\
        `DEVICE_CATEGORY` tinyint(3) NOT NULL COMMENT '设备种类',     \
        `DEVICE_TYPE` varchar(10) COLLATE utf8_bin NOT NULL COMMENT '设备类型',  \
        `DEVICE_MANUFACTURER` varchar(10) COLLATE utf8_bin DEFAULT NULL COMMENT '设备厂商', \
        `DEVICE_MODEL` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '设备型号',\
        `DEVICE_IP` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '设备地址',\
        `DEVICE_PORT` smallint(5) unsigned DEFAULT NULL COMMENT '设备端口',  \
        `OWNER_CODE` varchar(90) COLLATE utf8_bin NOT NULL COMMENT '所属编码',  \
        `DOMAIN_ID` bigint(20) unsigned DEFAULT NULL COMMENT '域ID', \
        `UNIT_NUM` tinyint(3) unsigned DEFAULT NULL COMMENT '单元数',    \
        `LOGIN_TYPE` varchar(10) COLLATE utf8_bin NOT NULL COMMENT '登入类型', \
        `LOGIN_NAME` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '登录名称', \
        `LOGIN_PASSWORD` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '登录密码',\
        `REGIST_SERVICE_ID` bigint(20) unsigned DEFAULT NULL COMMENT '主动注册服务ID',  \
        `REGIST_PROXY_PORT` smallint(5) unsigned DEFAULT NULL COMMENT '主动注册代理端口', \
        `REGIST_DEVICE_CODE` varchar(50) COLLATE utf8_bin DEFAULT NULL COMMENT '主动注册设备编码',  \
        `MEMO` varchar(255) COLLATE utf8_bin DEFAULT NULL COMMENT '描述',\
        `SORT` bigint(20) unsigned DEFAULT NULL COMMENT '排序码',    \
        `IS_ONLINE` tinyint(3) unsigned DEFAULT '0' COMMENT '在线状态',\
        `CREATE_DATE` datetime DEFAULT NULL COMMENT '创建日期',    \
        `CREATE_USER_ID` bigint(20) unsigned DEFAULT NULL COMMENT '创建用户ID',  \
        `UPDATE_DATE` datetime DEFAULT NULL COMMENT '修改日期', \
        `UPDATE_USER_ID` bigint(20) unsigned DEFAULT NULL COMMENT '修改用户ID', \
        `DMS_IP` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '分配给设备登陆的DMS的IP', \
        `DMS_AUTO_CONN_PORT` smallint(5) NOT NULL COMMENT '分配给设备登陆的DMS的端口',\
        `DMS_CLIENT_PORT` smallint(5) NOT NULL COMMENT 'DMS客户端口',  \
        `DMS_ID` varchar(50) COLLATE utf8_bin NOT NULL COMMENT 'DMS的ID', \
        `ADS_IP` varchar(50) COLLATE utf8_bin NOT NULL COMMENT '分配给设备登陆的ADS的IP',\
        `ADS_PORT` smallint(5) NOT NULL COMMENT '分配给设备登陆的ADS的端口', \
        `ADS_ID` varchar(50) COLLATE utf8_bin NOT NULL COMMENT 'ADS的ID',\
        `ABILITY` varchar(4000) COLLATE utf8_bin DEFAULT NULL COMMENT '设备属性',\
        `VERSION_SN` varchar(200) CHARACTER SET utf8 DEFAULT NULL COMMENT '版本号', \
        `DEFINDSTATE_TEMPLATE` varchar(20) COLLATE utf8_bin DEFAULT '1,0' COMMENT '用户设定默认布防状态记录',\
        `IDENTIFY_CODE` varchar(255) COLLATE utf8_bin DEFAULT NULL COMMENT '设备验证码', \
        `SCENE_MODES` varchar(4000) COLLATE utf8_bin DEFAULT '[{\"Mode\":\"nervous\",\"Period\":\"Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday\",\"BeginTime\":\"00:00:00\",\"EndTime\":\"23:59:59\"}]' COMMENT '设备情景模式的配置',  \
        PRIMARY KEY (`ID`)\
        ) ENGINE=InnoDB AUTO_INCREMENT=978 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='设备'";

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
        int online = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(online, 0);
        string name = pResult->getFieldAsString("DEVICE_CODE");
        EXPECT_STREQ(name.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_Preparedfunction, insertTable_sync)
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

    string cmd = "INSERT INTO `adm_dev` VALUES \
                 (?, ?, 'PZC3GW33300019', 'PZC3GW33300019',\
                 ?, 'IPC-36X', '16777216', 'HS-P100W', '192.168.1.137', \
                 ?, '0', ?, null, '0', '', '', null, null, null, \
                 null, null, '0', '2013-08-12 09:46:39', null, \
                 '2014-01-22 14:10:16', null, '112.124.4.112', '8682',\
                 '9202', '', '10.33.6.237', '9300', '4001', \
                 'AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P', \
                 'Chn_P_v2.211.0001.1.R.20131226', '1,0', null, \
                 ?)";

    pTask->setCmdText(cmd);
    pTask->setParamAsUInt64(0, 1);
    pTask->setParamAsString(1, "PZC3GW33300019");
    pTask->setParamAsInt32(2, 0);
    pTask->setParamAsInt32(3, 37777);
    pTask->setParamAsNull(4);
    pTask->setParamAsString(5, "[{\"Mode\":\"nervous\",\"Period\":\"Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday\", \
\"BeginTime\":\"00:00:00\",\"EndTime\":\"23:59:59\"}]");

    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 0);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int online = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(online, 0);
        string name = pResult->getFieldAsString("DEVICE_CODE");
        EXPECT_STREQ(name.c_str(), "");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_Preparedfunction, selectTable_sync)
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

    string cmd = "select * from adm_dev t where t.ID=?";

    pTask->setCmdText(cmd);
    pTask->setParamAsInt32(0, 1);

    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 38);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int id = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(id, 1);
        string deviceCode = pResult->getFieldAsString("DEVICE_CODE");
        EXPECT_STREQ(deviceCode.c_str(), "PZC3GW33300019");
        string deviceName = pResult->getFieldAsString("DEVICE_NAME");
        EXPECT_STREQ(deviceName.c_str(), "PZC3GW33300019"); 
        string deviceSN = pResult->getFieldAsString("DEVICE_SN");
        EXPECT_STREQ(deviceSN.c_str(), "PZC3GW33300019"); 
        int category = pResult->getFieldAsInt32("DEVICE_CATEGORY");
        EXPECT_EQ(category, 0);
        string deviceType = pResult->getFieldAsString("DEVICE_TYPE");
        EXPECT_STREQ(deviceType.c_str(), "IPC-36X"); 
        string deviceManu = pResult->getFieldAsString("DEVICE_MANUFACTURER");
        EXPECT_STREQ(deviceManu.c_str(), "16777216"); 
        string deviceModel = pResult->getFieldAsString("DEVICE_MODEL");
        EXPECT_STREQ(deviceModel.c_str(), "HS-P100W");
        string deviceIP = pResult->getFieldAsString("DEVICE_IP");
        EXPECT_STREQ(deviceIP.c_str(), "192.168.1.137");
        int devicePort = pResult->getFieldAsInt32("DEVICE_PORT");
        EXPECT_EQ(devicePort, 37777);
        string ownerCode = pResult->getFieldAsString("OWNER_CODE");
        EXPECT_STREQ(ownerCode.c_str(), "0");
        int domainId = pResult->getFieldAsInt32("DOMAIN_ID");
        EXPECT_EQ(domainId, 0);
        int unitNum = pResult->getFieldAsInt32("UNIT_NUM");
        EXPECT_EQ(unitNum, 0);
        string loginType = pResult->getFieldAsString("LOGIN_TYPE");
        EXPECT_STREQ(loginType.c_str(), "0");
        string loginName = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(loginName.c_str(), "");
        string loginPasswd = pResult->getFieldAsString("LOGIN_PASSWORD");
        EXPECT_STREQ(loginPasswd.c_str(), "");
        int registerId = pResult->getFieldAsInt32("REGIST_SERVICE_ID");
        EXPECT_EQ(registerId, 0);
        int registerPort = pResult->getFieldAsInt32("REGIST_PROXY_PORT");
        EXPECT_EQ(registerPort, 0);
        string registerDeviceCode = pResult->getFieldAsString("REGIST_DEVICE_CODE");
        EXPECT_STREQ(registerDeviceCode.c_str(), "");
        string memo = pResult->getFieldAsString("MEMO");
        EXPECT_STREQ(memo.c_str(), "");
        int sort = pResult->getFieldAsInt32("SORT");
        EXPECT_EQ(sort, 0);
        int online= pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
//         string createDate = pResult->getFieldAsString("CREATE_DATE");
//         EXPECT_STREQ(createDate.c_str(), "2013-08-12 09:46:39");
        int createUserId = pResult->getFieldAsInt32("CREATE_USER_ID");
        EXPECT_EQ(createUserId, 0);
//         string updateDate = pResult->getFieldAsString("UPDATE_DATE");
//         EXPECT_STREQ(updateDate.c_str(), "2014-01-22 14:10:16");
        int updateUserId = pResult->getFieldAsInt32("UPDATE_USER_ID");
        EXPECT_EQ(updateUserId, 0);
        string dmsIp = pResult->getFieldAsString("DMS_IP");
        EXPECT_STREQ(dmsIp.c_str(), "112.124.4.112");
        int dmsConnPort = pResult->getFieldAsInt32("DMS_AUTO_CONN_PORT");
        EXPECT_EQ(dmsConnPort, 8682);
        int dmsClientPort = pResult->getFieldAsInt32("DMS_CLIENT_PORT");
        EXPECT_EQ(dmsClientPort, 9202);
        string dmsId = pResult->getFieldAsString("DMS_ID");
        EXPECT_STREQ(dmsId.c_str(), "");
        string adsIp = pResult->getFieldAsString("ADS_IP");
        EXPECT_STREQ(adsIp.c_str(), "10.33.6.237");
        int adsPort = pResult->getFieldAsInt32("ADS_PORT");
        EXPECT_EQ(adsPort, 9300);
        string adsId = pResult->getFieldAsString("ADS_ID");
        EXPECT_STREQ(adsId.c_str(), "4001");
        string ability = pResult->getFieldAsString("ABILITY");
        EXPECT_STREQ(ability.c_str(), "AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P");
        string version = pResult->getFieldAsString("VERSION_SN");
        EXPECT_STREQ(version.c_str(), "Chn_P_v2.211.0001.1.R.20131226");
        string defineTemplate = pResult->getFieldAsString("DEFINDSTATE_TEMPLATE");
        EXPECT_STREQ(defineTemplate.c_str(), "1,0");
        string idCode = pResult->getFieldAsString("IDENTIFY_CODE");
        EXPECT_STREQ(idCode.c_str(), "");
        string scene = pResult->getFieldAsString("SCENE_MODES");
        EXPECT_STREQ(scene.c_str(), "[{\"Mode\":\"nervous\",\"Period\":\"Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday\", \
\"BeginTime\":\"00:00:00\",\"EndTime\":\"23:59:59\"}]");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_Preparedfunction, selectTable1_sync)
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

    string cmd = "select * from adm_dev";

    pTask->setCmdText(cmd);
    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 38);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int id = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(id, 1);
        string deviceCode = pResult->getFieldAsString("DEVICE_CODE");
        EXPECT_STREQ(deviceCode.c_str(), "PZC3GW33300019");
        string deviceName = pResult->getFieldAsString("DEVICE_NAME");
        EXPECT_STREQ(deviceName.c_str(), "PZC3GW33300019"); 
        string deviceSN = pResult->getFieldAsString("DEVICE_SN");
        EXPECT_STREQ(deviceSN.c_str(), "PZC3GW33300019"); 
        int category = pResult->getFieldAsInt32("DEVICE_CATEGORY");
        EXPECT_EQ(category, 0);
        string deviceType = pResult->getFieldAsString("DEVICE_TYPE");
        EXPECT_STREQ(deviceType.c_str(), "IPC-36X"); 
        string deviceManu = pResult->getFieldAsString("DEVICE_MANUFACTURER");
        EXPECT_STREQ(deviceManu.c_str(), "16777216"); 
        string deviceModel = pResult->getFieldAsString("DEVICE_MODEL");
        EXPECT_STREQ(deviceModel.c_str(), "HS-P100W");
        string deviceIP = pResult->getFieldAsString("DEVICE_IP");
        EXPECT_STREQ(deviceIP.c_str(), "192.168.1.137");
        int devicePort = pResult->getFieldAsInt32("DEVICE_PORT");
        EXPECT_EQ(devicePort, 37777);
        string ownerCode = pResult->getFieldAsString("OWNER_CODE");
        EXPECT_STREQ(ownerCode.c_str(), "0");
        int domainId = pResult->getFieldAsInt32("DOMAIN_ID");
        EXPECT_EQ(domainId, 0);
        int unitNum = pResult->getFieldAsInt32("UNIT_NUM");
        EXPECT_EQ(unitNum, 0);
        string loginType = pResult->getFieldAsString("LOGIN_TYPE");
        EXPECT_STREQ(loginType.c_str(), "0");
        string loginName = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(loginName.c_str(), "");
        string loginPasswd = pResult->getFieldAsString("LOGIN_PASSWORD");
        EXPECT_STREQ(loginPasswd.c_str(), "");
        int registerId = pResult->getFieldAsInt32("REGIST_SERVICE_ID");
        EXPECT_EQ(registerId, 0);
        int registerPort = pResult->getFieldAsInt32("REGIST_PROXY_PORT");
        EXPECT_EQ(registerPort, 0);
        string registerDeviceCode = pResult->getFieldAsString("REGIST_DEVICE_CODE");
        EXPECT_STREQ(registerDeviceCode.c_str(), "");
        string memo = pResult->getFieldAsString("MEMO");
        EXPECT_STREQ(memo.c_str(), "");
        int sort = pResult->getFieldAsInt32("SORT");
        EXPECT_EQ(sort, 0);
        int online= pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        string createDate = pResult->getFieldAsString("CREATE_DATE");
        EXPECT_STREQ(createDate.c_str(), "2013-08-12 09:46:39");
        int createUserId = pResult->getFieldAsInt32("CREATE_USER_ID");
        EXPECT_EQ(createUserId, 0);
        string updateDate = pResult->getFieldAsString("UPDATE_DATE");
        EXPECT_STREQ(updateDate.c_str(), "2014-01-22 14:10:16");
        int updateUserId = pResult->getFieldAsInt32("UPDATE_USER_ID");
        EXPECT_EQ(updateUserId, 0);
        string dmsIp = pResult->getFieldAsString("DMS_IP");
        EXPECT_STREQ(dmsIp.c_str(), "112.124.4.112");
        int dmsConnPort = pResult->getFieldAsInt32("DMS_AUTO_CONN_PORT");
        EXPECT_EQ(dmsConnPort, 8682);
        int dmsClientPort = pResult->getFieldAsInt32("DMS_CLIENT_PORT");
        EXPECT_EQ(dmsClientPort, 9202);
        string dmsId = pResult->getFieldAsString("DMS_ID");
        EXPECT_STREQ(dmsId.c_str(), "");
        string adsIp = pResult->getFieldAsString("ADS_IP");
        EXPECT_STREQ(adsIp.c_str(), "10.33.6.237");
        int adsPort = pResult->getFieldAsInt32("ADS_PORT");
        EXPECT_EQ(adsPort, 9300);
        string adsId = pResult->getFieldAsString("ADS_ID");
        EXPECT_STREQ(adsId.c_str(), "4001");
        string ability = pResult->getFieldAsString("ABILITY");
        EXPECT_STREQ(ability.c_str(), "AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P");
        string version = pResult->getFieldAsString("VERSION_SN");
        EXPECT_STREQ(version.c_str(), "Chn_P_v2.211.0001.1.R.20131226");
        string defineTemplate = pResult->getFieldAsString("DEFINDSTATE_TEMPLATE");
        EXPECT_STREQ(defineTemplate.c_str(), "1,0");
        string idCode = pResult->getFieldAsString("IDENTIFY_CODE");
        EXPECT_STREQ(idCode.c_str(), "");
        string scene = pResult->getFieldAsString("SCENE_MODES");
        EXPECT_STREQ(scene.c_str(), "[{\"Mode\":\"nervous\",\"Period\":\"Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday\", \
\"BeginTime\":\"00:00:00\",\"EndTime\":\"23:59:59\"}]");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}


TEST_F(CConnectionPool_Preparedfunction, deleteTable_sync)
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

    string cmd = "DELETE from adm_dev where id = 1";
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


TEST_F(CConnectionPool_Preparedfunction, selectTable2_sync)
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

    string cmd = "select * from adm_dev t where t.ID=?";

    pTask->setCmdText(cmd);
    pTask->setParamAsInt32(0, 1);

    int result = pTask->execute();
    EXPECT_EQ(result, 0);
    if (result == 0)
    {
        CResultSet* pResult = pTask->getResult();
        int fieldCount = pResult->getFieldCount();
        EXPECT_EQ(fieldCount, 38);
        int rowCount = pResult->getRowCount();
        EXPECT_EQ(rowCount, 1);
        int id = pResult->getFieldAsInt32("ID");
        EXPECT_EQ(id, 1);
        string deviceCode = pResult->getFieldAsString("DEVICE_CODE");
        EXPECT_STREQ(deviceCode.c_str(), "PZC3GW33300019");
        string deviceName = pResult->getFieldAsString("DEVICE_NAME");
        EXPECT_STREQ(deviceName.c_str(), "PZC3GW33300019"); 
        string deviceSN = pResult->getFieldAsString("DEVICE_SN");
        EXPECT_STREQ(deviceSN.c_str(), "PZC3GW33300019"); 
        int category = pResult->getFieldAsInt32("DEVICE_CATEGORY");
        EXPECT_EQ(category, 0);
        string deviceType = pResult->getFieldAsString("DEVICE_TYPE");
        EXPECT_STREQ(deviceType.c_str(), "IPC-36X"); 
        string deviceManu = pResult->getFieldAsString("DEVICE_MANUFACTURER");
        EXPECT_STREQ(deviceManu.c_str(), "16777216"); 
        string deviceModel = pResult->getFieldAsString("DEVICE_MODEL");
        EXPECT_STREQ(deviceModel.c_str(), "HS-P100W");
        string deviceIP = pResult->getFieldAsString("DEVICE_IP");
        EXPECT_STREQ(deviceIP.c_str(), "192.168.1.137");
        int devicePort = pResult->getFieldAsInt32("DEVICE_PORT");
        EXPECT_EQ(devicePort, 37777);
        string ownerCode = pResult->getFieldAsString("OWNER_CODE");
        EXPECT_STREQ(ownerCode.c_str(), "0");
        int domainId = pResult->getFieldAsInt32("DOMAIN_ID");
        EXPECT_EQ(domainId, 0);
        int unitNum = pResult->getFieldAsInt32("UNIT_NUM");
        EXPECT_EQ(unitNum, 0);
        string loginType = pResult->getFieldAsString("LOGIN_TYPE");
        EXPECT_STREQ(loginType.c_str(), "0");
        string loginName = pResult->getFieldAsString("LOGIN_NAME");
        EXPECT_STREQ(loginName.c_str(), "");
        string loginPasswd = pResult->getFieldAsString("LOGIN_PASSWORD");
        EXPECT_STREQ(loginPasswd.c_str(), "");
        int registerId = pResult->getFieldAsInt32("REGIST_SERVICE_ID");
        EXPECT_EQ(registerId, 0);
        int registerPort = pResult->getFieldAsInt32("REGIST_PROXY_PORT");
        EXPECT_EQ(registerPort, 0);
        string registerDeviceCode = pResult->getFieldAsString("REGIST_DEVICE_CODE");
        EXPECT_STREQ(registerDeviceCode.c_str(), "");
        string memo = pResult->getFieldAsString("MEMO");
        EXPECT_STREQ(memo.c_str(), "");
        int sort = pResult->getFieldAsInt32("SORT");
        EXPECT_EQ(sort, 0);
        int online= pResult->getFieldAsInt32("IS_ONLINE");
        EXPECT_EQ(online, 0);
        //         string createDate = pResult->getFieldAsString("CREATE_DATE");
        //         EXPECT_STREQ(createDate.c_str(), "2013-08-12 09:46:39");
        int createUserId = pResult->getFieldAsInt32("CREATE_USER_ID");
        EXPECT_EQ(createUserId, 0);
        //         string updateDate = pResult->getFieldAsString("UPDATE_DATE");
        //         EXPECT_STREQ(updateDate.c_str(), "2014-01-22 14:10:16");
        int updateUserId = pResult->getFieldAsInt32("UPDATE_USER_ID");
        EXPECT_EQ(updateUserId, 0);
        string dmsIp = pResult->getFieldAsString("DMS_IP");
        EXPECT_STREQ(dmsIp.c_str(), "112.124.4.112");
        int dmsConnPort = pResult->getFieldAsInt32("DMS_AUTO_CONN_PORT");
        EXPECT_EQ(dmsConnPort, 8682);
        int dmsClientPort = pResult->getFieldAsInt32("DMS_CLIENT_PORT");
        EXPECT_EQ(dmsClientPort, 9202);
        string dmsId = pResult->getFieldAsString("DMS_ID");
        EXPECT_STREQ(dmsId.c_str(), "");
        string adsIp = pResult->getFieldAsString("ADS_IP");
        EXPECT_STREQ(adsIp.c_str(), "10.33.6.237");
        int adsPort = pResult->getFieldAsInt32("ADS_PORT");
        EXPECT_EQ(adsPort, 9300);
        string adsId = pResult->getFieldAsString("ADS_ID");
        EXPECT_STREQ(adsId.c_str(), "4001");
        string ability = pResult->getFieldAsString("ABILITY");
        EXPECT_STREQ(ability.c_str(), "AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P");
        string version = pResult->getFieldAsString("VERSION_SN");
        EXPECT_STREQ(version.c_str(), "Chn_P_v2.211.0001.1.R.20131226");
        string defineTemplate = pResult->getFieldAsString("DEFINDSTATE_TEMPLATE");
        EXPECT_STREQ(defineTemplate.c_str(), "1,0");
        string idCode = pResult->getFieldAsString("IDENTIFY_CODE");
        EXPECT_STREQ(idCode.c_str(), "");
        string scene = pResult->getFieldAsString("SCENE_MODES");
        EXPECT_STREQ(scene.c_str(), "[{\"Mode\":\"nervous\",\"Period\":\"Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday\", \
                                    \"BeginTime\":\"00:00:00\",\"EndTime\":\"23:59:59\"}]");
        bool nextRow = pResult->nextRow();
        EXPECT_FALSE(nextRow);
    }

    pTask->release();
}

TEST_F(CConnectionPool_Preparedfunction, dropTable_sync)
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

    string cmd = "drop Table adm_dev";
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
