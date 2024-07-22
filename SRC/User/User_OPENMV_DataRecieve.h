#ifndef __USER_OPENMV_DATARECIEVE_H
#define __USER_OPENMV_DATARECIEVE_H
#include "include.h"
#include "User_OPENMV_Cal.h"
#include "Drv_usart.h"
#define IDLE    0
#define CHECK   1
#define LEN     2
#define WORK    3
#define END     4
#define RED    0x01
#define BLUE     0x02
#define CIRCLE    0x10
#define RECT      0x11
#define TRIANGLE  0x12
void Deal_With_OPENMV_Data(u8 func,u8 len,u8 *data);
void User_OPENMV_DataRecieve(u8 data) ;
 void Identify_Color_Shape(u8 *data);
void Deal_With_XY_Data(uint8_t *data);
#endif
