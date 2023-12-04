/*
 * uart_communication_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */

#include "uart_communication.h"
#include"main.h"
#include "sched.h"
uint32_t ADC_value = 0;
char str[50];


void send_ADC() {
    HAL_UART_Transmit(&huart2, (uint8_t *) str, sprintf(str, "!ADC=%.4d#", ADC_value), 1000);
    HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}

void uart_communication_fsm() {
    switch (status_communicate) {
        case WAIT_CMD_RST:
            if (command_flag) {
                command_flag = 0;
                if (is_RST()) {
                    status_communicate = SEND_ADC;
                    SCH_Add_Task(send_ADC, 10, 300); // Schedule the send_ADC task after 10 scheduler ticks and repeat every 300 ticks
                    ADC_value = HAL_ADC_GetValue(&hadc1);
                }
            }
            break;

        case SEND_ADC:
            if (command_flag) {
                command_flag = 0;
                if (is_OK()) {
                    status_communicate = WAIT_CMD_RST;
                }
            }
            break;

        default:
            break;
    }
}
int is_RST(){
	if (length_of_command == 3 && command_data[0] == 0x52 && command_data[1] == 0x53 && command_data[2] == 0x54){
		return 1;
	}

	return 0;
}

int is_OK(){
	if (length_of_command == 2 && command_data[0] == 0x4f && command_data[1] == 0x4b){
			return 1;
		}

		return 0;
}

