#ifndef	__MCU_CommonMethod_H__
#define	__MCU_CommonMethod_H__

#include "MCU_Config.h"
#include <math.h>

extern void Delay_ms(unsigned int time);
extern unsigned char Uart_Pretreatment();
extern void UART_BUF_Init();
extern void IsConnect_wifi();
extern void Data_Encapsulation(unsigned int Buf_len, unsigned char order, action);
extern void memcat(unsigned char *dest, const unsigned char *src,unsigned int index,len);
extern unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len);
extern unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len);
#endif