#ifndef __User_OPENMV_Cal_H__
#define __User_OPENMV_Cal_H__
#include "include.h"
#include "User_PID_XY.h"
#include "Ano_Pid.h"
#include "Ano_ProgramCtrl_User.h"
#include "Ano_Math.h"
#include "Ano_Parameter.h"
#include "Ano_Imu.h"
#include "User_PID_YAW.h"
extern u8 control_state_waypoint;
extern u8 correct_state; //航点修正状态
void Update_Current_Location(int x,int y);//更新当前位置
void Set_Target_WayPoint(int x,int y,int lim);//设定航点
void Cal_WayPoint_Error();//计算xy误差，送入pid
void User_WayPoint_Control(float dT_s);//航点PID控制
extern int x_current;
extern int y_current;
void Correct_Location();
extern u8 flag_arrive_the_waypoint;
void get_rotation_matrix(float theta, float R[2][2]);
void matrix_vector_multiply(float R[2][2], float vec[2], float result[2]);
float degrees_to_radians(float degrees) ;
#endif