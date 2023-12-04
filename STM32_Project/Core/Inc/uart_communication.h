/*
 * uart_communication.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_

#include "global.h"
#include "command_parser_fsm.h"

void sending();
void uart_communication_fsm();
int is_RST();
int is_OK();

#endif /* INC_UART_COMMUNICATION_H_ */
