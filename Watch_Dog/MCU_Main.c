#include	"MCU_Config.h"


void KEY(void)
{
		if(P23==0){Delay_ms(1);while(P23==0);P55=~P55;}
		
		//ι��ģʽһ����������Ҫ�ڹ涨ʱ��(D_WDT_SCALE_2,....D_WDT_SCALE_128,D_WDT_SCALE_256)ι��������MCU������
		//MCU����֮��ι��ģʽ�Զ��������������ڿ��Ź����������󣬵�Ƭ������ϵͳISP������������븴λǰ��WDT_CONTR�Ĵ����޹أ������Ź�һ���������޷��ر�
		//����ι��ģʽ
		if(P25==0){Delay_ms(1);while(P25==0);WDT_reset(D_WDT_SCALE_128);}	
}

void main()
{
		MCU_Init();
		Delay_ms(10);
		while(1)
		{
					KEY();
		}
	
}