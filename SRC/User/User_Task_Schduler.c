#include "User_Task_Schduler.h"
/* 任务调度器 */
u8 task_state =         0x00;   //任务标志位

u16 user_task_time = 0;
/**
 * @brief 管理飞行状态
 * 
 * @param state 飞行状态标识 
 * 
 * @param action 进行动作
 */
void User_FlyState_Manager(u8 state,u8 action)//管理飞行状态
{
    switch (state)
    {
    case HEIGHT_CTRL:
        /*高度环应该一直保持*/
        break;
    
    case YAW_CTRL://航角指定
        if(action == CTRL_ON)
            control_state_yaw = 1;
        else if(action == CTRL_OFF)
            control_state_yaw = 0;
        break;
    
    case WAYPOINT_CTRL://航点规划两者共用XY轴PID无法同时使用
        if(action == CTRL_ON)
        {
            control_state_waypoint = 1;
            control_state_openmv_localization = 0;
        }
        else if (action == CTRL_OFF)
            control_state_waypoint = 0;
        break;
    
    case OPENMV_DXDY_CTRL://openmv精确定位
        if(action == CTRL_ON)
            {
                control_state_openmv_localization = 1;
                control_state_waypoint = 0;
            }
        else if (action == CTRL_OFF)
            control_state_openmv_localization = 0;
        break;
    }
    
}
void User_Task_Schduler(u8 ms)
{
    /*未完待续*/
    switch (task_state)
    {
        case 0x00:
            user_task_time = 0;
            return;
        break;
        case 0x01:
        break;
        case 0x02:
        break;
        case 0x03:
        {

        }
            
            
        break;
    }
}

void Set_Task_State(u8 data)
{
    if(task_state == data)
    {
        return;
    }
    task_state = data;
    user_task_time = 0;
}
