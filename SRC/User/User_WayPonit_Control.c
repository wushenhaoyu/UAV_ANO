#include "User_WayPoint_Control.h"
float x_current;
float y_current;
float x_target;
float y_target;
float x_error;
float y_error;
u8 control_state_waypoint = 0;
void Update_Current_Location(float x,float y)
{
    x_current = x;
    y_current = y;
}
void Set_Target_WayPoint(float x,float y)
{
    x_target = x;
    y_target = y;
}

void Cal_WayPoint_Error()
{
    x_error = x_target - x_current;
    y_error = y_target - y_current;
    Set_Target_XY(x_error,y_error);
}

void User_WayPoint_Control(float dT_s)
{
    if(control_state_waypoint == 1 && flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
    {
        User_PID_XY_Ctrl(dT_s);
    }
}

