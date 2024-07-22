#ifndef __User_OPENMV_Cal_H__
#define __User_OPENMV_Cal_C__
#include "include.h"
#include "User_PID_XY.h"
#include "Ano_Pid.h"
#include "Ano_ProgramCtrl_User.h"
#include "Ano_Math.h"
#include "Ano_Parameter.h"
#include "Ano_Imu.h"
extern u8 control_state_waypoint;
void Update_Current_Location(float x,float y);//更新当前位置
void Set_Target_WayPoint(float x,float y);//设定航点
void Cal_WayPoint_Error();//计算xy误差，送入pid
void User_WayPoint_Control(float dT_s);//航点PID控制
extern float x_current;
extern float y_current;
#endif