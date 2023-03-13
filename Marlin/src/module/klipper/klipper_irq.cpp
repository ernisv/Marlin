/**
 * Provides integration points for Klipper code in private library.
*/

#include "../../inc/MarlinConfig.h"

extern "C" {
#include <board/irq.h>

#if __SIZEOF_POINTER__ > 4
#include <unistd.h>
#endif


irqstatus_t irq_save(void) {
    irqstatus_t ret = hal.isr_state();
    hal.isr_off();
    return ret;
}

void irq_restore(irqstatus_t flag) {
    if (flag) 
        hal.isr_on();
    else hal.isr_off();
}

void irq_disable(void) {
    hal.isr_off();
}

void irq_enable(void) {
    hal.isr_on();
}

void irq_wait(void) {
    hal.isr_on();
    asm volatile ("nop");
    #if __SIZEOF_POINTER__ > 4
    usleep(1);
    #endif
    hal.isr_off();
}

void irq_poll(void) { }
}
