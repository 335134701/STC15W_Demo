#include	"MCU_Config.h"

u16 key_num;

void KEY(void)
{
		if(key_num>10)
		{	
					key_num=0;
					//10秒后醒来
					SetWakeUpTime(10000);
					//开启掉电
					MCU_POWER_DOWN();
		}else
		{
				if(P23==0){
						Delay_ms(10);
						while(P23==0);
						key_num++;
						P55=~P55;
				}
		
		}
}

void main()
{
		MCU_Init();
		key_num=0;
		Delay_ms(10);
		EA=1;
		while(1)
		{
					KEY();
		}
	
}