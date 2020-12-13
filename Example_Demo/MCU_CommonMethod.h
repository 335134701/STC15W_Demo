#ifndef	__MCU_CommonMethod_H__
#define	__MCU_CommonMethod_H__

#include "MCU_Config.h"
#include <math.h>

extern void Delay_ms(unsigned int time);
extern void UART_BUF_Init();
extern unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len);
extern unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len);
#endif