#include "MCU_Main.h"

void main()
{
		MCU_Init();
		SendString1("STC15F4K60S4 USART1 Test Prgramme!\r\n");Delay_ms(10);
		SendString2("STC15F4K60S4 USART2 Test Prgramme!\r\n");Delay_ms(10);
		SendString3("STC15F4K60S4 USART3 Test Prgramme!\r\n");Delay_ms(10);
		SendString4("STC15F4K60S4 USART4 Test Prgramme!\r\n");Delay_ms(10);
		while(1){
			/*
			OLED_P6x8Str(0,8,"heltec.taobao.com");
			Delay_ms(5000);
			OLED_CLS_Local(0,0,X_WIDTH,Y_WIDTH);
			*/
		}
}