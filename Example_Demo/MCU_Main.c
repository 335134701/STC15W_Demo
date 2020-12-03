#include "MCU_Main.h"

void main()
{
    //系统初始化
    MCU_Init();
    while(1) {
        //串口接收函数
        UART_Receive_Service_Layer();
        //串口发送函数
        UART_Send_Servvice_Layer();
        //串口接收判断函数
        IsConnect_wifi();
    }
}