#ifndef __USER_ROS_DATARECIEVE_H__
#define __USER_ROS_DATARECIEVE_H__
#include "Drv_usart.h"
#include "User_ROS_ControlFly.h"
#include "User_Task_Schduler.h"
#include <string.h>
void User_ROS_DataRecieve(u8 data);
#define IDLE    0
#define CHECK   1
#define FUNC    2
#define LEN     3
#define WORK    4
#define END     5
#endif