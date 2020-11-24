#ifndef	__MCU_CommonMethod_H__
#define	__MCU_CommonMethod_H__

#include "MCU_Config.h"

extern void Delay_ms(unsigned int time);
extern unsigned char Uart_Pretreatment();
extern void UART_BUF_Init();
extern void IsConnect_wifi();
extern void Data_Encapsulation(unsigned char *Buf,unsigned int Buf_len,unsigned char order,sn,action);
extern unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len);
extern void Printf(unsigned char flag,unsigned char *Buf,unsigned int len);
extern unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len);
extern void HexToAscii(unsigned char *Buf_Dest,unsigned char *Buf_Src,unsigned int Buf_len);
#endif