/*
 * command_parser_fsm.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */

#ifndef INC_COMMAND_PARSER_FSM_H_
#define INC_COMMAND_PARSER_FSM_H_
#include "global.h"


extern uint8_t command_flag;
extern uint8_t command_data[10];
extern uint8_t length_of_command;

void command_parser_fsm();



#endif /* INC_COMMAND_PARSER_FSM_H_ */
