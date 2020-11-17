#include	"MCU_Config.h"


void Key_SCAN()
{
	if(P23==0){Delay_ms(10);if(P23==0){P55=~P55;Delay_ms(1000);}}
	if(P24==0){Delay_ms(10);if(P24==0){P55=~P55;Delay_ms(2000);}}
	if(P25==0){Delay_ms(10);if(P25==0){P55=~P55;Delay_ms(4000);}}
	if(P26==0){Delay_ms(10);if(P26==0){P55=~P55;Delay_ms(8000);}}
}

void main()
{
		MCU_Init();
		P55=1;
		while(1)
		{
				Key_SCAN();
		}
	
}