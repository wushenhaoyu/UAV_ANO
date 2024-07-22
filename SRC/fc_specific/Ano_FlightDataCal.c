#include "Ano_FlightDataCal.h"
#include "Ano_Imu.h"
#include "Drv_icm20602.h"
#include "Ano_MagProcess.h"
#include "Drv_spl06.h"
#include "Drv_ak8975.h"
#include "drv_ak09915.h"
#include "Ano_MotionCal.h"
#include "Drv_laser.h"
#include "Ano_FlightCtrl.h"
#include "Drv_led.h"
#include "Ano_OF.h"
#include "Ano_Sensor_Basic.h"
#include "Ano_Imu_Task.h"
#include "Ano_Imu_Calibration.h"
#include "Ano_Imu_Data.h"

/*============================================================================
���£�
201908022235-Jyoun������wcz_acc_use���˲�ϵ����
202011232135-Jyoun����088������

===========================================================================*/

u16 test_time_cnt;
void Fc_Sensor_Get()//1ms
{
	static u8 cnt;
	if(flag.start_ok)
	{
		//
		ImuServices_1ms_c();
		//
		cnt ++;
		cnt %= 20;
		if(cnt==0)
		{
			/*��ȡ�������̴���������*/
			if(MagType == MAG_AK8975)
				DrvAk8975Read();
			else if(MagType == MAG_AK09915)
				DrvAk09915Read();
			/*��ȡ��ѹ������*/
			baro_height = (s32)Drv_Spl0601_Read();

		}
	}	
	test_time_cnt++;

}

extern s32 sensor_val_ref[];

static u8 reset_imu_f;
void IMU_Update_Task(u8 dT_ms)
{


	
////////////////////////////////////////////////////////////////////////		
			/*���׼�����У���λ������λ��Ǻʹ����Ƹ�λ���*/
				if(flag.unlock_sta )
				{
					imu_state.G_reset = imu_state.M_reset = 0;
					reset_imu_f = 0;
				}
				else 
				{
					if(st_imuData.data_sta==0)
					{
						imu_state.G_reset = 1;//�Զ���λ
						//sensor.gyr_CALIBRATE = 2;
					}	
					
					if(reset_imu_f==0 )//&& flag.motionless == 1)
					{
						imu_state.G_reset = 1;//�Զ���λ	
						st_imu_cali.gyr_cali_on = 2;//У׼�����ǣ�������
						reset_imu_f = 1;     //�Ѿ���λ��λ���
					}
								
				}
									
				if(0) 
				{
					imu_state.gkp = 0.0f;
					imu_state.gki = 0.0f;
					
				}
				else
				{
					if(0)
					{
						imu_state.gkp = 0.2f;
					}
					else
					{
						/*�������������ں�����kpϵ��*/
						imu_state.gkp = 0.2f;//0.4f;
					}
					
					/*�������������ں�����kiϵ��*/
					imu_state.gki = 0.01f;
					
					/*�������̻����ں�����kiϵ��*/
					imu_state.mkp = 0.1f;
				}
				
				imu_state.M_fix_en = 0;		//����������ʹ��
	
				if(st_imuData.data_sta==1 && st_imu_cali.gyr_cali_on == 0)
				{
					/*��̬���㣬���£��ں�*/
					IMU_update(dT_ms *1e-3f, &imu_state,sensor.Gyro_rad, sensor.Acc_cmss, mag.val,&imu_data);//x3_dT_1[2] * 0.000001f
				}
//////////////////////////////////////////////////////////////////////	
}

static s16 mag_val[3];
void Mag_Update_Task(u8 dT_ms)
{
	if(MagType==MAG_AK8975)//8975
	{
		Mag_Get(mag_val);
	}
	else if(MagType==MAG_AK09915)//09915
	{
		mag_val[0] = -ak09915Buf.st_data.y;
		mag_val[1] =  ak09915Buf.st_data.x;
		mag_val[2] =  ak09915Buf.st_data.z;
	}
	
	Mag_Data_Deal_Task(dT_ms,mag_val,imu_data.z_vec[Z],sensor.Gyro_deg[X],sensor.Gyro_deg[Z]);
	
}


s32 baro_height,baro_h_offset,ref_height_get_1,ref_height_get_2,ref_height_used;
s32 baro2tof_offset,tof2baro_offset;

float baro_fix1,baro_fix2,baro_fix;

static u8 wcz_f_pause;
float wcz_acc_use;			

void WCZ_Acc_Get_Task()//��С����
{
	wcz_acc_use += 0.02f *(imu_data.w_acc[Z] - wcz_acc_use);
}

//void Baro_Get_Task()
//{
////			ref_height_get += LIMIT((s32)user_spl0601_get() - ref_height_get,-20,20 );
////	baro_height =(s32)user_spl0601_get();
//}

u16 ref_tof_height;
static u8 baro_offset_ok,tof_offset_ok;
void WCZ_Fus_Task(u8 dT_ms)
{

	
	if(flag.taking_off)
	{
		baro_offset_ok = 2;
	}
	else
	{
		if(baro_offset_ok == 2)
		{
			baro_offset_ok = 0;
		}
		//reset
		tof2baro_offset = 0;
	}
	
	if(baro_offset_ok >= 1)//(flag.taking_off)
	{
		ref_height_get_1 = baro_height - baro_h_offset + baro_fix  + tof2baro_offset;//��ѹ����Ը߶ȣ��л������TOF
		//baro_offset_ok = 0;
	}
	else
	{
		if(baro_offset_ok == 0 )
		{
			baro_h_offset = baro_height;
			if(flag.sensor_imu_ok)
			{
				baro_offset_ok = 1;
			}
		}
	}
	
	if((flag.flying == 0) && flag.auto_take_off_land == AUTO_TAKE_OFF	)
	{
		wcz_f_pause = 1;
		
		baro_fix = 0;
	}
	else
	{
		wcz_f_pause = 0;
		
		if(flag.taking_off == 0)
		{
			baro_fix1 = 0;
			baro_fix2 = 0;
				
		}
		baro_fix2 = -BARO_FIX;

		
		baro_fix = baro_fix1 + baro_fix2 - BARO_FIX;//+ baro_fix3;
	}
	//
	static u8 jump_f;
	static s16 of_tof_old_cm;
	jump_f = (ABS(jsdata.valid_of_alt_cm - of_tof_old_cm)>25) ? 1 : 0;
	of_tof_old_cm = jsdata.valid_of_alt_cm;
	//
	if((sens_hd_check.of_df_ok || sens_hd_check.of_ok) && baro_offset_ok) //TOF����OFӲ������������ѹ�Ƽ�¼���ֵ�Ժ�
	{
		if( ( switchs.tof_on || switchs.of_tof_on )&&( jump_f == 0 ) ) //TOF������Ч
		{
			if(switchs.of_tof_on) //������TOF����������
			{
				ref_tof_height = jsdata.valid_of_alt_cm ;
			}
			else//switchs.tof_on
			{
//				ref_tof_height = Laser_height_mm/10;
			}
			
			
			//
			if(tof_offset_ok == 0)
			{
				baro2tof_offset = ref_height_get_1 - ref_tof_height ; //��¼TOF�л���		
				tof_offset_ok = 1;
			}
			//
			ref_height_get_2 = ref_tof_height + baro2tof_offset;//TOF�ο��߶ȣ��л��������ѹ��				
			ref_height_used = ref_height_get_2;
			
			tof2baro_offset += 0.5f *((ref_height_get_2 - ref_height_get_1) - tof2baro_offset);//��¼��ѹ���л��㣬��ѹ�Ʋ�������΢�˲�һ��
			//tof2baro_offset = ref_height_get_2 - ref_height_get_1;				
			

		}
		else
		{
			
			tof_offset_ok = 0;
			
			ref_height_used = ref_height_get_1 ;
		}
	}
	else
	{
		ref_height_used = ref_height_get_1;
	}
	
	//����z����߶���Ϣ�ں�
	WCZ_Data_Calc(dT_ms,wcz_f_pause,(s32)wcz_acc_use,(s32)(ref_height_used));

}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////



