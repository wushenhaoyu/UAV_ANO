#ifndef __USER_PID_YAW_H
#define __USER_PID_YAW_H
#include "include.h"
#include "Ano_Pid.h"
#include "Ano_ProgramCtrl_User.h"
#include "Ano_Math.h"
#include "Ano_Parameter.h"
#include "Ano_Imu.h"
extern float yaw_target;
extern u8 control_state_yaw;
extern u8 direction_state ;
extern u8 flag_arrvie_the_yaw;
void User_PID_yaw_Init();//请放在All_PID_Init里面
void User_PID_yaw_Ctrl(float dT_s);
void Set_Target_yaw(float data , float lim);
float NormalizeYaw(float angle);
void Set_Direction(u8 direction , float lim);
#endif
