#include "MCU_Main.h"

void main()
{
    //ϵͳ��ʼ��
    MCU_Init();
    while(1) {
        //���ڽ��պ���
        UART_Receive_Processing();
        //���ڷ��ͺ���
        UART_Send_Processing();
        //���ڽ����жϺ���
        //IsConnect_wifi();
    }
}