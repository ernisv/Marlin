#include <stdint.h>
#include "../autoconf.h"
#include "../command.h"

uint8_t
timer_is_before(uint32_t time1, uint32_t time2)
{
    return (int32_t)(time1 - time2) < 0;
}

DECL_CONSTANT("CLOCK_FREQ", CONFIG_CLOCK_FREQ);
DECL_CONSTANT_STR("MCU", "Marlin Klipper emulator");