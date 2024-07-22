#include "Ano_ProgramCtrl_User.h"
#include "Ano_Math.h"


#define MAX_PC_XYVEL_CMPS  200
#define MAX_PC_ZVEL_CMPS   150
#define MAX_PC_PAL_DPS     100

_pc_user_st pc_user;

//=====1������ˮƽ����ϵ�̿��ٶȹ��ܽӿں���=====
/**********************************************************************************************************
* 功能说明: 控制程序，用于水平坐标系中的速度趋势实时控制，
 * 参数说明: X速度，每秒变化的距离，向前为正；Y速度，每秒变化的距离，向右为正。
 * 返回值: 无
**********************************************************************************************************/
void Program_Ctrl_User_Set_HXYcmps(float hx_vel_cmps,float hy_vel_cmps)
{
	//
	pc_user.vel_cmps_set_h[0] = hx_vel_cmps;
	pc_user.vel_cmps_set_h[1] = hy_vel_cmps;
	//����XY�ٶ�ģ��
	length_limit(&pc_user.vel_cmps_set_h[0],&pc_user.vel_cmps_set_h[1],MAX_PC_XYVEL_CMPS,pc_user.vel_cmps_set_h);
}


//=====2����ͷģʽ�ο�����ϵ�̿ع��ٶ��ܽӿں��������ޣ��Ժ󿪷������߲ο���λ���̿ع��ܣ�=====
//
//
//

//=====3��ͨ�ó̿��ٶȹ��ܽӿں���=====
/**********************************************************************************************************
功能名称: Program_Ctrl_User_Set_WHZcmps
 * 功能说明: 控制程序，用户设置垂直速度趋势的实时控制，
 * 参数说明: 速度，每秒变化的高度，单位为厘米/秒。
 * 返回值: 无
**********************************************************************************************************/
void Program_Ctrl_User_Set_Zcmps(float z_vel_cmps)
{
	//
	pc_user.vel_cmps_set_z = z_vel_cmps;
	//�޷�
	pc_user.vel_cmps_set_z = LIMIT(pc_user.vel_cmps_set_z,-MAX_PC_ZVEL_CMPS,MAX_PC_ZVEL_CMPS);
}
/**********************************************************************************************************
 功能名称: Program_Ctrl_User_Set_YAWdps
 * 功能说明: 控制程序，用户设置偏航角速度的实时控制，
 * 参数说明: 速度，每秒旋转的角度，单位为度/秒。
 * 返回值: 无
**********************************************************************************************************/
void Program_Ctrl_User_Set_YAWdps(float yaw_pal_dps)
{
	//
	pc_user.pal_dps_set = yaw_pal_dps;
	//�޷�
	pc_user.pal_dps_set = LIMIT(pc_user.pal_dps_set,-MAX_PC_PAL_DPS,MAX_PC_PAL_DPS);
}





