#ifndef	__MCU_UART_H
#define	__MCU_UART_H

#include <string.h>

#include "MCU_Config.h"

/*************	���س�������	**************/
#define	RX1_Length	256		/* ���ջ��峤�� */
#define	RX2_Length	256		/* ���ջ��峤�� */
#define	RX3_Length	256		/* ���ջ��峤�� */
#define	RX4_Length	256		/* ���ջ��峤�� */

/*************	���ڲ�����	**************/
#define	UART_BaudRate1	9600UL	 /* ������ */
#define	UART_BaudRate2	9600UL	 /* ������ */
#define	UART_BaudRate3	9600UL	 /* ������ */
#define	UART_BaudRate4	9600UL	 /* ������ */
//#define	UART_BaudRate2	 57600UL	 /* ������ */
//#define	UART_BaudRate3	 38400UL	 /* ������ */
//#define	UART_BaudRate4	 19200UL	 /* ������ */


/*************	���ر�������	**************/
extern unsigned char	xdata	RX1_Buffer[RX1_Length];	//���ջ���
//extern unsigned char	xdata	RX2_Buffer[RX2_Length];	//���ջ���
//extern unsigned char	xdata	RX3_Buffer[RX3_Length];	//���ջ���
//extern unsigned char	xdata	RX4_Buffer[RX4_Length];	//���ջ���

extern unsigned char	RX1_len;	//�������ݳ���
//extern unsigned char	RX2_len;	//�������ݳ���
//extern unsigned char	RX3_len;	//�������ݳ���
//extern unsigned char	RX4_len;	//�������ݳ���

//========================================================================
// UART����˵��:
// UART1:(Ĭ��)P3^0,P3^1;		(��ѡ)P3^6,P3^7; P1^6,P1^7;
// UART2:(Ĭ��)P1^0,P1^1;		(��ѡ)P4^6,P4^7;
// UART3:(Ĭ��)P0^0,P0^1;		(��ѡ)P5^0,P5^1;
// UART4:(Ĭ��)P0^2,P0^3;		(��ѡ)P5^2,P5^3;
//========================================================================

extern bit B_TX1_Busy,B_TX2_Busy;	// ����æ��־
//extern bit B_TX1_Busy,B_TX2_Busy,B_TX3_Busy,B_TX4_Busy;	// ����æ��־

/*************	���غ�������	**************/
extern void Uart_Init(void);
extern void SendString1(unsigned char *puts,unsigned int len);
extern void SendString2(unsigned char *puts,unsigned int len);
//extern void SendString3(unsigned char *puts);
//extern void SendString4(unsigned char *puts);

#endif