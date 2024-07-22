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
    Usart3_Send(&data,1);
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

 void	Deal_With_OPENMV_Data(u8 u3_func,u8 len,u8 *data)
 {
	 
    switch (u3_func)
    {
    case 0x01:/*0x01 识别颜色与形状 */
        Identify_Color_Shape(data);
        
        break;
    case 0x02://精准定位返回xy坐标偏差
				Deal_With_XY_Data(data);
        break;
    }
 }


 void Identify_Color_Shape(u8 *data)
 {
    switch (data[0])
    {
        case RED:

            break;
        case BLUE:

            break;

    }
    switch (data[1])
    {
    case CIRCLE:
        break;
    case RECT:
        break;
    case TRIANGLE:
        break;
    }
 }



void Deal_With_XY_Data(uint8_t *data) {
    int32_t x = 0;
    int32_t y = 0;
    //char str[24]; // 足够大以存储格式化字符串

    // 使用类型转换和指针操作解包数据
    x = (int32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
    y = (int32_t)((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]);

    Set_OPENMV_DXDY(x, y);

    // 将 x 和 y 转换为字符串
    //snprintf(str, sizeof(str), "X: %d, Y: %d", x, y);

    // 可以在这里使用str，例如打印或存储
    //AnoDTSendStr(USE_HID|USE_U2,SWJ_ADDR,LOG_COLOR_GREEN,str);
}