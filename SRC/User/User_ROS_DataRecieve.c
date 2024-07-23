#include "User_ROS_DataRecieve.h"
#include "include.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
/* ROS数据处理 */
u8 data_reg[56]           ; //RX缓冲区
u8 state        =   IDLE  ; //状态机标志位
u8 func         =   0     ;
u8 len_         =   0     ;
u8 len_reg      =   0     ;
char _str[16];
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
        len_ = data;
        state = WORK;
        len_reg = 0;
        break;
    case WORK:
        if(len_reg < len_)
        {
            data_reg[len_reg] = data;
            len_reg++;
        }
        if(len_reg == len_)
        {
            state = END;
        }
        break;
    case END:
        if(data == 0xAF)
        {
            Deal_With_ROS_Data(func, len_, data_reg);
        }
        len_ = 0;
        state = IDLE;
        len_reg = 0;
        func = 0;
        break;
    
    }
}

void Deal_With_ROS_Data(u8 func,u8 len,u8 *data)
{

    switch(func)
    {
        //0x01 树莓派发送雷达坐标 9字节 x坐标 单位 米 、 y坐标 单位 米、是否有效位 
        case 0x01:
						User_DataSend(0x02,0x08,data);
            float x_, y_;

            // 解包数据
            memcpy(&x_, data, sizeof(float));
            memcpy(&y_, data + sizeof(float), sizeof(float));
						Update_Current_Location(x_,y_);
            break;
        //0x02  设置任务状态 1位 
        case 0X02:
            if(len ==  1)
                {
                   // Set_Task_State(data[0]);
                }
            break;
        //0x03 设置飞行控制权 1位 
        case 0x03:
            if(len == 1)
                {
                    //Set_Control_State(data[0]);
                }
            break;
        case 0x04:
            if(len == 1)
            {
               // Set_Target_Height(data[0]);
            }

    }
}
