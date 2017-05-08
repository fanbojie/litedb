//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2014-03-27        fan_bojie            Create
//

#ifndef LITEBASE_BINARYBUFFER_H
#define LITEBASE_BINARYBUFFER_H

#include "Config.h"

namespace litebase
{
    namespace details
    {
        class LITEBASE_DECL CBinaryBuffer
        {
            struct _BinaryBuffer
            {
                int _pos;
                int _length;
                char _buffer[];
            };

        public:
            CBinaryBuffer(int length);
            CBinaryBuffer();
            ~CBinaryBuffer();

            void append(void* data, int size);
            void updateLength(int length);
            void* dump();
            int getLength();

        private:
            _BinaryBuffer*  m_buffer;
        };
    }
}

#endif
