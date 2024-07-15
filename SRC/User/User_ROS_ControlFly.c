/*
ROS控制飞控导航,由于是cartographer 2D + nav2 不需要Z轴速度控制，只需要把握水平即可，据往年考察，Z轴控制不会与XY同时发生
并且多发生于细致的任务，不处于ROS导航控制范围  
*/
u8    control_state = 0;
float linear_x_vel = 0;
float linear_y_vel = 0;
float yaw_vel = 0;
#include "User_ROS_ControlFly.h"

 void User_ROS_ControlFly()
{
	if(control_state)
	{
		Program_Ctrl_User_Set_HXYcmps(linear_x_vel,linear_y_vel);
		Program_Ctrl_User_Set_YawRate(yaw_vel);
	}
}

void Set_Vel(float hx_vel_cmps,float hy_vel_cmps,float yaw_vel_cmps)
{
	linear_x_vel = hx_vel_cmps;
	linear_y_vel = hy_vel_cmps;
	yaw_vel = yaw_vel_cmps;
}

void Set_Control_State(u8 state)
{
	control_state = state;
}