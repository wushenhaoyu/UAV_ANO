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
                            Set_Target_Height(150);//锁定高度
                            Program_Ctrl_User_Set_HXYcmps(0,0);//锁定xy速度
                            Correct_Location();//坐标修正
                        }
						break;
                    case 1:
                        Task_One_Time_Stamp = Task_One_Time;
                        Set_Target_WayPoint(0,0,5);
                        Task_One_state_flag = 2;
                            //EN_XY = 1;
                            //control_state_waypoint = 1;
                           // Set_Target_WayPoint(60,200,10);//设定航点
                        break;
                    case 2:
                        if(Task_One_Time - Task_One_Time_Stamp >= 2000 && flag_arrvie_the_yaw)//给2s认为航向调整到右方
                            {
                                Set_Target_Height(140); //识别第一行信息
                                EN_XY = 1;
                                control_state_waypoint = 1;
                                Set_Target_WayPoint(0,200,10);//设定航点 识别 A3 -> A2 -> A1
                                Task_One_state_flag = 3;
                                Task_One_Time_Stamp = Task_One_Time;
                            }
                        break;
                    case 3:
                        if(flag_arrive_the_waypoint && Task_One_Time - Task_One_Time_Stamp >= 1000) //认为到底航点附近
                            {
                                Set_Target_Height(100);
                                Task_One_state_flag = 4;
                                Task_One_Time_Stamp = Task_One_Time;
																User_Car_DataSend(&line,0x02,1);
                            }
                            break;
                    case 4:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000)//给1s去下降40cm
                        {
                            Set_Target_WayPoint(0,-50,10); //识别 A6 -> A5 -> A4
                            Task_One_state_flag = 5;
                            Task_One_Time_Stamp = Task_One_Time;
                        }
                        break;
                    case 5:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
														User_Car_DataSend(&line,0x02,1);
                            Set_Target_WayPoint(150,-50,10);//走到B墙下面
                            Task_One_state_flag = 6;
                            Task_One_Time_Stamp = Task_One_Time;
                        }
                        break;
                    case 6:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
                            Set_Target_WayPoint(150,-50,1);
                            Set_Direction(2,15);//转向左边当前高度为下层
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 7;
                        }
                    case 7:
                        if(Task_One_Time - Task_One_Time_Stamp >= 3000 && flag_arrvie_the_yaw)
                        {
                            Set_Target_WayPoint(150,200,10);//识别B4 -> B5 -> B6
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 8;
                        }
                        break;
                    case 8:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
														User_Car_DataSend(&line,0x02,1);
                            Set_Target_Height(140);
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 9;
                        }
                    case 9:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000)
                        {
                            Set_Target_WayPoint(150,0,10);//识别B3 -> B2 -> B1
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 10;
                        }
                    case 10:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
														User_Car_DataSend(&line,0x02,1);
                            Set_Target_WayPoint(150,0,1);
                            Set_Direction(0,15);//转向右面
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 11;
                        }
                    case 11:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrvie_the_yaw)
                        {
                            Set_Target_WayPoint(200,0,10);
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 12;
                        }
                    case 12:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
                            Set_Target_WayPoint(200,200,10);//识别C3 -> C2 -> C1
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 13;
                        }
                    case 13:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
														User_Car_DataSend(&line,0x02,1);
                            Set_Target_Height(100);
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 14;
                        }
                    case 14:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000)
                        {
                            Set_Target_WayPoint(200,-50,10);//识别C4 -> C5 -> C6
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 15;
                        }
                    case 15:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
														User_Car_DataSend(&line,0x02,1);
                            Set_Target_WayPoint(350,-50,10);
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 16;
                        }
                    case 16:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
                            Set_Target_WayPoint(350,-50,1);//旋转限幅
                            Set_Direction(2,15);
                            Task_One_Time_Stamp = Task_One_Time;//转向D面
                            Task_One_state_flag = 17;
                        }
                    case 17:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrvie_the_yaw)
                        {
                            Set_Target_WayPoint(350,200,10);
                            Task_One_Time_Stamp = Task_One_Time;//识别D4 -> D5 -> D6
                            Task_One_state_flag = 18;
                        }
                    case 18:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
														User_Car_DataSend(&line,0x02,1);
                            Set_Target_Height(140);
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 19;
                        }
                    case 19:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000)
                        {
                            Set_Target_WayPoint(350,0,10);
                            Task_One_Time_Stamp = Task_One_Time;//识别D3 -> D2 -> D1
                            Task_One_state_flag = 20;
                        }
                    case 20:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
														User_Car_DataSend(&line,0x02,1);
                            Set_Target_WayPoint(350,250,10);
                            Task_One_Time_Stamp = Task_One_Time;
                            Task_One_state_flag = 21;
                        }
                    case 21:
                        if(Task_One_Time - Task_One_Time_Stamp >= 1000 && flag_arrive_the_waypoint)
                        {
                            control_state_waypoint = 0;
                            control_state_openmv_localization = 1;
                            Program_Ctrl_User_Set_HXYcmps(0,0); //降落前准备
                            Task_One_state_flag = 22;
                        }
                   case 22:
                        User_Land_Task(ms);

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
void Task_tow(u8 ms)
{
			   Task_Two_Time += ms;
			   if ((Task_Two_Time >= 2000)&&(Task_Two_Time < 9000)) //7s起飞
				    {
			            one_key_take_off();
				    }
			   else if(Task_Two_Time >= 9000)
		            {
				         switch(Task_Two_state_flag)
			                 {
				                case 0:
						                 if(flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
                               {
                                Task_Two_state_flag  = 1;
                                Set_Target_yaw(0,15); 
                                Set_Target_Height(150);
                                Program_Ctrl_User_Set_HXYcmps(0,0);
                                Correct_Location();
                               }
						            break;
				                case 1:
								              switch(Target_num1)
										          {
         case 1:
										     EN_XY = 1;
                control_state_waypoint = 1;
                Set_Target_WayPoint(200,0,10); 
									       switch(Task_Two_state_flag2)
									       {
									       case 0:
									             if(flag_arrive_the_waypoint)
												         {
													        Task_Two_state_flag2=1;
												         }
												 break;
												 case 1:
												       switch(Target_num2)
														   {	
															     case 1:
																		      AC123(0,0,0,0,0,0,0,0,30);break;
																	 case 2:
																		      AC123(0,0,0,0,0,0,0,0,30);break;
																	 case 3:
																		      AC123(0,0,0,0,0,0,0,0,30);break;
																	 case 4:
																		      AC456(0,0,0,0,0,0,0,0,30);break;
																	 case 5:
																		      AC456(0,0,0,0,0,0,0,0,30);break;
																	 case 6:
																	        AC456(0,0,0,0,0,0,0,0,30);break;
														   }
													break;		 
													}
					         break;
									 case 2:
										     EN_XY = 1;
            control_state_waypoint = 1;
            Set_Target_WayPoint(200,0,30); 
									       switch(Task_Two_state_flag2)
									       {
									       case 0:
									             if(flag_arrive_the_waypoint)
												         {
													        Task_Two_state_flag2=1;
												         }
												 break;
												 case 1:
												       switch(Target_num2)
														   {	
															     case 1:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 2:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 3:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 4:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 5:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 6:
																	        BD123(0,0,0,0,0,0,0,0,30);break;
														   }
													break;		 
													}
					         break;
									 case 3:
										     EN_XY = 1;
            control_state_waypoint = 1;
            Set_Target_WayPoint(200,0,30); 
									       switch(Task_Two_state_flag2)
									       {
									       case 0:
									             if(flag_arrive_the_waypoint)
												         {
													        Task_Two_state_flag2=1;
												         }
												 break;
												 case 1:
												       switch(Target_num2)
														   {	
															     case 1:
																		      AC123(0,0,0,0,0,0,0,0,30);break;
																	 case 2:
																		      AC123(0,0,0,0,0,0,0,0,30);break;
																	 case 3:
																		      AC123(0,0,0,0,0,0,0,0,30);break;
																	 case 4:
																		      AC456(0,0,0,0,0,0,0,0,30);break;
																	 case 5:
																		      AC456(0,0,0,0,0,0,0,0,30);break;
																	 case 6:
																	        AC456(0,0,0,0,0,0,0,0,30);break;
														   }
													break;		 
													}
					         break;
									 case 4:
										     EN_XY = 1;
                            control_state_waypoint = 1;
                            Set_Target_WayPoint(200,0,30); 
									       switch(Task_Two_state_flag2)
									       {
									       case 0:
									             if(flag_arrive_the_waypoint)
												         {
													        Task_Two_state_flag2=1;
												         }
												 break;
												 case 1:
												       switch(Target_num2)
														   {	
															     case 1:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 2:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 3:
																		      BD123(0,0,0,0,0,0,0,0,30);break;
																	 case 4:
																		      BD456(0,0,0,0,0,0,0,0,30);break;
																	 case 5:
																		      BD456(0,0,0,0,0,0,0,0,30);break;
																	 case 6:
																	        BD456(0,0,0,0,0,0,0,0,30);break;
														   }
													break;		 
													}
					         break;
			                        }
									      }
							}			 
}









void AC123(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim)
{
static u8 state=0; 
switch(state)	
      {
	     case 0:
				     Set_Target_WayPoint(x_1,y_1,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=1;
							 }
		   break;  
       case 1:
             Set_Target_WayPoint(x_2,y_2,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=2;
							 }
       break; 
       case 2:
             Set_Target_WayPoint(x_3,y_3,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=3;
							 }
       break; 							 
       case 3:
             Set_Target_WayPoint(x_4,y_4,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=4;
							 }
       break;
			 case 4:

								  one_key_land();
							 
       break;				 

      }
}







void AC456(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim)
{
static u8 state=0; 
static u32 time1=0; 
static u32 time2=0;
switch(state)	
      {
	     case 0:
				     Set_Target_WayPoint(x_1,y_1,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=1;
							 }
		   break;  
       case 1:
             Set_Target_Height(100); 
			       time1+=20;
				     if( time1>=5000)
						   {
								  state=2;
							 }
       break; 
       case 2:
             Set_Target_Height(140);
	           time2+=20;
				     if( time2>=5000)
						   {
								  state=3;
							 }
       break; 							 
       case 3:
             Set_Target_WayPoint(x_2,y_2,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=4;
							 }
       break;
			 case 4:
             Set_Target_WayPoint(x_3,y_3,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=5;
							 }
       break;				 
			 case 5:
             Set_Target_WayPoint(x_4,y_4,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=6;
							 }
       break;	
		   case 6:
              one_key_land();
       break;
      }
}

void BD123(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim)
{
static u8 state=0; 
static u32 time1=0; 
static u32 time2=0;
switch(state)	
      {
	     case 0:
				     Set_Target_yaw(2,15); 
			       time1+=20;
				     if(time1>=5000&&flag_arrvie_the_yaw)
						   {
								  state=1;
							 }
		   break;  
       case 1:
             Set_Target_WayPoint(x_1,y_1,lim);
             if(flag_arrive_the_waypoint)
						   {
								  state=2;
							 }
       break; 
       case 2:
             Set_Target_WayPoint(x_2,y_2,lim);
             if(flag_arrive_the_waypoint)
						   {
								  state=3;
							 }
       break; 							 
       case 3:
				     Set_Target_yaw(0,15); 
			       time2+=20;
				     if(time2>=5000&&flag_arrvie_the_yaw)
						   {
								  state=4;
							 }
       break;
			 case 4:
             Set_Target_WayPoint(x_3,y_3,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=5;
							 }
       break;				 
			 case 5:
             Set_Target_WayPoint(x_4,y_4,lim); 
				     if(flag_arrive_the_waypoint)
						   {
								  state=6;
							 }
       break;	
		   case 6:
              one_key_land();
       break;
      }
		}

		
void BD456(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4,int lim)
{
static u8  state=0; 
static u32 time1=0; 
static u32 time2=0;
static u32 time3=0; 
static u32 time4=0;
switch(state)
{
	case 0:
				 Set_Target_yaw(2,15); 
			   time1+=20;
				 if(time1>=5000&&flag_arrvie_the_yaw)
					 {
					  state=1;
					 }
	break;  
	case 1:
				 Set_Target_WayPoint(x_1,y_1,lim);
         if(flag_arrive_the_waypoint)
				 {
				   state=2;
				 }
  break;
  case 2:
         Set_Target_Height(100); 
			   time2+=20;
				 if( time2>=5000)
				{
					state=3;
				}
  break; 
  case 3:
        Set_Target_Height(140);
	     time3+=20;
			  if( time3>=5000)
				{
				 state=4;
				}
  break;							 
	case 4:
				 Set_Target_WayPoint(x_2,y_2,lim);
         if(flag_arrive_the_waypoint)
				 {
				   state=5;
				 }
  break;
	case 5:
				 Set_Target_yaw(0,15); 
			   time4+=20;
				 if(time4>=5000&&flag_arrvie_the_yaw)
					 {
					  state=6;
					 }
	break; 				 
	case 6:
				 Set_Target_WayPoint(x_3,y_3,lim);
         if(flag_arrive_the_waypoint)
				 {
				   state=7;
				 }
  break;	
	case 7:
				 Set_Target_WayPoint(x_4,y_4,lim);
         if(flag_arrive_the_waypoint)
				 {
				   state=8;
				 }
  break;
	case 8:
				 one_key_land();
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
            Set_Target_Height(20);
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
                            Set_Target_WayPoint(60,200,30);//设定航点
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
                                Set_Target_Height(140); //识别第一行信息
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