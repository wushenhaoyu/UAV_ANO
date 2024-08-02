#include "User_QR_Data.h"

/*拓展开发板通信*/
#include <stdio.h>  // 包含 sprintf 函数
#include <stdint.h> // 包含 int32_t 类型
#include <string.h>
u8 u1_data_reg[56]           ;
u8 u1_state = IDLE;
u8 u1_func = 0;
u8 u1_len_= 0;
u8 u1_len_reg = 0;
void User_QR_DataRecieve(u8 data) //length = 8
{
    switch (u1_state)
    {
    case IDLE:
        if(data == 0xAA)
            u1_state = CHECK;
        break;
    case CHECK:
            u1_func = data;
            u1_state = LEN;
        break;
    case LEN:
        u1_len_= data;
        u1_len_reg = 0;
        u1_state = WORK;
        break;
    case WORK:
        if(u1_len_reg < u1_len_)
        {
            u1_data_reg[u1_len_reg] = data;
            u1_len_reg++;
        }
        if(u1_len_reg == u1_len_)
        {
            u1_state = END;
        }
        break;
    case END:
        if(data == 0xAF)
        {
            Deal_With_QR_Data(u1_func,u1_len_,u1_data_reg);
        }
        u1_len_ = 0;
        u1_state = IDLE;
        u1_len_reg = 0;
        u1_func = 0;
        break;
    }
}
u8 number__ = 0;
void Deal_With_QR_Data(u8 u1_func, u8 len, u8 *data)
{
		//Beep();
    if(IsInitTaskTwo)
    {
        switch (u1_func)
        {
            case 0x03:
                User_OPENMV_DataSend(0x03,1,data);
                User_Car_DataSend(data,0x03,1);
                IsStartTaskTwo = 1;
                break;
        }
    }else{
        switch (u1_func)
        {
        case 0x01:
            break;
        case 0x02:
            break;
        case 0x03:
            User_Car_DataSend(data,0x01,0x01);
            Beep();
            break;
        }
    }
}

void User_QR_DataSend(u8 func,u8 len,u8 *data)
{
    u8 f = 0xAA;
    u8 t = 0XAF;
    Usart1_Send(&f,1);
    Usart1_Send(&func,1);
    Usart1_Send(&len,1);
    Usart1_Send(data,len);
    Usart1_Send(&t,1);

}