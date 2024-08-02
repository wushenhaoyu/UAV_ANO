#ifndef __USER_TASK_SCHEDULER_H
#define __USER_TASK_SCHEDULER_H
#include "Ano_FlightCtrl.h"
#include "include.h"
#include "User_OPENMV_DataRecieve.h"
#include "User_WayPoint_Control.h"
#include "User_PID_XY.h"
#include "User_PID_YAW.h"
#include "User_RC.h"
#include "User_WayPoint_Control.h"
#include "User_PID_Height.h"
#include "User_QR_Data.h"
void User_Task_Schduler(u8 ms);
void Set_Task_State(u8 data);
void User_TakeOff_Init(u8 ms);
void Task_One(u8 ms);
void Task_Two(u8 ms);
u8 User_Land_Task(u8 ms);
void AC456(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim);
void AC123(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim);
void BD456(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim);
void BD123(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim);
extern u8 Target_num1; // 1:a 2:b 3:c 4:d
extern u8 Target_num2; // 1 2 3 4 5 6 
extern u8  x_state ;
extern u8 z_state;
extern u8 IsInitTaskTwo;
extern u8 IsStartTaskTwo;
#define HEIGHT_CTRL         0x01
#define YAW_CTRL            0x02
#define WAYPOINT_CTRL       0x03
#define OPENMV_DXDY_CTRL    0x04
#define CTRL_ON             0x01
#define CTRL_OFF            0x00
#endif
