/*#include <math.h>
#include <stdio.h>
#include "User_WayPoint_Control.h"
#include "User_Extend_Data.h"
#define PI 3.14159265358979323846
int x_correct = 0;
int y_correct = 0;
int x_current = 0;
int y_current = 0;
int x_target = 0;
int y_target = 0;
int x_error;
int y_error;
int vel_lim = 30;
u8 correct_state = 0; //修正生效位
u8 control_state_waypoint = 0;
u8 flag_arrive_the_waypoint = 0;  //到达航点标志

float yaw_angle = 0.0;  // 当前的航向角，需要从IMU传感器获取并更新

void Update_Current_Location(int x, int y) {
    if(correct_state) {
        x_current = x - x_correct;
        y_current = y - y_correct;
    } else {
        x_current = x;
        y_current = y;
    }
    if(control_state_waypoint) {
        Cal_WayPoint_Error();
    }
}

void Set_Target_WayPoint(int x, int y, int lim) {
    x_target = x;
    y_target = y;
    if(lim < 5) {
        vel_lim = 5;
    } else if(lim > 30) {
        vel_lim = 30;
    } else {
        vel_lim = lim;
    }
}

void Cal_WayPoint_Error() {
    float local_error[2];
    float R[2][2];
    get_rotation_matrix(degrees_to_radians(imu_data.yaw), R);

    // Calculate error in global coordinates
    x_error = x_target - x_current;
    y_error = y_target - y_current;

    // Transform error to drone's local coordinates
    float global_error[2] = {x_error, y_error};
    matrix_vector_multiply(R, global_error, local_error);

    // Use local_error for PID control
    Set_Target_XY(local_error[0], local_error[1], vel_lim);

    if(my_abs(x_error) <= 10 && my_abs(y_error) <= 10) {
        flag_arrive_the_waypoint = 1; //到达航点附近
    } else {
        flag_arrive_the_waypoint = 0;
    }
}

void Correct_Location() {
    x_correct = x_current;
    y_correct = y_current;
    correct_state = 1;
}

// Example function to set target velocity in X and Y directions
void get_rotation_matrix(float theta, float R[2][2]) {
    R[0][0] = cos(theta);
    R[0][1] = -sin(theta);
    R[1][0] = sin(theta);
    R[1][1] = cos(theta);
}

void matrix_vector_multiply(float R[2][2], float vec[2], float result[2]) {
    result[0] = (int)(R[0][0] * vec[0] + R[0][1] * vec[1]);
    result[1] = (int)(R[1][0] * vec[0] + R[1][1] * vec[1]);
}

float degrees_to_radians(float degrees) {
    return degrees * (PI / 180.0);
}*/
#include "User_WayPoint_Control.h"
#include "User_Extend_Data.h"
int x_correct    =    0       ;
int y_correct    =    0       ;
int x_current    =    0       ;
int y_current    =    0       ;
int x_target     =    0       ;
int y_target     =    0       ;
int x_error                   ;
int y_error                   ;
int vel_lim      =    30      ;
u8 correct_state = 0; //修正生效位
u8 control_state_waypoint = 0;
u8 flag_arrive_the_waypoint = 0;  //到达航点标志
void Update_Current_Location(int x,int y)//更新当前位置
{
    if(correct_state)
    {
        x_current = x - x_correct;
        y_current = y - y_correct;
    }
    else{
            x_current = x;
            y_current = y;
    }
		if(control_state_waypoint)
		{
			Cal_WayPoint_Error();
		}
}
void Set_Target_WayPoint(int x,int y,int lim)//设定航点
{
    x_target = x;
    y_target = y;
    if(lim <5)
    {
        vel_lim = 5;
    }
    else if(lim > 30)
    {
        vel_lim = 30;
    }else
    {
        vel_lim = lim;
    }
}

void Cal_WayPoint_Error()//计算xy误差，送入pid
{
    x_error = (x_target - x_current) ;
    y_error = (y_target - y_current) ;
    switch (direction_state)
    {
    case 0:
        Set_Target_XY(x_error,y_error,vel_lim);
        break;
    case 1:
        Set_Target_XY(-y_error,x_error,vel_lim);
        break;
    case 2:
        Set_Target_XY(-x_error,-y_error,vel_lim);
        break;
    case 3:
        Set_Target_XY(y_error,-x_error,vel_lim);
        break;
    }
    if(my_abs(x_error) <= 15 && my_abs(y_error) <= 15)    
    {
        flag_arrive_the_waypoint = 1; //到达航点附近
    }
    else
    {
        flag_arrive_the_waypoint = 0;
    }
}

void Correct_Location()//修正当前坐标
{
    x_correct = x_current;
    y_correct = y_current;
    correct_state = 1;
}
