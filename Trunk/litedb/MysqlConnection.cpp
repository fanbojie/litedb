#include "MysqlConnection.h"
#include "litebase/Trace.h"
#include "ConnectionWorker.h"
#include "Error.h"
#include "MysqlError.h"

using namespace std;
using namespace litedb;

litedb::CMysqlConnection::CMysqlConnection()
: m_mysql(NULL)
{
}

litedb::CMysqlConnection::~CMysqlConnection()
{
    close();
}

void litedb::CMysqlConnection::open()
{
	MYSQL* mysqlInit = NULL;
	mysqlInit = mysql_init(NULL);
	if (mysqlInit == NULL)
	{
		throw CLiteDBError("mysql_init() failed.");
	}
	
	mysql_options(mysqlInit, MYSQL_SET_CHARSET_NAME, "utf8");

	int port;
	char const* unix_socket;

	#ifdef WIN32
	if (m_connectionInfo.m_host == ".")                                           // named pipe use option (Windows)
	{
		unsigned int opt = MYSQL_PROTOCOL_PIPE;
		mysql_options(mysqlInit, MYSQL_OPT_PROTOCOL, (char const*)&opt);
		port = 0;
		unix_socket = 0;
	}
	else                                                    // generic case
	{
		port = atoi(m_connectionInfo.m_port.c_str());
		unix_socket = 0;
	}
	#else
	if (m_connectionInfo.m_host == ".")                                           // socket use option (Unix/Linux)
	{
		unsigned int opt = MYSQL_PROTOCOL_SOCKET;
		mysql_options(mysqlInit, MYSQL_OPT_PROTOCOL, (char const*)&opt);
		m_connectionInfo.m_host = "localhost";
		port = 0;
		unix_socket = m_connectionInfo.m_port.c_str();
	}
	else                                                    // generic case
	{
		port = atoi(m_connectionInfo.m_port.c_str());
		unix_socket = 0;
	}
	#endif

	m_mysql = mysql_real_connect(mysqlInit, m_connectionInfo.m_host.c_str(), m_connectionInfo.m_user.c_str(),
						m_connectionInfo.m_password.c_str(), m_connectionInfo.m_database.c_str(),
						port, unix_socket, 0);
	if (m_mysql != NULL)
	{
		// 自动提交
		mysql_autocommit(m_mysql, 1);
		mysql_set_character_set(m_mysql, "utf8");
        int reconnect = 1;
        mysql_options(m_mysql, MYSQL_OPT_RECONNECT, (my_bool*)&reconnect);
	}
	else
	{
        TRACE_ERR(0, "connect mysql server failed, MySQL client library:%s.", 
            mysql_get_client_info());
		string errMsg = mysql_error(mysqlInit);
		unsigned int errNum = mysql_errno(mysqlInit);
		mysql_close(mysqlInit);
        mysqlInit = NULL;
		throw CMysqlError(errMsg, errNum);
	}
}

void litedb::CMysqlConnection::close()
{
	if (m_mysql != NULL)
	{
		mysql_close(m_mysql);
		m_mysql = NULL;
	}

    if (m_worker != NULL)
    {
        m_worker->stop();
//         delete m_worker;
//         m_worker = NULL;
    }

    m_isClose = true;
}
