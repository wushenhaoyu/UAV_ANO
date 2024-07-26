#include "User_Task_Schduler.h"
/* 任务调度器 */
u8 task_state =         0x00;   //任务标志位

u16 user_task_time = 0;

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
     		//稳定航向角
    //User_FlyState_Manager(WAYPOINT_CTRL,CTRL_ON); //稳定起飞位置
}

u32 land_task_time = 0;//降落任务计时
void User_Land_Task_Init()
{
	    EN_XY = 1;//开启openmv识别局部定位
			control_state_openmv_localization = 1;
			control_state_waypoint = 0;
}	
/**
 * @brief 精准降落任务，返回值0正在进行，返回值1代表完成
 */
u8 User_Land_Task(u8 ms)//精准降落任务
{
    if(flag_stable == 2) //达到一级稳定状态
    {
        land_task_time += ms;
        if(land_task_time == 1000)//稳定超过1秒钟
        {
						EN_XY = 0;
            Program_Ctrl_User_Set_HXYcmps(0,0);//狠狠的定点
            one_key_land();
        }
				if(flag.auto_take_off_land == AUTO_LAND)
        {
            land_task_time = 0;
            return 1;
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
