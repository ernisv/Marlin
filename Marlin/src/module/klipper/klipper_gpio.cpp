#include "../../inc/MarlinConfig.h"

extern "C" {
    #include <board/gpio.h>

    void gpio_out_toggle_noirq(struct gpio_out g) {
        TOGGLE(g.pin);
    }

    void gpio_out_write(struct gpio_out g, uint8_t val) {
        WRITE(g.pin, val);
    }

    struct gpio_out gpio_out_setup(uint8_t pin, uint8_t val) {
        SET_OUTPUT(pin);
        WRITE(pin, val);
        struct gpio_out g = { .pin = pin };
        return g;
    }
}