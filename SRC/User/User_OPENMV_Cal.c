#include "User_OPENMV_Cal.h"
/**在80cm定高飞行条件下1像素对应0.316cm */
#define PIXEL_CM 0.316
int32_t pixel_dx_ = 0;
int32_t pixel_dy_ = 0;
float real_dx_ = 0;
float real_dy_ = 0;
u8 control_state_openmv_localization = 0;

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
				if(real_dx < 5 && real_dy_ <5)
				{
					Set_Target_XY(0,0);
				}
				else
				{
					Set_Target_XY(real_dx_,real_dy_);
				}
				
		}
    
}

void Set_OPENMV_DXDY(int32_t dx,int32_t dy)
{
    pixel_dx_ = dx;
    pixel_dy_ = dy;
    User_OPENMV_DXDY_Cal();
}