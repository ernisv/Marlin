#include <stdint.h>

static uint8_t receive_buf[4096];

void *
console_receive_buffer(void)
{
    return receive_buf;
}

uint8_t
timer_is_before(uint32_t time1, uint32_t time2)
{
    return (int32_t)(time1 - time2) < 0;
}