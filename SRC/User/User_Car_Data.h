#ifndef __USER_TASK_SCHEDULER_H__
#define __USER_TASK_SCHEDULER_H__
#include "include.h"
#include "User_Task_Schduler.h"
#include "Drv_usart.h"
#include "User_Extend_Data.h"
void User_Car_DataRecieve(u8 data);
void User_Car_DataSend(u8 *data ,u8 func ,u8 length);
void User_Debug_DataSend(float *data, uint8_t length);
#define IDLE_ 				1
#define CHECK_ 				2
#define WORK_ 				3
#define END_					4
#endif