#include "MCU_Config.h"



void main()
{
	MCU_Init();
	while(1)
	{
//		OLED_Fill(0xff); //��ȫ��
//		delay(2000);
//		OLED_Fill(0x00); //��ȫ��
//		delay(200);
		OLED_P8x16Str(24,3,"123456");//��һ�� -- 8x16����ʾ��Ԫ��ʾASCII��
		Delay_ms(4000);
		OLED_CLS();      //����
	}

}