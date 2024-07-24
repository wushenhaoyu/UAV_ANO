#ifndef __USER_TASK_SCHEDULER_H
#define __USER_TASK_SCHEDULER_H
#include "Ano_FlightCtrl.h"
#include "include.h"
#include "User_OPENMV_DataRecieve.h"
#include "User_OPENMV_Cal.h"
#include "User_WayPoint_Control.h"
#include "User_PID_XY.h"
#include "User_PID_YAW.h"
#include "User_RC.h"
#include "User_WayPoint_Control.h"
void User_Task_Schduler(u8 ms);
void Set_Task_State(u8 data);
void User_FlyState_Manager(u8 state,u8 action);
#define HEIGHT_CTRL         0x01
#define YAW_CTRL            0x02
#define WAYPOINT_CTRL       0x03
#define OPENMV_DXDY_CTRL    0x04
#define CTRL_ON             0x01
#define CTRL_OFF            0x00
#endif
