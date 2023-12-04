/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */

/*
 * command_parser_fsm.c
 *
 *  Created on: 4 thg 12, 2023
 *      Author: Acer
 */


#include "command_parser_fsm.h"

uint8_t command_flag = 0;
uint8_t command_data [ 10 ];
uint8_t length_of_command;

void command_parser_fsm() {
    switch (status_cmd) {
        case WAIT_HEADER:
            if (temp == 0x21) {
                length_of_command = 0;
                status_cmd = IN_RECEIVE_CMD;
            }
            break;

        case IN_RECEIVE_CMD:
            if (temp != 0x21 && temp != 0x23) {
                command_data[length_of_command++] = temp;
            }

            if (temp == 0x23) {
                status_cmd = WAIT_HEADER;
                command_flag = 1;
            }
            break;

        default:
            break;
    }
}


