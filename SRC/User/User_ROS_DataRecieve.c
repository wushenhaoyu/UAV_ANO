#include "User_ROS_DataRecieve.h"

u8 data_reg[56]           ; //RX缓冲区
u8 state        =   IDLE  ; //状态机标志位
u8 func         =   0     ;
u8 len          =   0     ;
u8 len_reg      =   0     ;

/**
 * @brief ROS任务流程数据接收
 */
void User_ROS_DataRecieve(u8 data)
{
    switch (state)
    {
    case IDLE:
        /*第一次校验*/
        if(data == 0xAA)
            state = CHECK;
        break;
    case CHECK:
        func = data;
        state = LEN;
        break;
    case LEN:
        len = data;
        state = WORK;
        len_reg = 0;
    case WORK:
        if(len_reg < len)
        {
            data_reg[len_reg] = data;
            len_reg++;
        }
        if(len_reg == len)
        {
            state = END;
        }
    case END:
        if(data == 0xAF)
        {
            Deal_With_ROS_Data(func, len, data_reg);
        }
        len = 0;
        state = IDLE;
        len_reg = 0;
        func = 0;
    }
}

void Deal_With_ROS_Data(u8 func, u8 len, u8 *data)
{
    switch(func)
    {
        /*0x01 树莓派控制航向 3位浮点数 12位 依次为 x线速度 y线速度 YAW航向角速度*/
        case 0x01:
            if(len == 12)
                {
                    float hx_vel_cmps, hy_vel_cmps, yaw_vel_cmps;
                    memcpy(&hx_vel_cmps, data, sizeof(float));
                    memcpy(&hy_vel_cmps, data + sizeof(float), sizeof(float));
                    memcpy(&yaw_vel_cmps, data + 2 * sizeof(float), sizeof(float));
                    
                    // 调用set_vel函数
                    Set_Vel(hx_vel_cmps, hy_vel_cmps, yaw_vel_cmps);
                }
            break;
        /*0x02  设置任务状态 1位 */
        case 0X02:
            if(len ==  1)
                {
                    Set_Task_State(data[0]);
                }
            break;
        /*0x03 设置飞行控制权 1位 */
        case 0x03:
            if(len == 1)
                {
                    Set_Control_State(data[0]);
                }
            break;

    }
}