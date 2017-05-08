#include "MysqlFactory.h"
#include "MysqlConnection.h"
#include "DatabaseRequest.h"
#include "MysqlRawRequest.h"
#include "MysqlPreparedRequest.h"
#include "MysqlPingRequest.h"
#include "MysqlTask.h"
#include "BaseDefine.h"

using namespace litedb;

litedb::CMysqlFactory::CMysqlFactory()
{

}

litedb::CMysqlFactory::~CMysqlFactory()
{

}

litedb::CConnection* litedb::CMysqlFactory::createConnection()
{
	return new CMysqlConnection;
}

litedb::CDatabaseRequest* litedb::CMysqlFactory::createRequest( int type )
{
	CDatabaseRequest* pReq = NULL;

	switch(type)
	{
		case REQ_TYPE::TYPE_RAW:
		{
			pReq = new CMysqlRawRequest;
			break;
		}
		case REQ_TYPE::TYPE_PREPARED:
		{
			pReq = new CMysqlPreparedRequest;
			break;
		}
        case REQ_TYPE::TYPE_PING:
        {
            pReq = new CMysqlPingRequest;
            break;
        }
		default:
		{
			break;
		}
	}
	
	return pReq;
}

litedb::CSqlTask* litedb::CMysqlFactory::createTask()
{
	return new CMysqlTask;
}

