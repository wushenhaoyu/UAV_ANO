	#include "Ano_ProgramCtrl_User.h"
#include "Ano_Math.h"


#define MAX_PC_XYVEL_CMPS  200
#define MAX_PC_ZVEL_CMPS   150
#define MAX_PC_PAL_DPS     100

_pc_user_st pc_user;

//=====1������ˮƽ����ϵ�̿��ٶȹ��ܽӿں���=====
/**********************************************************************************************************
*�� �� ��: Program_Ctrl_User_Set_HXYcmps
*����˵��: �̿ع��ܣ�����ˮƽ����ϵ���ٶ��趨��ʵʱ���ƣ�
*��    ��: X�ٶȣ�����ÿ�룬��Ϊǰ������Ϊ���ˣ�Y�ٶȣ�����ÿ�룬��Ϊ���ƣ���Ϊ���ƣ�
*�� �� ֵ: ��
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
*�� �� ��: Program_Ctrl_User_Set_WHZcmps
*����˵��: �̿ع��ܣ������½��ٶ��趨��ʵʱ���ƣ�
*��    ��: �ٶȣ�����ÿ�룬��Ϊ��������Ϊ�½���
*�� �� ֵ: ��
**********************************************************************************************************/
void Program_Ctrl_User_Set_Zcmps(float z_vel_cmps)
{
	//
	pc_user.vel_cmps_set_z = z_vel_cmps;
	//�޷�
	pc_user.vel_cmps_set_z = LIMIT(pc_user.vel_cmps_set_z,-MAX_PC_ZVEL_CMPS,MAX_PC_ZVEL_CMPS);
}
/**********************************************************************************************************
*�� �� ��: Program_Ctrl_User_Set_YAWdps
*����˵��: �̿ع��ܣ������ٶ��趨��ʵʱ���ƣ�
*��    ��: �ٶȣ���ÿ�룬��Ϊ��ת����Ϊ��ת��
*�� �� ֵ: ��
**********************************************************************************************************/
void Program_Ctrl_User_Set_YAWdps(float yaw_pal_dps)
{
	//
	pc_user.pal_dps_set = yaw_pal_dps;
	//�޷�
	pc_user.pal_dps_set = LIMIT(pc_user.pal_dps_set,-MAX_PC_PAL_DPS,MAX_PC_PAL_DPS);
}





