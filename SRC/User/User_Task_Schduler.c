#include "User_Task_Schduler.h"
/* 任务调度器 */
u8 task_state =         0x00;   //任务标志位
/**
 * @param take_state
 * 0x00
 */
u16 user_task_time = 0;
void User_Task_Schduler(u8 ms)
{
    /*未完待续*/
    switch (task_state)
    {
        case 0x00:
            user_task_time = 0;
            return;
        break;
        case 0x01:
        break;
        case 0x02:
        break;
        case 0x03:
        {

        }
            
            
        break;
    }
}

void Set_Task_State(u8 data)
{
    if(task_state == data)
    {
        return;
    }
    task_state = data;
    user_task_time = 0;
}
