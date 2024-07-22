#ifndef __USER_ROS_DATARECIEVE_H__
#define __USER_ROS_DATARECIEVE_H__
#include "Drv_usart.h"
#include "User_ROS_ControlFly.h"
#include "User_Task_Schduler.h"
#include <string.h>
#include "User_PID_Height.h"
#include "include.h"
#include "User_WayPoint_Control.h"
void Deal_With_ROS_Data(u8 func,u8 len,u8 *data);
void User_ROS_DataRecieve(u8 data);
#define IDLE    0
#define CHECK   1
#define LEN     2
#define WORK    3
#define END     4

#endif
