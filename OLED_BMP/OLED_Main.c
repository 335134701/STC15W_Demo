#include "MCU_Config.h"



void main()
{
	MCU_Init();
	while(1)
	{
//		OLED_Fill(0xff); //屏全亮
//		delay(2000);
//		OLED_Fill(0x00); //屏全灭
//		delay(200);
		Draw_BMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		Delay_ms(8000);
		OLED_CLS();      //清屏
	}

}