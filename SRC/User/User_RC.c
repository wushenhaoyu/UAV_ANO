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
				/*if(RC_task_time_2 == 100)
				{
					User_TakeOff_Init(ms);
				}*/
				/*if(RC_task_time_2 == 3000)
				{
					one_key_take_off();
				}
				else if(RC_task_time_2 == 8000)
				{
						User_Land_Task_Init();
				}
				else if(RC_task_time_2 > 8000)
				{
						User_Land_Task(ms);
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
							Set_Target_WayPoint(200,200);
							EN_XY = 1;
							control_state_waypoint = 1;
					}
        
    }
    else
    {
                if(RC_task_time_3 > 0)
				{
							EN_XY = 0;
							control_state_waypoint = 0;
							Program_Ctrl_User_Set_HXYcmps(0,0);
				}
    }
		
}
		
