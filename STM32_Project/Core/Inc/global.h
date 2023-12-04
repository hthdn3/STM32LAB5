/*
 * global.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_


#include "main.h"
#include "stdint.h"
#include "software_timer.h"
#include "stdio.h"
#include "uart_communication.h"
#include "command_parser_fsm.h"
#include "software_timer.h"
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

#define WAIT_HEADER 			0
#define IN_RECEIVE_CMD			1

#define WAIT_CMD_RST			10
#define SEND_ADC				11

extern int status_cmd;
extern int status_communicate;
extern uint8_t temp;

#endif /* INC_GLOBAL_H_ */
