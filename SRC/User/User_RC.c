#include "User_RC.h"
#include "Ano_Parameter.h"
#include "User_OPENMV_Cal.h"
#include <stdio.h>
/* 遥控器逻辑 */
u16 RC_task_time_2 = 0;
u16 RC_task_time_3 = 0;
void RC_task(u8 ms)
{
    if(rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1950)
    {
				RC_task_time_2 += ms;
				if(RC_task_time_2 == 3000)
				{
						one_key_take_off();
				}
				/*else if (RC_task_time_2 == 10000)
				{
					Program_Ctrl_User_Set_HXYcmps(10,0);
				}
				else if (RC_task_time_2 == 13000)
				{
					Program_Ctrl_User_Set_HXYcmps(0,10);
				}
				else if (RC_task_time_2 == 16000)
				{
					Program_Ctrl_User_Set_HXYcmps(-10,10);
				}
				else if (RC_task_time_2 == 19000)
				{
					Program_Ctrl_User_Set_HXYcmps(0,0);
				}
				else if (RC_task_time_2 == 20000)
				{
					one_key_land();
				}*/
				
				/*else if(RC_task_time_2 == 10000)
				{
					EN_XY = 1;
					control_state_waypoint = 1;
				}
				else if(RC_task_time_2 == 11000)
				{
					Set_Target_WayPoint(100,0);
				}
				else if(RC_task_time_2 == 20000)
				{
					Set_Target_WayPoint(x_current,y_current);
				}
				else if(RC_task_time_2 == 21000)
				{
					EN_XY = 0;
					control_state_waypoint = 0;
				}
				else if(RC_task_time_2 == 22000)
				{
					one_key_land();
				}*/
    }
    else{
        if(RC_task_time_2 > 0)
				{
                    //AnoDTSendStr(USE_HID|USE_U2,SWJ_ADDR,LOG_COLOR_GREEN,"0");
					RC_task_time_2 = 0;
					one_key_land();
				}
        
    }

    if(rc_in.rc_ch.st_data.ch_[ch_7_aux3] > 1950)
    {
				 RC_task_time_3 += ms;
					if(RC_task_time_3 == 1000)
					{
							EN_XY = 1;
							control_state_openmv_localization = 1;
							//User_FlyState_Manager(OPENMV_DXDY_CTRL,CTRL_ON);
						//User_FlyState_Manager(WAYPOINT_CTRL,CTRL_ON);
					}
					/*else if(RC_task_time_3 == 2000)
					{
							Set_Target_WayPoint(100,100);
					}*/
        
    }
    else
    {
                if(RC_task_time_3 > 0)
				{
                    //AnoDTSendStr(USE_HID|USE_U2,SWJ_ADDR,LOG_COLOR_GREEN,"0");
							RC_task_time_3 = 0;
							EN_XY = 0;
							control_state_openmv_localization = 0;
					//User_FlyState_Manager(OPENMV_DXDY_CTRL,CTRL_OFF);
					//Set_Target_WayPoint(x_current,y_current);
					//User_FlyState_Manager(WAYPOINT_CTRL,CTRL_OFF);
				}
    }
		
}
