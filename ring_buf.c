#include "ring_buf.h"

uint32_t ring_buf_get_free(ring_buf_t *buf)
{
    uint32_t size;
    if (buf->wrIdx == buf->rdIdx)
    {
        size = buf->size;
    }
    else if (buf->rdIdx > buf->wrIdx)
    {
        size = buf->rdIdx - buf->wrIdx;
    }
    else
    {
        size = buf->size - buf->wrIdx + buf->rdIdx;
    }
    
    return size - 1;
}

uint32_t ring_buf_get_size_to_read(ring_buf_t *buf)
{
    if (buf->wrIdx == buf->rdIdx) 
    {
        return 0;
    } 
    else if (buf->wrIdx > buf->rdIdx) 
    {
        return (buf->wrIdx - buf->rdIdx);
    } 
    else 
    {
        return (buf->size - buf->rdIdx  + buf->wrIdx);
    }
}

bool ring_buf_write(ring_buf_t *buf, ring_buf_data_t * msg)
{   
    if (ring_buf_get_free(buf) == 0)
    {
        return false;
    }

    buf->buff[buf->wrIdx].len = msg->len;
    memcpy(buf->buff[buf->wrIdx].data, msg->data, msg->len);

    buf->wrIdx += 1;

    if (buf->wrIdx >= buf->size)
        buf->wrIdx = 0;

    return true;
}

bool ring_buf_read(ring_buf_t *buf, ring_buf_data_t * msg)
{
    if (ring_buf_get_size_to_read(buf) == 0)
    {
        return false;
    }

    uint32_t idx = buf->rdIdx;
    
    msg->len = buf->buff[buf->rdIdx].len;
    memcpy(msg->data, buf->buff[buf->rdIdx].data, msg->len);

    buf->rdIdx += 1;
    
    if (buf->rdIdx >= buf->size)
        buf->rdIdx = 0;

    return true;
}

void ring_buf_skip(ring_buf_t *buf, uint32_t skip_cnt)
{
    uint32_t size = ring_buf_get_size_to_read(buf);
    
    if (skip_cnt >= size)
        skip_cnt = size;
    
    for (uint32_t i = 0; i < skip_cnt;i++)
    {
        buf->rdIdx += 1;   
        if (buf->rdIdx >= buf->size)
            buf->rdIdx = 0;
    }
}
