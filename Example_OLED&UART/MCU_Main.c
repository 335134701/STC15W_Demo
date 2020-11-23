#include "MCU_Main.h"

void main()
{
    //系统初始化
    MCU_Init();
		while(1){
				if((RX1_len > 0) && !B_TX1_Busy)	//收到过数据, 并且发送空闲
				{
						SendString1(RX1_Buffer);
						RX1_len = 0;
						memset(RX1_Buffer, 0, sizeof(RX1_Buffer));
				}
		}
}