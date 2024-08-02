#include "User_PID_XY.h"

_PID_arg_st X_arg;
_PID_arg_st Y_arg;
_PID_val_st X_val;
_PID_val_st Y_val;
u8 EN_XY = 0;
float X_err , Y_err;
float lim_;
#include <stdio.h>

void User_PID_XY_Init()
{
    X_arg.kp = Ano_Parame.set.pid_user_X[KP];
    X_arg.ki = Ano_Parame.set.pid_user_X[KI];
    X_arg.kd_ex = 0.00f;
    X_arg.kd_fb = Ano_Parame.set.pid_user_X[KD];
    X_arg.k_ff = 0.0f;

    Y_arg.kp = Ano_Parame.set.pid_user_Y[KP];
    Y_arg.ki = Ano_Parame.set.pid_user_Y[KI];
    Y_arg.kd_ex = 0.0f;
    Y_arg.kd_fb = Ano_Parame.set.pid_user_Y[KD];
    Y_arg.k_ff = 0.0f;
}

void  User_PID_XY_Ctrl(float dT_s)
{
    static float X_out,Y_out;
    if(flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH && EN_XY )
    {
        PID_calculate(
            dT_s,
            0,
            X_err ,
            0,
            &X_arg,
            &X_val,
            50,
            10
        );
        PID_calculate(
            dT_s,
            0,
            Y_err ,
            0,
            &Y_arg,
            &Y_val,
            50,
            10
        );
        X_out = X_val.out ;
        Y_out = Y_val.out ;
        Program_Ctrl_User_Set_HXYcmps(LIMIT(X_out,-1 * lim_ ,lim_),LIMIT(Y_out,-1 * lim_,lim_));
    }
}

void Set_Target_XY(float X, float Y , float lim )
{
    X_err = X;
    Y_err = Y;
		lim_ = lim;
}
