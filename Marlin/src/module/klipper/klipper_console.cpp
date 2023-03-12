#include "../../inc/MarlinConfig.h"

extern "C" {
    #include <board/misc.h>
    #include <command.h>

    static uint8_t klipper_response_buf[256];

    void console_sendf(const struct command_encoder *ce, va_list args) {
        uint_fast8_t msglen = command_encode_and_frame(klipper_response_buf, ce, args);

        PORT_REDIRECT(SERIAL_PORTMASK(KLIPPER_SERIAL_PORT));
        
        for (uint8_t *out = klipper_response_buf; out - klipper_response_buf < msglen; ++out) {
            SERIAL_CHAR(*out);
        }
    }
}