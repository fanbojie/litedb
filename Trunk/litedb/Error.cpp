#include "Error.h"

litedb::CLiteDBError::CLiteDBError( const std::string& msg )
						: std::runtime_error(msg)
{
}
