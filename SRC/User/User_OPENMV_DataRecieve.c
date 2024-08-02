#include "User_OPENMV_DataRecieve.h"

#include <stdio.h>  // 包含 sprintf 函数
#include <stdint.h> // 包含 int32_t 类型
#include <string.h>
u8 u3_data_reg[56]           ;
u8 u3_state = IDLE;
u8 u3_func = 0;
u8 u3_len_= 0;
u8 u3_len_reg = 0;
void User_OPENMV_DataRecieve(u8 data) //length = 8
{
    switch (u3_state)
    {

    case IDLE:
        if(data == 0xAA)
            u3_state = CHECK;
        break;
    case CHECK:
            u3_func = data;
            u3_state = LEN;
        break;
    case LEN:
        u3_len_= data;
        u3_len_reg = 0;
        u3_state = WORK;
        break;
    case WORK:
        if(u3_len_reg < u3_len_)
        {
            u3_data_reg[u3_len_reg] = data;
            u3_len_reg++;
        }
        if(u3_len_reg == u3_len_)
        {
            u3_state = END;
        }
        break;
    case END:
        if(data == 0xAF)
        {
            Deal_With_OPENMV_Data(u3_func,u3_len_,u3_data_reg);
        }
        u3_len_ = 0;
        u3_state = IDLE;
        u3_len_reg = 0;
        u3_func = 0;
        break;

    }
}
u8 number_ = 0;
 void	Deal_With_OPENMV_Data(u8 u3_func,u8 len,u8 *data)
 {    
    if(IsInitTaskTwo)
    {
        switch (u3_func)
        {
        case 0x03:
            User_QR_DataSend(0x03,1,data);
            User_Car_DataSend(data,0x03,1);
            IsStartTaskTwo = 1;
            break;
        }
    }else{
        switch (u3_func)
        {
        case 0x01:
            break;
        case 0x02:
            break;
        case 0x03:
            User_Car_DataSend(data,0x02,1);
            break;
        }
    }
 }

void User_OPENMV_DataSend(u8 func,u8 len,u8 *data)
{
    u8 f = 0xAA;
    u8 t = 0XAF;
    Usart1_Send(&f,1);
    Usart1_Send(&func,1);
    Usart1_Send(&len,1);
    Usart1_Send(data,len);
    Usart1_Send(&t,1);

}