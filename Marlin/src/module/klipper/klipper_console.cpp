#include "../../inc/MarlinConfig.h"

extern "C" {
    #include <board/misc.h>

    void console_sendf(const struct command_encoder *ce, va_list args);
}