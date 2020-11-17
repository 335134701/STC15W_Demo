#include	"MCU_Config.h"

void main()
{
		MCU_Init();
		P55=0;
		while(1)
		{
				P55=~P55;
				Delay_ms(1000);
		}
	
}