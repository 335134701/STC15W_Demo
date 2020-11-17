#include	"MCU_Config.h"


void LED(void)
{
		if(INT0_cnt > 65536 ) {INT0_cnt=0;}
		if(INT1_cnt > 65536 ) {INT0_cnt=0;}
		if((INT0_cnt % 2==0 )&&(INT0_cnt != 0)) {P55=0;}
		else {P55=1;}
		if((INT1_cnt % 2!=0 )&&(INT1_cnt != 0)) {P55=0;}
		else {P55=1;}
}

void main()
{
		MCU_Init();
		Delay_ms(10);
		EA=1;
		while(1)
		{
					LED();
		}
	
}