/*
 * s.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */

#ifndef INC_S_H_
#define INC_S_H_

#include "stdint.h"

#define  SCH_MAX_TASKS     10
#define NO_TASK_ID 0xFFFFFFFF // Giá trị ID task không hợp lệ

    void SCH_Init(void);
    static uint32_t Get_New_Task_ID(void);
    void SCH_Update(void);

    uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);

    void SCH_Dispatch_Tasks(void);
    void Delete_Task();
    void Add_Periodic_Task();
    void Run_Task();

    uint8_t SCH_Delete_Task(uint32_t TASK_ID);


    static void TIMER_Init();

#endif /* INC_S_H_ */
