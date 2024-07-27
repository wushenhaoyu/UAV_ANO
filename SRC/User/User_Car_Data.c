#include "User_Car_Data.h"
#include <stdio.h>  // 包含 sprintf 函数
#include <stdint.h> // 包含 int32_t 类型
#include <string.h>
u8 u5_data_reg[56]           ;
u8 u5_state = IDLE;
u8 u5_func = 0;
u8 u5_len_= 0;
u8 u5_len_reg = 0;
void User_Car_DataRecieve(u8 data)
{
    switch (u5_state)
    {

    case IDLE_:
        if(data == 0xFF)
            u5_state = CHECK;
            Uart5_Send(&data,1);
        break;
    case CHECK_:
            u5_func = data;
            u5_state = WORK;
        break;
    case WORK_:
        if(u5_len_reg < u5_len_)
        {
            u5_data_reg[u5_len_reg] = data;
            u5_len_reg++;
        }
        if(u5_len_reg == u5_len_)
        {
            u5_state = END;
        }
        break;
    case END_:
        if(data == 0xFE)
        {
            Deal_With_OPENMV_Data(u5_func,u5_len_,u5_data_reg);
        }
        u5_len_ = 0;
        u5_state = IDLE;
        u5_len_reg = 0;
        u5_func = 0;
        break;

    }
}

void User_Car_DataSend(u8 *data ,u8 func ,u8 length)
{
    unsigned char header = 0xFF; // Header byte
    unsigned char trailer = 0xFE; // Trailer byte
    Uart5_Send(&header, 1);
    Uart5_Send(&func, 1);
    Uart5_Send(data, length);
    Uart5_Send(&trailer, 1);

}