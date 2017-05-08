#ifndef LITEDB_PARAMSTATEMENT_H
#define LITEDB_PARAMSTATEMENT_H

#include <string>
#include "Types.h"

namespace litedb
{
    union ParamStatementData
    {
        bool boolean;
        uint8 ui8;
        int8 i8;
        uint16 ui16;
        int16 i16;
        uint32 ui32;
        int32 i32;
        uint64 ui64;
        int64 i64;
        float f;
        double d;
    };

    //- This enum helps us differ data held in above union
    enum ParamStatementValueType
    {
        TYPE_BOOL,
        TYPE_UI8,
        TYPE_UI16,
        TYPE_UI32,
        TYPE_UI64,
        TYPE_I8,
        TYPE_I16,
        TYPE_I32,
        TYPE_I64,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_STRING,
        TYPE_NULL
    };

    struct ParamStatement
    {
        ParamStatementData data;
        ParamStatementValueType type;
        std::string str;
    };
}

#endif
