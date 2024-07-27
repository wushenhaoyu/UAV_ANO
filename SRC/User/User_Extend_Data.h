#ifndef __USER_EXTEND_DATA_H__
#define __USER_EXTEND_DATA_H__
#include "include.h"
#include "Drv_usart.h"
#include "User_WayPoint_Control.h"
#include "User_Car_Data.h"
void User_Extend_DataRecieve(u8 data);
void User_Extend_DataSend(u8 func,u8 len,u8 *data);
void Deal_With_Extend_Data(u8 u2_func, u8 len, u8 *data);
void Beep();
void Laser_Turn_On();
void Laser_Turn_Off();
#define IDLE    0
#define CHECK   1
#define LEN     2
#define WORK    3
#define END     4
#endif