#include "gtest/gtest.h"
#include "litedb/ConnectionInfo.h"

using namespace litedb;

class CConnectionInfo_function: public testing::Test
{
protected:

    static void SetUpTestCase()
    {
        printf("Set up ConnectionInfo Test...\n");
    }
    static void TearDownTestCase()
    {
        printf("TearDown ConnectionInfo Test...\n");
    }

public:
    static CConnectionInfo  m_connInfo;
};

CConnectionInfo CConnectionInfo_function::m_connInfo = CConnectionInfo("1;172.6.1.246;3306;dh;123456;test"); 

TEST_F(CConnectionInfo_function, parse)
{
    EXPECT_EQ(m_connInfo.m_type, 1);
    EXPECT_STREQ(m_connInfo.m_user.c_str(), "dh");
    EXPECT_STREQ(m_connInfo.m_password.c_str(), "123456");
    EXPECT_STREQ(m_connInfo.m_database.c_str(), "test");
    EXPECT_STREQ(m_connInfo.m_port.c_str(), "3306");
    EXPECT_STREQ(m_connInfo.m_host.c_str(), "172.6.1.246");
}
