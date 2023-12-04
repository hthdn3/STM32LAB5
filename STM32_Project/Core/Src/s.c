/*
 * s.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */
#include "s.h"
#include "stddef.h"


#ifdef __cplusplus
extern "C" {
#endif



typedef struct {
    void (*pTask)();    // Con trỏ đến hàm task
    uint32_t Delay;     // Độ trễ
    uint32_t Period;    // Chu kỳ
    uint8_t RunMe;      // Cờ cho biết task đã sẵn sàng chạy hay chưa
    uint32_t TaskID;    // ID của task
} task_t;

 task_t SCH_tasks_G[SCH_MAX_TASKS];
static uint32_t newTaskID = 0;
static uint32_t count_SCH_Update;
static uint32_t Get_New_Task_ID(void);
static uint32_t Get_New_Task_ID(void){
	newTaskID++;
	if(newTaskID == NO_TASK_ID){
		newTaskID++;
	}
	return newTaskID;
}

void SCH_Init(void){
	for(int i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}
}

 void SCH_Update(void){
 	// kiểm tra nếu task ở đây
 	count_SCH_Update ++;
 	if (SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0) {
 		if(SCH_tasks_G[0].Delay > 0){
 			SCH_tasks_G[0].Delay--;
 		}
 		if (SCH_tasks_G[0].Delay == 0) {
 			SCH_tasks_G[0].RunMe = 1;
 		}
 	}
 }


uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    uint8_t newTaskIndex = 0;
    uint32_t sumDelay = 0;
    uint32_t newDelay = 0;

    for (newTaskIndex = 0; newTaskIndex < SCH_MAX_TASKS; newTaskIndex++) {
        sumDelay += SCH_tasks_G[newTaskIndex].Delay;
        // Nếu tổng độ trễ lớn hơn độ trễ mong muốn
        if (sumDelay > DELAY) {
            // Tính toán lại độ trễ mới
            newDelay = DELAY - (sumDelay - SCH_tasks_G[newTaskIndex].Delay);
            SCH_tasks_G[newTaskIndex].Delay = sumDelay - DELAY;

            // Dời các task phía sau lên một vị trí để chèn task mới
            for (uint8_t i = SCH_MAX_TASKS - 1; i > newTaskIndex; i--) {
                SCH_tasks_G[i] = SCH_tasks_G[i - 1];
            }

            // Thêm task mới vào vị trí phù hợp
            SCH_tasks_G[newTaskIndex].pTask = pFunction;
            SCH_tasks_G[newTaskIndex].Delay = newDelay;
            SCH_tasks_G[newTaskIndex].Period = PERIOD;
            SCH_tasks_G[newTaskIndex].RunMe = (SCH_tasks_G[newTaskIndex].Delay == 0) ? 1 : 0;
            SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();

            // Trả về ID của task mới được thêm
            return SCH_tasks_G[newTaskIndex].TaskID;
        } else {
            // Nếu task hiện tại chưa được khởi tạo
            if (SCH_tasks_G[newTaskIndex].pTask == NULL) {
                // Thêm task mới vào vị trí hiện tại
                SCH_tasks_G[newTaskIndex].pTask = pFunction;
                SCH_tasks_G[newTaskIndex].Delay = DELAY - sumDelay;
                SCH_tasks_G[newTaskIndex].Period = PERIOD;
                SCH_tasks_G[newTaskIndex].RunMe = (SCH_tasks_G[newTaskIndex].Delay == 0) ? 1 : 0;
                SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();

                // Trả về ID của task mới được thêm
                return SCH_tasks_G[newTaskIndex].TaskID;
            }
        }
    }

    // Trả về ID của task cuối cùng trong danh sách
    return SCH_tasks_G[newTaskIndex - 1].TaskID;
}




uint8_t SCH_Delete_Task(uint32_t taskID) {
    uint8_t Return_code = 0;
    uint8_t taskIndex;
    uint8_t j;

    if (taskID != NO_TASK_ID) {
        for (taskIndex = 0; taskIndex < SCH_MAX_TASKS; taskIndex++) {
            if (SCH_tasks_G[taskIndex].TaskID == taskID) {
                Return_code = 1; // Đánh dấu trạng thái xóa thành công là 1

                // Cộng độ trễ của task bị xóa vào task phía sau (nếu có)
                if (taskIndex < SCH_MAX_TASKS - 1 && SCH_tasks_G[taskIndex + 1].pTask != NULL) {
                    SCH_tasks_G[taskIndex + 1].Delay += SCH_tasks_G[taskIndex].Delay;
                }

                // Di chuyển các task phía sau task bị xóa lên một vị trí để ghi đè lên task bị xóa
                for (j = taskIndex; j < SCH_MAX_TASKS - 1; j++) {
                    SCH_tasks_G[j] = SCH_tasks_G[j + 1];
                }

                // Đặt các thông số của task cuối cùng về giá trị mặc định
                SCH_tasks_G[j].pTask = NULL;
                SCH_tasks_G[j].Period = 0;
                SCH_tasks_G[j].Delay = 0;
                SCH_tasks_G[j].RunMe = 0;
                SCH_tasks_G[j].TaskID = 0;

                return Return_code; // Trả về mã trạng thái xóa thành công
            }
        }
    }

    return Return_code; // Trả về mã trạng thái mặc định
}

void SCH_Dispatch_Tasks(void) {
    if (SCH_tasks_G[0].RunMe > 0) {
        Run_Task();
        Delete_Task();
            }
}
void Run_Task(){
    (*SCH_tasks_G[0].pTask)();
   // Đặt lại cờ RunMe về 0 để đánh dấu task đã được thực thi
    SCH_tasks_G[0].RunMe = 0;
}
void Delete_Task(){
    // Lưu lại task đã làm
    task_t temtask = SCH_tasks_G[0];
    // Xóa task đã làm
    SCH_Delete_Task(temtask.TaskID);
    // Nếu task có chu kỳ (Period) khác 0, thêm lại vào danh sách để tiếp tục chạy
    if (temtask.Period != 0) {
        SCH_Add_Task(temtask.pTask, temtask.Period, temtask.Period);
    }
}


#ifdef __cplusplus
}
#endif

