#include "User_Extend_Data.h"
/*拓展开发板通信*/
#include <stdio.h>  // 包含 sprintf 函数
#include <stdint.h> // 包含 int32_t 类型
#include <string.h>
u8 u2_data_reg[56]           ;
u8 u2_state = IDLE;
u8 u2_func = 0;
u8 u2_len_= 0;
u8 u2_len_reg = 0;
void User_Extend_DataRecieve(u8 data) //length = 8
{
    switch (u2_state)
    {

    case IDLE:
        if(data == 0xAA)
            u2_state = CHECK;
        break;
    case CHECK:
            u2_func = data;
            u2_state = LEN;
        break;
    case LEN:
        u2_len_= data;
        u2_len_reg = 0;
        u2_state = WORK;
        break;
    case WORK:
        if(u2_len_reg < u2_len_)
        {
            u2_data_reg[u2_len_reg] = data;
            u2_len_reg++;
        }
        if(u2_len_reg == u2_len_)
        {
            u2_state = END;
        }
        break;
    case END:
        if(data == 0xAF)
        {
            Deal_With_Extend_Data(u2_func,u2_len_,u2_data_reg);
        }
        u2_len_ = 0;
        u2_state = IDLE;
        u2_len_reg = 0;
        u2_func = 0;
        break;

    }
}

void Deal_With_Extend_Data(u8 u2_func, u8 len, u8 *data)
{
    switch (u2_func)
    {
    case 0x01:
        if (len >= 4) {
            int16_t x = (data[0] << 8) | data[1];
            int16_t y = (data[2] << 8) | data[3];
            Update_Current_Location(x,y);
            // 在这里处理x和y坐标
            // 例如：printf("X: %d, Y: %d\n", x, y);
        }
        break;
    case 0x02:
        break;
    case 0x03:
        // 处理0x03功能的代码
        break;
    }
}

void User_Extend_DataSend(u8 func,u8 len,u8 *data)
{
    u8 f = 0xAA;
    u8 t = 0XAF;
    Usart2_Send(&f,1);
    Usart2_Send(&func,1);
    Usart2_Send(&len,1);
    Usart2_Send(data,len);
    Usart2_Send(&t,1);

}
void Beep()
{
    u8 data[1] = {0x01};
    User_Extend_DataSend(0x01,1,data);
}

void Laser_Turn_On()
{
    u8 data[1] = {0x01};
    User_Extend_DataSend(0x02,1,data);
}

void Laser_Turn_Off()
{
    u8 data[1] = {0x00};
    User_Extend_DataSend(0x02,1,data);
}