#include "MCU_Main.h"

void main()
{
		MCU_Init();
		while(1){
			UART_Receive_Processing();
			UART_Send_Processing();
			IsConnect_wifi();
		}
}