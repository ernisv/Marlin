#include "../../inc/MarlinConfig.h"

/**
 * Klipper timers are handled by piggybacking on Marlin steppers.
*/

extern "C" {
    #include <sched.h>

    uint32_t timer_from_us(uint32_t us) {
        return us * STEPPER_TIMER_RATE / 1000000;
    }

    #if ENABLED(I2S_STEPPER_STREAM)
        static uint32_t klipper_timer_ticks = 0;
        static uint32_t next_wake_time = 0;
    
        uint32_t timer_read_time(void) {
            return klipper_timer_ticks;
        }

        void timer_kick(void) { 
            next_wake_time = timer_read_time();
        }
    #else
        uint32_t timer_read_time(void) {
            return (uint32_t)HAL_timer_get_count(MF_TIMER_STEP);
        }
        
        void timer_kick(void) { 
            HAL_timer_set_compare(MF_TIMER_STEP, timer_read_time() + 50);
        }            
    #endif
}

#if ENABLED(I2S_STEPPER_STREAM)
    /**
     * To be invoked if klipper timers are simulated by having periodic ticks, like it's
     *  done with I2S_STEPPER_STREAM.
     */
    void klipper_timer_periodic_tick() {
        
        klipper_timer_ticks++;
        
        if (next_wake_time >= klipper_timer_ticks) {
            next_wake_time = sched_timer_dispatch();
        }
    }
#endif