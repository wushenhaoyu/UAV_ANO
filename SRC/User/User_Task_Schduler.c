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
						EN_XY = 1;
            control_state_waypoint = 1;
            control_state_openmv_localization = 0;
        }
        else if (action == CTRL_OFF)
						EN_XY = 0;
            control_state_waypoint = 0;
        break;
    
    case OPENMV_DXDY_CTRL://openmv精确定位
        if(action == CTRL_ON)
            {
								EN_XY = 1;
                control_state_openmv_localization = 1;
                control_state_waypoint = 0;
            }
        else if (action == CTRL_OFF)
						EN_XY = 0;
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
/**
* @brief 起飞任务初始化
*/
void User_TakeOff_Init(u8 ms)
{
    //Set_Target_WayPoint();						//需要设定起飞坐标位置
    User_FlyState_Manager(YAW_CTRL,CTRL_ON); 		//稳定航向角
    //User_FlyState_Manager(WAYPOINT_CTRL,CTRL_ON); //稳定起飞位置
}

u8 land_task_time = 0;//降落任务计时
/**
 * @brief 精准降落任务，返回值0正在进行，返回值1代表完成
 */
u8 User_Land_Task(u8 ms)//精准降落任务
{
    User_FlyState_Manager(OPENMV_DXDY_CTRL,CTRL_ON); //开启openmv识别局部定位
    if(flag_stable == 2) //达到一级稳定状态
    {
        land_task_time += ms;
        if(land_task_time >= 1000)//稳定超过1秒钟
        {
            Program_Ctrl_User_Set_HXYcmps(0,0);//狠狠的定点
            one_key_land();
            if(flag.auto_take_off_land == AUTO_LAND)
            {
                land_task_time = 0;
                return 1;
            }
        }
    }
    
    return 0;

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
