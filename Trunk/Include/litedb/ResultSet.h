//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2014-02-14        fan_bojie            Create
//

#ifndef LITEDB_RESULTSET_H
#define LITEDB_RESULTSET_H

#include <string>
#include "litebase/Noncopyable.h"
#include "Config.h"
#include "Types.h"

#ifdef  WIN32
#define atoll       _atoi64
#define strtoull    _strtoui64   
#endif

namespace litedb
{
	class LITEDB_DECL CResultSet: public litebase::details::CNoncopyable
	{
	public:
		CResultSet(uint64 rowCount, uint32 fieldCount);
		virtual ~CResultSet();

        uint64 getRowCount() const { return m_rowCnt; }
        uint32 getFieldCount() const { return m_fieldCnt; }
        uint64 getRowNum() const { return m_rowCnt; }
        uint32 getFieldNum() const { return m_fieldNum; }
        virtual int32 getFieldAsInt32(const std::string &fieldName) = 0;
        virtual int64 getFieldAsInt64(const std::string &fieldName) = 0;
        virtual uint32 getFieldAsUInt32(const std::string &fieldName) = 0;
        virtual uint64 getFieldAsUInt64(const std::string &fieldName) = 0;
        virtual std::string getFieldAsString(const std::string &fieldName) = 0; 
        virtual bool nextRow() = 0;

    protected:
        uint64 m_rowCnt;      // �����ϴ�UPDATE��DELETE��INSERT��ѯ���ģ�ɾ�������������
        uint32 m_fieldCnt;    // �����ϴ�ִ�����Ľ���е���Ŀ
        uint64 m_rowNum;        // ���������
        uint32 m_fieldNum;      // ���������

	};
}
#endif
