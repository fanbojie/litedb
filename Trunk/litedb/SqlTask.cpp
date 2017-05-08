#include "SqlTask.h"
#include "litebase/Trace.h"
#include "Error.h"
#include "MysqlError.h"
#include "BaseDefine.h"
#include "DatabaseRequest.h"
#include "ResultSet.h"

using namespace std;
using namespace litedb;

litedb::CSqlTask::CSqlTask()
: m_type(TASK_TYPE::TYPE_SYNC)
, m_taskId(0)
, m_connPool(NULL)
, m_request(NULL)
, m_response(NULL)
{
}

litedb::CSqlTask::~CSqlTask()
{
}

void litedb::CSqlTask::init( int type, int taskId, litedb::CConnectionPool* pool /*= NULL*/ )
{
    m_type = type;
    m_taskId = taskId;
    m_connPool = pool;
}

void litedb::CSqlTask::setParamAsUInt8( int index, uint8 value )
{
    if (m_request != NULL)
    {
        m_request->setUInt8(index, value);
    }
}

void litedb::CSqlTask::setParamAsUInt16( int index, uint16 value )
{
    if (m_request != NULL)
    {
        m_request->setUInt16(index, value);
    }
}

void litedb::CSqlTask::setParamAsUInt32( int index, uint32 value )
{
    if (m_request != NULL)
    {
        m_request->setUInt32(index, value);
    }
}

void litedb::CSqlTask::setParamAsUInt64( int index, uint64 value )
{
    if (m_request != NULL)
    {
        m_request->setUInt64(index, value);
    }
}

void litedb::CSqlTask::setParamAsInt8( int index, int8 value )
{
    if (m_request != NULL)
    {
        m_request->setInt8(index, value);
    }
}

void litedb::CSqlTask::setParamAsInt16( int index, int16 value )
{
    if (m_request != NULL)
    {
        m_request->setInt16(index, value);
    }
}

void litedb::CSqlTask::setParamAsInt32( int index, int32 value )
{
    if (m_request != NULL)
    {
        m_request->setInt32(index, value);
    }
}

void litedb::CSqlTask::setParamAsInt64( int index, int64 value )
{
    if (m_request != NULL)
    {
        m_request->setInt64(index, value);
    }
}

void litedb::CSqlTask::setParamAsFloat( int index, float value )
{
    if (m_request != NULL)
    {
        m_request->setFloat(index, value);
    }
}

void litedb::CSqlTask::setParamAsDouble( int index, double value )
{
    if (m_request != NULL)
    {
        m_request->setDouble(index, value);
    }
}

void litedb::CSqlTask::setParamAsString( int index, const std::string& value )
{
    if (m_request != NULL)
    {
        m_request->setString(index, value);
    }
}

void litedb::CSqlTask::setParamAsNull( int index )
{
    if (m_request != NULL)
    {
        m_request->setNull(index);
    }
}

void litedb::CSqlTask::call()
{
    try
    {
        execute();
    }
    catch (CMysqlError* e)
    {
        TRACE_ERR(0, "mysql error, taskId=%d errno=%d err=%s.",
            m_taskId, e->m_errNum, e->what());
        return;
    }
    catch (CLiteDBError* e)
    {
        TRACE_ERR(0, "litedb error, taskId=%d err=%s.", m_taskId, e->what());
        return;
    }
    catch (...)
    {
        TRACE_ERR(0, "taskId=%d other error.", m_taskId);
        return;
    }

    // 这样调用有可能因为外部使用不当，阻塞数据库线程
//     if (m_callback != NULL)
//     {
//         m_callback->sendRequestReply(pResult);
//     }
}

void litedb::CSqlTask::release()
{
    if (m_request != NULL)
    {
        delete m_request;
        m_request = NULL;
    }

    if (m_response != NULL)
    {
        delete m_response;
        m_response = NULL;
    }

    delete this;
}
