#include	"MCU_Config.h"


void main()
{
		MCU_Init();
		EA = 1;		
		PWM_Set((MAIN_Fosc / 200));
		while(1){Delay_ms(2000);}
	
}