#include "BinaryBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

litebase::details::CBinaryBuffer::CBinaryBuffer( int length )
: m_buffer(NULL)
{
    m_buffer = (_BinaryBuffer*)malloc(sizeof(*m_buffer) + length);
    if (m_buffer != NULL)
    {
        m_buffer->_length = length;
        m_buffer->_pos = 0;
    }
}

litebase::details::CBinaryBuffer::CBinaryBuffer()
: m_buffer(NULL)
{
    m_buffer = (_BinaryBuffer*)malloc(sizeof(*m_buffer));
    if (m_buffer != NULL)
    {
        m_buffer->_pos = 0;
        m_buffer->_length = 0;
    }
}

litebase::details::CBinaryBuffer::~CBinaryBuffer()
{
    free(m_buffer); 
}
  
void litebase::details::CBinaryBuffer::updateLength( int length )
{
    if (m_buffer == NULL || m_buffer->_length - m_buffer->_pos >= length)
    {
        return;        
    }
    
    int newLength = m_buffer->_length+length;
    m_buffer = (_BinaryBuffer*)realloc(m_buffer, sizeof(*m_buffer) + newLength);
    if (m_buffer != NULL)
    {
        m_buffer->_length = newLength;
    }
}

void litebase::details::CBinaryBuffer::append( void* data, int size )
{
    if (m_buffer != NULL)
    {
        memcpy(m_buffer->_buffer+m_buffer->_pos, data, size);
        m_buffer->_pos += size;
    }
}

void* litebase::details::CBinaryBuffer::dump()
{
    if (m_buffer != NULL)
    {
        return (void*)m_buffer->_buffer;
    }

    return NULL;
}

int litebase::details::CBinaryBuffer::getLength()
{
    if (m_buffer != NULL)
    {
        return m_buffer->_pos;
    }

    return 0;
}

