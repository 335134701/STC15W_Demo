#include	"MCU_Config.h"


void main()
{
		MCU_Init();
		
		//	EA = 1; ����PWM�����������ж�
		//Ĭ������£�һ��PWM������ڼ���Ϊ256��PWM���������һ��Ϊ64���ڶ��η�תΪ192
		//����Ҫ����Ĭ�����ã�����PWM_Config()�����и��ĳ�ʼ������
		//���� PWM���������һ��Ϊ16���ڶ��η�תΪ32...
		PWMx_SetPwmWide(PWM2_ID, 16, 32);	//PWM_id: PWMͨ��, PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID.
		PWMx_SetPwmWide(PWM3_ID, 16, 48);
		PWMx_SetPwmWide(PWM4_ID, 16, 64);
		PWMx_SetPwmWide(PWM5_ID, 16, 96);
		PWMx_SetPwmWide(PWM6_ID, 16, 128);
		PWMx_SetPwmWide(PWM7_ID, 16, 144);
		while(1){Delay_ms(2000);}
	
}