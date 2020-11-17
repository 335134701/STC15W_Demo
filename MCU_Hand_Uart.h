#ifndef __MCU_HAND_UART_H__
#define __MCU_HAND_UART_H__

#include <stdlib.h>

#include "MCU_Config.h"
#include "MCU_Control.h"
#include "MCU_Variable.h"
#include "MCU_OLED_Show.h"


sbit Set_soft_flag=P2^3;
sbit Set_AP_flag=P2^4;
sbit Reset_message_flag=P2^5;
sbit Bindable_wifi_flag=P2^0;
sbit Restart_wifi_flag=P2^6;

extern void UART_Receive_Processing();
extern void UART_Send_Processing();
#endif