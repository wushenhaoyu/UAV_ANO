#ifndef __USER_ROS_CONTROLFLY_H__
#define __USER_ROS_CONTROLFLY_H__
#include "Ano_ProgramCtrl_User.h"

void Set_Vel(float hx_vel_cmps,float hy_vel_cmps,float yaw_vel_cmps);
void Set_Control_State(u8 state);
extern u8 control_state;
#endif