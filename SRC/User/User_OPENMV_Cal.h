#ifndef __USER_OPENMV_CAL_H
#define __USER_OPENMV_CAL_H
#include "include.h"
#include "User_PID_XY.h"
#include "Ano_Pid.h"
#include "Ano_ProgramCtrl_User.h"
#include "Ano_Math.h"
#include "Ano_Parameter.h"
#include "Ano_Imu.h"
extern int32_t pixel_dx_;
extern int32_t pixel_dy_;
extern u8 control_state_openmv_localization;
void User_OPENMV_Localization(float dT_s);
void User_OPENMV_DXDY_Cal();

void Set_OPENMV_DXDY(int32_t dx,int32_t dy);
#endif

