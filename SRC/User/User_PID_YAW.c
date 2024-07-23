#include "User_PID_yaw.h"
#include <stdio.h>
#include <math.h>
/* PID航向角环 */
_PID_arg_st yaw_arg;
_PID_val_st yaw_val;
float yaw_target;
float yaw_exp_;
float yaw_feedback;
float yaw_error;
u8    control_state_yaw = 1;
void User_PID_yaw_Init()//请放在All_PID_Init里面
{
    yaw_arg.kp = Ano_Parame.set.pid_user_Yaw[KP];
    yaw_arg.ki = Ano_Parame.set.pid_user_Yaw[KI];
    yaw_arg.kd_ex = 0.00f;
    yaw_arg.kd_fb = Ano_Parame.set.pid_user_Yaw[KD];
    yaw_arg.k_ff = 0.0f;
    yaw_target = imu_data.yaw;
}

// 规范化角度到-180到180度范围
// 规范化角度到-180到180度范围
float NormalizeAngle(float angle) {
    while (angle > 180.0f) angle -= 360.0f;
    while (angle < -180.0f) angle += 360.0f;
    return angle;
}

// 计算最短路径误差，确保不跨越180度至-180度
float CalculateShortestPathError(float target, float current) {
    float diff = target - current;
    if (diff > 180.0f) {
        diff -= 360.0f; // 从负方向移动
    } else if (diff < -180.0f) {
        diff += 360.0f; // 从正方向移动
    }
    return diff;
}

// PID控制函数，使用最短路径误差
void User_PID_yaw_Ctrl(float dT_s)
{   
    static float yaw_out = 0.0f;
    if(flag.auto_take_off_land == AUTO_TAKE_OFF_FINISH && control_state_yaw )
    {
        // 规范化目标角度
        yaw_exp_ = NormalizeAngle(yaw_target);

        // 规范化反馈角度
        yaw_feedback = NormalizeAngle(imu_data.yaw);

        // 使用最短路径误差
				yaw_error = CalculateShortestPathError(yaw_target,yaw_feedback);

        // 调整PID_calculate函数以使用误差而非直接的目标和反馈值
        PID_calculate(
            dT_s,
            0,
            yaw_error,
            0, 
            &yaw_arg,
            &yaw_val,    
            50,             //积分误差限幅
            10              //积分限幅
        );

        yaw_out = yaw_val.out;
        Program_Ctrl_User_Set_YAWdps(LIMIT(yaw_out,-30,30));

        // 创建一个更大的字符串缓冲区以容纳两个浮点数
        //char yaw_str[64]; // 增加缓冲区大小以防万一
        // 格式化字符串，包含imu_data.yaw和yaw_out
        //snprintf(yaw_str, sizeof(yaw_str), "IMU Yaw: %.2f, Yaw Out: %.2f", imu_data.yaw, yaw_out);
        
        // 发送包含两个值的字符串
        //AnoDTSendStr(USE_HID|USE_U2,SWJ_ADDR,LOG_COLOR_GREEN,yaw_str);
    }
}

void Set_Target_yaw(float data)
{
    // Normalize the angle to be within -180 to 180 degrees
    while (data > 180.0f) {
        data -= 360.0f;
    }
    while (data < -180.0f) {
        data += 360.0f;
    }

    // Now assign the normalized value to yaw_target
    yaw_target = data;
}

