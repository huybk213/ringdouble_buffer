#include "ring_buf.h"

uint32_t ring_buf_get_free(ring_buf_t *buf)
{
    uint32_t size;
    if (buf->wr_idx == buf->rd_idx)
    {
        size = buf->size;
    }
    else if (buf->rd_idx > buf->wr_idx)
    {
        size = buf->rd_idx - buf->wr_idx;
    }
    else
    {
        size = buf->size - buf->wr_idx + buf->rd_idx;
    }
    
    return size - 1;
}

uint32_t ring_buf_get_size_to_read(ring_buf_t *buf)
{
    if (buf->wr_idx == buf->rd_idx) 
    {
        return 0;
    } 
    else if (buf->wr_idx > buf->rd_idx) 
    {
        return (buf->wr_idx - buf->rd_idx);
    } 
    else 
    {
        return (buf->size - buf->rd_idx  + buf->wr_idx);
    }
}

bool ring_buf_write(ring_buf_t *buf, ring_buf_data_t * msg)
{   
    if (ring_buf_get_free(buf) == 0)
    {
        return false;
    }

    buf->buff[buf->wr_idx].len = msg->len;
    memcpy(buf->buff[buf->wr_idx].data, msg->data, msg->len);

    buf->wr_idx += 1;

    if (buf->wr_idx >= buf->size)
        buf->wr_idx = 0;

    return true;
}

bool ring_buf_read(ring_buf_t *buf, ring_buf_data_t * msg)
{
    if (ring_buf_get_size_to_read(buf) == 0)
    {
        return false;
    }

    uint32_t idx = buf->rd_idx;
    
    msg->len = buf->buff[buf->rd_idx].len;
    memcpy(msg->data, buf->buff[buf->rd_idx].data, msg->len);

    buf->rd_idx += 1;
    
    if (buf->rd_idx >= buf->size)
        buf->rd_idx = 0;

    return true;
}

void ring_buf_skip(ring_buf_t *buf, uint32_t skip_cnt)
{
    uint32_t size = ring_buf_get_size_to_read(buf);
    
    if (skip_cnt >= size)
        skip_cnt = size;
    
    for (uint32_t i = 0; i < skip_cnt;i++)
    {
        buf->rd_idx += 1;   
        if (buf->rd_idx >= buf->size)
            buf->rd_idx = 0;
    }
}
