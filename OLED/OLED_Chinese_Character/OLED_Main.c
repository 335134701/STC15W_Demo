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
		OLED_P16x16Ch(24,0,1);//(x, y, N)显示16*16点阵  显示的坐标（x,y），N为页范围0～7
		OLED_P16x16Ch(40,0,2);//(x, y, N)显示16*16点阵  显示的坐标（x,y），N为页范围0～7
		OLED_P16x16Ch(56,0,3);//(x, y, N)显示16*16点阵  显示的坐标（x,y），N为页范围0～7
		OLED_P16x16Ch(72,0,4);//(x, y, N)显示16*16点阵  显示的坐标（x,y），N为页范围0～7
		OLED_P16x16Ch(88,0,5);//(x, y, N)显示16*16点阵  显示的坐标（x,y），N为页范围0～7
		/*for(i=0; i<8; i++)//通过点整显示汉字 -- i表示字表数组的位置
		{
//			OLED_P16x16Ch(i*16,0,i);
		 	OLED_P16x16Ch(i*16,2,i+8);
		 	OLED_P16x16Ch(i*16,4,i+16);
		 	OLED_P16x16Ch(i*16,6,i+24);
		}*/
		Delay_ms(4000);
		OLED_CLS();//清屏
	}
}