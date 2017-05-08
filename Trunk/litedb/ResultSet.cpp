#include "ResultSet.h"

litedb::CResultSet::CResultSet(uint64 rowCnt, uint32 fieldCnt)
: m_rowCnt(rowCnt)
, m_fieldCnt(fieldCnt)
, m_rowNum(0)
, m_fieldNum(0)
{
}

litedb::CResultSet::~CResultSet()
{
}


