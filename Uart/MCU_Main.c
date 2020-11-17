#include	"MCU_Config.h"


void main()
{
	MCU_Init();
	
	EA = 1; 					//�����ж�

	SendString1("STC15F4K60S4 USART1 Test Prgramme!\r\n");Delay_ms(10);
	SendString2("STC15F4K60S4 USART2 Test Prgramme!\r\n");Delay_ms(10);
	SendString3("STC15F4K60S4 USART3 Test Prgramme!\r\n");Delay_ms(10);
	SendString4("STC15F4K60S4 USART4 Test Prgramme!\r\n");Delay_ms(10);
	while (1)
	{
		if((RX1_len > 0) && !B_TX1_Busy)	//�յ�������, ���ҷ��Ϳ���
		{
			SendString1(RX1_Buffer);
			Cl_RX_Buffer(RX1_Buffer,&RX1_len);
		}

		if((RX2_len > 0) && !B_TX2_Busy)	//�յ�������, ���ҷ��Ϳ���
		{
			SendString2(RX2_Buffer);
			Cl_RX_Buffer(RX2_Buffer,&RX2_len);
		}

		if((RX3_len > 0) && !B_TX3_Busy)	//�յ�������, ���ҷ��Ϳ���
		{
			SendString3(RX3_Buffer);
			Cl_RX_Buffer(RX3_Buffer,&RX3_len);
		}

		if(( RX4_len > 0) && !B_TX4_Busy)	//�յ�������, ���ҷ��Ϳ���
		{
			SendString4(RX4_Buffer);
			Cl_RX_Buffer(RX4_Buffer,&RX4_len);
		}
	}

}