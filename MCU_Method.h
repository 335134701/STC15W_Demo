#ifndef	__MCU_Method_H
#define	__MCU_Method_H

#include "MCU_Uart.h"
#include "MCU_Variable.h"

extern void Delay_ms(unsigned int time);
extern unsigned char Uart_Pretreatment();
extern void RST_Uart_Timer();
extern void IsConnect_wifi();
extern void Data_Encapsulation(unsigned char *Buf,unsigned int Buf_len,unsigned char order,sn,action);
extern unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len);
extern void Printf(unsigned char flag,unsigned char *Buf,unsigned int len);
extern unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len);
extern void HexToAscii(unsigned char *Buf_Dest,unsigned char *Buf_Src,unsigned int Buf_len);
#endif