#ifndef __USER_QR_DATA_H
#define __USER_QR_DATA_H
#include "include.h"
#include "Drv_usart.h"
#include "User_Car_Data.h"
#include "User_Extend_Data.h"
#define IDLE    0
#define CHECK   1
#define LEN     2
#define WORK    3
#define END     4
void User_QR_DataRecieve(u8 data);
void Deal_With_QR_Data(u8 u1_func, u8 len, u8 *data);
void User_QR_DataSend(u8 func,u8 len,u8 *data);
#endif