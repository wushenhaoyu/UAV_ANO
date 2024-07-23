#ifndef __USER_PID_XY_H
#define __USER_PID_XY_H
#include "include.h"
#include "Ano_Pid.h"
#include "Ano_ProgramCtrl_User.h"
#include "Ano_Math.h"
#include "Ano_Parameter.h"
void User_PID_XY_Init();
void  User_PID_XY_Ctrl(float dT_s);
void Set_Target_XY(float X, float Y);
extern u8 EN_XY;
#endif

