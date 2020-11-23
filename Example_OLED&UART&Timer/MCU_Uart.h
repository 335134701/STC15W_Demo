#ifndef	__MCU_UART_H__
#define	__MCU_UART_H__

#include "MCU_Config.h"
#include <string.h>

/*************	本地常量声明	**************/
#define	RX1_Length	256		/* 接收缓冲长度 */
#define	RX2_Length	256		/* 接收缓冲长度 */
#define	RX3_Length	256		/* 接收缓冲长度 */
#define	RX4_Length	256		/* 接收缓冲长度 */

/*************	串口波特率	**************/
#define	UART_BaudRate1	9600UL	 /* 波特率 */
#define	UART_BaudRate2	9600UL	 /* 波特率 */
#define	UART_BaudRate3	9600UL	 /* 波特率 */
#define	UART_BaudRate4	9600UL	 /* 波特率 */
//#define	UART_BaudRate2	 57600UL	 /* 波特率 */
//#define	UART_BaudRate3	 38400UL	 /* 波特率 */
//#define	UART_BaudRate4	 19200UL	 /* 波特率 */


/*************	本地变量声明	**************/
extern unsigned char	xdata	RX1_Buffer[RX1_Length];	//接收缓冲
//extern unsigned char	xdata	RX2_Buffer[RX2_Length];	//接收缓冲
//extern unsigned char	xdata	RX3_Buffer[RX3_Length];	//接收缓冲
//extern unsigned char	xdata	RX4_Buffer[RX4_Length];	//接收缓冲

extern unsigned char	RX1_len;	//接收数据长度
//extern unsigned char	RX2_len;	//接收数据长度
//extern unsigned char	RX3_len;	//接收数据长度
//extern unsigned char	RX4_len;	//接收数据长度

//========================================================================
// UART引脚说明:
// UART1:(默认)P3^0,P3^1;		(可选)P3^6,P3^7; P1^6,P1^7;
// UART2:(默认)P1^0,P1^1;		(可选)P4^6,P4^7;
// UART3:(默认)P0^0,P0^1;		(可选)P5^0,P5^1;
// UART4:(默认)P0^2,P0^3;		(可选)P5^2,P5^3;
//========================================================================

extern bit B_TX1_Busy,B_TX2_Busy;	// 发送忙标志
//extern bit B_TX1_Busy,B_TX2_Busy,B_TX3_Busy,B_TX4_Busy;	// 发送忙标志

/*************	本地函数声明	**************/
extern void Uart_Init(void);
extern void SendString1(unsigned char *puts);
extern void SendString2(unsigned char *puts);
//extern void SendString3(unsigned char *puts);
//extern void SendString4(unsigned char *puts);
#endif