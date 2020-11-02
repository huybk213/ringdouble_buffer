#include "ring_buf.h"
#include <stdio.h>

ring_buf_t buf;
ring_buf_data_t holder[12];

void main(void)
{
    buf.buff = holder;
    buf.size = 12;

    for (uint32_t i = 0; ; i++)
    {
        uint32_t size = ring_buf_get_free(&buf);
        if (size == 0)
        {
            printf("Ring buffer full\r\n");
            break;
        }
        ring_buf_data_t msg;

        msg.len = 1;
        msg.data[0] = i;

        ring_buf_write(&buf, &msg);
    }


    ring_buf_skip(&buf, 2);
    
    uint32_t size = ring_buf_get_size_to_read(&buf);
    printf("Reading %d\r\n", size);

    for (uint32_t i = 0; i < size; i++)
    {
        ring_buf_data_t msg;

        ring_buf_read(&buf, &msg);
        printf("%d %d, remain %d\r\n", msg.data[0], msg.len, ring_buf_get_size_to_read(&buf));
    }
    printf("Done\r\n");
    getch();
}
