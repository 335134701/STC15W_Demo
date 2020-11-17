#include "MCU_Config.h"



void main()
{
	MCU_Init();
	while(1)
	{
//		OLED_Fill(0xff); //ÆÁÈ«ÁÁ
//		delay(2000);
//		OLED_Fill(0x00); //ÆÁÈ«Ãð
//		delay(200);
		OLED_P6x8Str(0,7,"cn.heltec@gmail.com");
		OLED_P6x8Str(0,8,"heltec.taobao.com");
		Delay_ms(4000);
		OLED_CLS();      //ÇåÆÁ
		Delay_ms(4000);
	}


}