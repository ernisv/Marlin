#pragma once

#include <stdint.h>

#define MSG_BLOCK_BUFFER_SIZE 255

class KlipperCmdParser {
    private:
        uint8_t msg_block_buf[MSG_BLOCK_BUFFER_SIZE];
        int content_ind = 0;

        static inline bool maybe_first_byte(char c);
        static inline bool maybe_second_byte(char c);
        static inline bool is_last_byte(char c);
        inline void block_completed();

    public:
        void process_char(const char c);
};
