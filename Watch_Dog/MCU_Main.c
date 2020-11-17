#include	"MCU_Config.h"


void KEY(void)
{
		if(P23==0){Delay_ms(1);while(P23==0);P55=~P55;}
		
		//喂狗模式一旦开启，需要在规定时间(D_WDT_SCALE_2,....D_WDT_SCALE_128,D_WDT_SCALE_256)喂狗，否则MCU将重启
		//MCU重启之后喂狗模式自动开启，这是由于看门狗程序启动后，单片机将从系统ISP监控区启动，与复位前的WDT_CONTR寄存器无关，即看门狗一旦启动，无法关闭
		//开启喂狗模式
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