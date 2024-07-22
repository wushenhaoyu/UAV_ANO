#include "User_PID_Height.h"
/* PID高度环 */
_PID_arg_st height_arg;
_PID_val_st height_val;
float height_target;
float exp_;
float feedback;
void User_PID_Height_Init()//请放在All_PID_Init里面
{
    height_arg.kp = Ano_Parame.set.pid_user_height[KP];
    height_arg.ki = Ano_Parame.set.pid_user_height[KI];
    height_arg.kd_ex = 0.00f;
    height_arg.kd_fb = Ano_Parame.set.pid_user_height[KD];
    height_arg.k_ff = 0.0f;
    height_target = Ano_Parame.set.auto_take_off_height;
}

void User_PID_Height_Ctrl(float dT_s)
{   
    static float height_out = 0.0f;
    if(flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH)
    {
        exp_ = height_target;
        feedback = jsdata.of_alt;
        PID_calculate(
            dT_s,
            0,
            exp_,
            feedback,
            &height_arg,
            &height_val,    
            50,             //积分误差限幅
            10              //积分限幅
        );
        height_out = height_val.out;
        Program_Ctrl_User_Set_Zcmps(LIMIT(height_out,-15,20));
    }
}

void Set_Target_Height(float data)
{
    if(data <0.4)
    {
        height_target = 0.4;
    }
    else if(data >1.8)
    {
        height_target = 1.8;
    }
    else
    {
        height_target = data;
    }
}

