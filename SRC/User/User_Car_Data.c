#include "User_Car_Data.h"
#include <cstdint>
#include <cstring>
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
void Deal_With_Car_Data(u8 func ,u8 *data)
{
		switch(func)
		{
			case 0x01:
						Target_num1 = data[0];
						Target_num2 = data[1];
						Beep();
			break;
			case 0x02:
				
			break;
		}
	}

void User_Car_DataSend(u8 *data ,u8 func ,u8 length)
{
    unsigned char header = 0xAB; // Header byte
    unsigned char trailer = 0xCD; // Trailer byte
    Uart5_Send(&header, 1);
    Uart5_Send(&func, 1);
    Uart5_Send(data, length);
    Uart5_Send(&trailer, 1);
}

void User_Debug_DataSend(float *data, uint8_t length)
{
    // 数据缓冲区，预留足够的空间存放所有数据和结束标志
    static uint8_t buffer[256]; // 根据实际情况调整大小
    uint8_t pos = 0;

    // 循环遍历传入的浮点数数组
    for (uint8_t i = 0; i < length; ++i) {
        // 将浮点数转换为字节序列并添加到缓冲区
        memcpy(buffer + pos, &data[i], sizeof(float));
        pos += sizeof(float);
    }

    // 结束标志
    const uint8_t trailer[] = {0x00, 0x00, 0x80, 0x7F};
    // 添加结束标志到缓冲区
    memcpy(buffer + pos, trailer, sizeof(trailer));
    pos += sizeof(trailer);

    // 使用Uart5_Send发送数据
    Uart5_Send(buffer, pos);
}
