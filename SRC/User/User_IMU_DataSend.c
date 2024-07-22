#include "User_IMU_DataSend.h"
#include <string.h>
//通过UART2发送IMU数据到树莓派中
ROS_IMU_Data_t ROS_IMU_Data = { 
    {0.0f, 0.0f, 0.0f}, // ACC
    {0.0f, 0.0f, 0.0f}, // GYRO
    {0.0f, 0.0f, 0.0f}  // ORI
};
/**
 * @brief IMU数据发送给树莓派通过UART2
 */

void User_IMU_DataSend()
{
    unsigned char data_to_send[36];
    unsigned char header = 0xAA; // Header byte
    unsigned char trailer = 0xAF; // Trailer byte
    unsigned char func = 0x01;
    unsigned char length = 36;
    
    for (int i = 0 ; i < 3 ; i++)
    {
        ROS_IMU_Data.ACC[i] = st_imuData.f_acc_cmpss_nb[i];
        ROS_IMU_Data.GYRO[i] = st_imuData.f_gyr_dps_nb[i];
    }
    ROS_IMU_Data.ORI[0] = imu_data.rol;
    ROS_IMU_Data.ORI[1] = imu_data.pit;
    ROS_IMU_Data.ORI[2] = imu_data.yaw;

    memcpy(data_to_send, ROS_IMU_Data.ACC, 3 * sizeof(float));
    memcpy(data_to_send + 3 * sizeof(float), ROS_IMU_Data.GYRO, 3 * sizeof(float));
    memcpy(data_to_send + 6 * sizeof(float), ROS_IMU_Data.ORI, 3 * sizeof(float));

    // Add header before the data
    Usart2_Send(&header, 1);

    Usart2_Send(&func, 1);

    Usart2_Send(&length, 1);


    // Send the IMU data
    Usart2_Send(data_to_send, 36); // Sending 12 bytes of data

    // Add trailer after the data
    Usart2_Send(&trailer, 1);
}

void User_DataSend(u8 func,u8 length,u8 *data)
{
    unsigned char data_to_send[length];
    unsigned char header = 0xAA; // Header byte
    unsigned char trailer = 0xAF; // Trailer byte
    Usart2_Send(&header, 1);
    Usart2_Send(&func, 1);
    Usart2_Send(&length, 1);
    Usart2_Send(data, length);
    Usart2_Send(&trailer, 1);
}