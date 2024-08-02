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
u8 line = 0x02;
u32 Task_One_Time = 0;
u32 Task_One_Time_Stamp = 0; //时间标记记录
u8 Task_One_state_flag = 0;
u8 x_state = 0;
u8 z_state = 0;
void Task_One(u8 ms)
{
		Task_One_Time += ms;
		if(Task_One_Time == 200)
		{
				User_TakeOff_Init(ms);
		}
		else if(Task_One_Time == 3000)
		{
				one_key_take_off();
		}
		else if(Task_One_Time >= 3000)
		{
				switch(Task_One_state_flag)
			{
					case 0:
						if(flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
                        {
                            Task_One_state_flag  = 1;
                            Set_Target_yaw(0,15); //锁定航向
                            Set_Target_Height(140,10);//锁定高度
                            z_state = 1;
                            Program_Ctrl_User_Set_HXYcmps(0,0);//锁定xy速度
                            //Correct_Location();//坐标修正
                        }
						break;
                    case 1:
                        EN_XY = 1;
                        control_state_waypoint = 1;
                        Set_Target_WayPoint(75,75,5);
                        Task_One_state_flag = 2;
                            //EN_XY = 1;
                            //control_state_waypoint = 1;
                           // Set_Target_WayPoint(60,180,10);//设定航点
                        break;
                    case 2:
                        if(flag_arrive_the_waypoint)
                            {
                                Task_One_Time_Stamp += ms;
                                if(Task_One_Time_Stamp >= 500)
                                {
                                     Correct_Location();
                                    Set_Target_WayPoint(0,0,10);
                                    Task_One_state_flag = 3;
                                    Task_One_Time_Stamp = 0;
                                }
                            }break;
                    case 3:
                        if(flag_arrive_the_waypoint)
                            {
                                Task_One_Time_Stamp += ms;
                                if(Task_One_Time_Stamp >= 500)
                                {
                                    Set_Target_WayPoint(-20,0,10);
                                    Task_One_state_flag = 4;
                                    Task_One_Time_Stamp = 0;
                                }
                            }
                        break;
                        case 4: if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                                Set_Target_WayPoint(-20,200,10);//设定航点 识别 A3 -> A2 -> A1
                                Task_One_state_flag = 5;
                                Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 5:
                        if(flag_arrive_the_waypoint) //认为到底航点附近
                            {
                                Task_One_Time_Stamp += ms;
                                if(Task_One_Time_Stamp >= 500)
                                {
                                    Set_Target_Height(110,10);
                                    z_state = 2;
                                    Task_One_state_flag = 6;
                                    
                                    Task_One_Time_Stamp = 0;
                                }
                            }
                            break;
                    case 6:
                        if(flag_arrive_the_height)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                                Set_Target_WayPoint(-20,-25,10); //识别 A6 -> A5 -> A4
                                Task_One_state_flag = 7;
                                Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 7:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                                
                                Set_Target_WayPoint(175,-40,10);//走到B墙下面
                                Task_One_state_flag = 8;
                                Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 8:
                        if(flag_arrive_the_waypoint)
                            {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                                x_state = 2;
                                Set_Target_WayPoint(175,200,10);//识别B4 -> B5 -> B6
                                Task_One_state_flag = 9;
                                Task_One_Time_Stamp = 0;
                            }
                            }
                        break;
                    case 9:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
							
                            Set_Target_Height(140,10);
                            z_state = 1;
                            Task_One_state_flag = 10;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 10:
                        if( flag_arrive_the_waypoint) 
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                            Set_Target_WayPoint(175,-40,10);//识别C4 -> C5 -> C6
                            Task_One_state_flag = 16;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                         break;
                    case 16:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
							
                            Set_Target_WayPoint(350,-40,10);
                            Task_One_state_flag = 17;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                         break;
                    case 17:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                            x_state = 3;
                            Set_Target_WayPoint(350,200,10);
                            //识别D4 -> D5 -> D6
                            Task_One_state_flag = 18;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 18:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                            Set_Target_Height(110,10);
                            z_state = 2;
                            Task_One_state_flag = 19;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 19:
                        if(flag_arrive_the_height)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
							
                            Set_Target_WayPoint(350,-40,10);
                            Task_One_state_flag = 20;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 20:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
							
                            Set_Target_WayPoint(350,250,10);
                            Task_One_state_flag = 21;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 21:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
							
                            Set_Target_WayPoint(350,250,10);
                            Task_One_state_flag = 22;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                   case 22:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                            EN_XY = 0;
                            Program_Ctrl_User_Set_HXYcmps(0,0);
                            Task_One_state_flag = 23;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 23:
                        Program_Ctrl_User_Set_HXYcmps(0,0);
                        one_key_land();
                        break;

			}
		}
}

u32 Task_Two_Time = 0;
u32 Task_Two_Time_Count = 0; 
u8 Task_Two_state_flag = 0;
u8 Task_Two_state_flag2 = 0;
u8 Wait_Time1 = 0;//ms Turning time
u32 Wait_Time2 = 5000;//ms Landing time
u8 Target_num1; // 1:a 2:b 3:c 4:d
u8 Target_num2; // 1 2 3 4 5 6 
u8 IsInitTaskTwo = 0;
u8 IsStartTaskTwo = 0; //
void Task_Two_w(u8 ms)
{
    u8 d = 0x02;
    User_OPENMV_DataSend(0x02,1,&d);
    User_QR_DataSend(0x02,1,&d);
    IsInitTaskTwo = 1;
    if(IsStartTaskTwo)
    {
        //Task_two(ms);
        Task_One_Time += ms;
		if(Task_One_Time == 200)
		{
				User_TakeOff_Init(ms);
		}
		else if(Task_One_Time == 3000)
		{
				one_key_take_off();
		}
		else if(Task_One_Time >= 3000)
		{
				switch(Task_One_state_flag)
			{
					case 0:
						if(flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
                        {
                            Task_One_state_flag  = 1;
                            Set_Target_yaw(0,15); //锁定航向
                            Set_Target_Height(140,10);//锁定高度
                            z_state = 1;
                            Program_Ctrl_User_Set_HXYcmps(0,0);//锁定xy速度
                            //Correct_Location();//坐标修正
                        }
						break;
                    case 1:
                        EN_XY = 1;
                        control_state_waypoint = 1;
                        Set_Target_WayPoint(75,75,5);
                        Task_One_state_flag = 2;
                            //EN_XY = 1;
                            //control_state_waypoint = 1;
                           // Set_Target_WayPoint(60,180,10);//设定航点
                        break;
                    case 2:
                        if(flag_arrive_the_waypoint)
                            {
                                Task_One_Time_Stamp += ms;
                                if(Task_One_Time_Stamp >= 500)
                                {
                                     Correct_Location();
                                    Set_Target_WayPoint(0,0,10);
                                    Task_One_state_flag = 3;
                                    Task_One_Time_Stamp = 0;
                                }
                            }break;
                    case 3:
                        if(flag_arrive_the_waypoint)
                            {
                                Task_One_Time_Stamp += ms;
                                if(Task_One_Time_Stamp >= 500)
                                {
                                    Set_Target_WayPoint(-20,-20,10);
                                    Task_One_state_flag = 4;
                                    Task_One_Time_Stamp = 0;
                                }
                            }
                        break;
                        case 4: if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                                Set_Target_WayPoint(350,-20,5);//设定航点 识别 A3 -> A2 -> A1
                                Task_One_state_flag = 5;
                                Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                     case 5:
                        if(flag_arrive_the_waypoint) //认为到底航点附近
                            {
                                Task_One_Time_Stamp += ms;
                                if(Task_One_Time_Stamp >= 500)
                                {
                                    Set_Target_WayPoint(350,250,5);
                                    z_state = 2;
                                    Task_One_state_flag = 6;
                                    
                                    Task_One_Time_Stamp = 0;
                                }
                            }
                            break;
                    case 7:
                        if(flag_arrive_the_waypoint)
                        {
                            Task_One_Time_Stamp += ms;
                            if(Task_One_Time_Stamp >= 500)
                            {
                            EN_XY = 0;
                            Program_Ctrl_User_Set_HXYcmps(0,0);
                            Task_One_state_flag = 23;
                            Task_One_Time_Stamp = 0;
                            }
                        }
                        break;
                    case 23:
                        Program_Ctrl_User_Set_HXYcmps(0,0);
                        one_key_land();
                        break;
            }
    }
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

			control_state_waypoint = 0;
}	
/**
 * @brief 精准降落任务，返回值0正在进行，返回值1代表完成
 */
u8 User_Land_Task(u8 ms)//精准降落任务
{
		

    
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
//
/*void Task_One(u8 ms)
{
		Task_One_Time += ms;
		if(Task_One_Time == 200)
		{
				User_TakeOff_Init(ms);
		}
		else if(Task_One_Time == 3000)
		{
				one_key_take_off();
		}
		else if(Task_One_Time >= 3000)
		{
				switch(Task_One_state_flag)
			{
					case 0:
						if(flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
                        {
                            Task_One_state_flag  = 1;
                            Set_Target_yaw(0); //锁定航向
                            Set_Target_Height(150);//锁定高度
                            Program_Ctrl_User_Set_HXYcmps(0,0);//锁定xy速度
                            Correct_Location();//坐标修正
                        }
						break;
                    case 1:
                            EN_XY = 1;
                            control_state_waypoint = 1;
                            Set_Target_WayPoint(60,180,30);//设定航点
                        break;
                    case 2:
                        if(flag_arrive_the_waypoint) //认为到底航点附近
                            {
                                Set_Direction(1);//机头朝右
                                Task_One_Time_Stamp = Task_One_Time;
                                Task_One_state_flag = 3;
                            }
                        break;
                    case 3:
                            if(Task_One_Time - Task_One_Time_Stamp >= 2000)//给2s认为航向调整到右方
                            {
                                Set_Target_Height(150); //识别第一行信息
                                //可能还要发位置给openmv？害怕一步错步步接错
                                flag_arrive_the_waypoint = 0;//重置到达标志位
                                Task_One_state_flag = 4;
                            }
                            break;
                    case 4:
                            Set_Target_WayPoint(60,50,30);
                            Task_One_state_flag = 5;
                        break;
                    case 5:
														
											break;
												
			}
		}
		
}*/