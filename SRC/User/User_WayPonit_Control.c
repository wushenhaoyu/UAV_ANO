#include "User_WayPoint_Control.h"
float x_current    =    0       ;
float y_current    =    0       ;
float x_target     =    0       ;
float y_target     =    0       ;
float x_error                   ;
float y_error                   ;
u8 control_state_waypoint = 0;
u8 flag_arrive_the_waypoint = 0;  //到达航点标志
void Update_Current_Location(float x,float y)//更新当前位置
{
    x_current = x;
    y_current = y;
		if(control_state_waypoint)
		{
				Cal_WayPoint_Error();
		}
}
void Set_Target_WayPoint(float x,float y)//设定航点
{
    x_target = x;
    y_target = y;
}

void Cal_WayPoint_Error()//计算xy误差，送入pid
{
    x_error = x_target - x_current;
    y_error = y_target - y_current;
    Set_Target_XY(x_error,y_error);
    if(x_error <= 0.15 && y_error <= 0.15)
    {
        flag_arrive_the_waypoint = 1; //到达航点附近
    }
}

void User_WayPoint_Control(float dT_s)//航点PID控制
{
    if(control_state_waypoint && flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
    {
        Cal_WayPoint_Error();
        User_PID_XY_Ctrl(dT_s);
    }
}//作废

