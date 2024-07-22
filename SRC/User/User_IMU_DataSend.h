#ifndef __USER_IMU_DATASEND_H
#define __USER_IMU_DATASEND_H
#include "Ano_Imu_Data.h"
#include "Drv_usart.h"
#include "Ano_Imu.h"
#include "include.h"
//
//imu_data
typedef struct 
{
   vec3_f ACC;      //线性加速度
   vec3_f GYRO;     //角速度
   vec3_f ORI;      //欧拉角 ROS需要四元形式，在树莓派中转化
}ROS_IMU_Data_t;

void User_IMU_DataSend();
void User_DataSend(u8 func,u8 length,u8 *data);
#endif
