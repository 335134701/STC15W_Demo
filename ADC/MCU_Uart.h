#ifndef	__MCU_UART_H
#define	__MCU_UART_H

#include <string.h>

/*************	本地常量声明	**************/
#define	RX1_Length	256		/* 接收缓冲长度 */


/*************	串口波特率	**************/
#define	UART_BaudRate1	115200UL	 /* 波特率 */


/*************	本地变量声明	**************/
extern u8	xdata	RX1_Buffer[RX1_Length];	//接收缓冲


extern u8	RX1_len;	//接收数据长度


//========================================================================
// UART引脚说明:
// UART1:(默认)P3^0,P3^1;		(可选)P3^6,P3^7; P1^6,P1^7;
//========================================================================

extern bit B_TX1_Busy;	// 发送忙标志

/*************	本地函数声明	**************/
extern void	UART1_config(u8 brt);	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.

extern void SendString1(u8 *puts);

extern void Cl_RX_Buffer(u8 *puts,u8 *len); //接收BUF清理函数

#endif