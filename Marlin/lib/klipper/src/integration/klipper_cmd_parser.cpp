#include "klipper_cmd_parser.h"

extern "C" {
#include "../command.h"

extern uint8_t next_sequence = MESSAGE_DEST;
}

void KlipperCmdParser::process_char(const char c) {
    if (content_ind == 0 && maybe_first_byte(c)) {
        msg_block_buf[content_ind++] = c;
    } else if (content_ind == 1) {
        if (maybe_second_byte(c)) {
            msg_block_buf[content_ind++] = c;
        } else if (maybe_first_byte(c)) {
            // if it's not second byte, it still may be first byte
            msg_block_buf[0] = c;
        } else content_ind = 0;
    } else {
        // already reading contents
        msg_block_buf[content_ind++] = c;
        if ((int)msg_block_buf[0] == content_ind) {
            if (is_last_byte(c)) {
                block_completed();
            }
            content_ind = 0;
        } else if (content_ind >= MSG_BLOCK_BUFFER_SIZE) {
            content_ind = 0;
        }
    }
}

bool KlipperCmdParser::maybe_first_byte(char c) {
    return c >= 5;
}

bool KlipperCmdParser::maybe_second_byte(char c) {
    return (c & 0xF0) == 0x10;
}

bool KlipperCmdParser::is_last_byte(char c) {
    return c == 0x7e;
}

void KlipperCmdParser::block_completed() {
    next_sequence = ((msg_block_buf[1] + 1) & MESSAGE_SEQ_MASK) | MESSAGE_DEST;
    ::command_dispatch(msg_block_buf, content_ind);
    ::command_send_ack();
}
