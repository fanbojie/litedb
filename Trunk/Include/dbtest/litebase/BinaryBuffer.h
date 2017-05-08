#ifndef LITEBASE_BINARYBUFFER_H
#define LITEBASE_BINARYBUFFER_H

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

        private:
            _BinaryBuffer*  m_buffer;
        };
    }
}

#endif
