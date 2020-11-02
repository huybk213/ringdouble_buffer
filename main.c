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
        }
        ring_buf_data_t msg;

        msg.len = 1;
        msg.data[0] = i;

        if (ring_buf_write(&buf, &msg) == false)
            break;
    }

    
    uint32_t size = ring_buf_get_size_to_read(&buf);
    printf("Reading %d\r\n", size);

    for (uint32_t i = 0; ; i++)
    {
        ring_buf_data_t msg;

        if (ring_buf_read(&buf, &msg) == false)
            break;

        printf("%d %d, remain %d\r\n", msg.data[0], msg.len, ring_buf_get_size_to_read(&buf));
    }
    printf("Done\r\n");
    getch();
}
