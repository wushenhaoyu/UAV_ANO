#include "User_OPENMV_Cal.h"
/**在80cm定高飞行条件下1像素对应0.316cm */
#define PIXEL_CM 0.316
int32_t pixel_dx_ = 0;
int32_t pixel_dy_ = 0;
float real_dx_ = 0;
float real_dy_ = 0;
u8 cnt_detect = 0;
u8 control_state_openmv_localization = 0;
u8 flag_stable = 0; //0:不稳定  1:二级稳定状态  2:一级稳定状态
u8 stable_lim = 20;
u8 flag_detect = 0; //是否检测到了物体

void User_OPENMV_Localization(float dT_s)
{
    if(control_state_openmv_localization && flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
    {
        User_PID_XY_Ctrl(dT_s);
    }
}//作废
void User_OPENMV_DXDY_Cal()
{
    real_dx_ = (float)pixel_dy_ * PIXEL_CM;
    real_dy_ = (float)pixel_dx_ * PIXEL_CM;
		if(control_state_openmv_localization)
		{	
				Change_stable_state();
				Set_Target_XY(real_dx_,real_dy_,stable_lim);
		}
    
}
void Change_stable_state()
{
			if(flag_detect)
			{
					switch(flag_stable)
				{
					case 0:
								if(real_dx_ <= 12 && real_dy_ <= 12)
								{
										cnt_detect += 1 ;
								}
									stable_lim = 20;
								if(cnt_detect == 20)
								{
										flag_stable = 1;
										cnt_detect = 0;	
								}
									break;
					case 1:
								if(real_dx_ <= 8 && real_dy_ <= 8)
								{
										cnt_detect += 1 ;
								}
								stable_lim = 10;
								if(cnt_detect == 20)
								{
										flag_stable = 2;
										cnt_detect = 0;	
										stable_lim = 5;
								}
									break;
				}
			}
			flag_detect = 0;
}
void Clear_Flag_Stable()
{
	flag_stable = 0;
	flag_detect = 0;
	stable_lim = 20;
	cnt_detect = 0;
}

void Set_OPENMV_DXDY(int32_t dx,int32_t dy)
{
    pixel_dx_ = dx;
    pixel_dy_ = dy;
    User_OPENMV_DXDY_Cal();
}
