#include "MCU_Main.h"

void main()
{
    //ϵͳ��ʼ��
    MCU_Init();
		while(1){
				if((RX1_len > 0) && !B_TX1_Busy)	//�յ�������, ���ҷ��Ϳ���
				{
						SendString1(RX1_Buffer);
						RX1_len = 0;
						memset(RX1_Buffer, 0, sizeof(RX1_Buffer));
				}
		}
}