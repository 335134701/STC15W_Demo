#include	"MCU_Config.h"


void main()
{
		MCU_Init();
		
		//	EA = 1; 允许PWM计数器归零中断
		//默认情况下，一个PWM输出周期计数为256，PWM脉冲输出第一次为64，第二次翻转为192
		//若需要更改默认设置，可在PWM_Config()函数中更改初始化变量
		//设置 PWM脉冲输出第一次为16，第二次翻转为32...
		PWMx_SetPwmWide(PWM2_ID, 16, 32);	//PWM_id: PWM通道, PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID.
		PWMx_SetPwmWide(PWM3_ID, 16, 48);
		PWMx_SetPwmWide(PWM4_ID, 16, 64);
		PWMx_SetPwmWide(PWM5_ID, 16, 96);
		PWMx_SetPwmWide(PWM6_ID, 16, 128);
		PWMx_SetPwmWide(PWM7_ID, 16, 144);
		while(1){Delay_ms(2000);}
	
}