#include "MCU_Main.h"

void main()
{
		MCU_Init();
		while(1){
			OLED_P6x8Str(0,8,"heltec.taobao.com");
			Delay_ms(1000);
			OLED_CLS_Local(0,0,X_WIDTH,Y_WIDTH);
		}
}