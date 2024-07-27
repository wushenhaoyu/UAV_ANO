#include "User_WayPoint_Control.h"
int x_current    =    0       ;
int y_current    =    0       ;
int x_target     =    0       ;
int y_target     =    0       ;
int x_error                   ;
int y_error                   ;
u8 control_state_waypoint = 0;
u8 flag_arrive_the_waypoint = 0;  //到达航点标志
void Update_Current_Location(int x,int y)//更新当前位置
{
    x_current = x;
    y_current = y;
		if(control_state_waypoint)
		{
				Cal_WayPoint_Error();
		}
}
void Set_Target_WayPoint(int x,int y)//设定航点
{
    x_target = x;
    y_target = y;
}

void Cal_WayPoint_Error()//计算xy误差，送入pid
{
    x_error = x_target - x_current;
    y_error = y_target - y_current;
    Set_Target_XY(-y_error,x_error,30);
    if(x_error <= 5 && y_error <= 5)
    {
        flag_arrive_the_waypoint = 1; //到达航点附近
    }
}


