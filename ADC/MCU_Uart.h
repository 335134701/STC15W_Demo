#ifndef	__MCU_UART_H
#define	__MCU_UART_H

#include <string.h>

/*************	���س�������	**************/
#define	RX1_Length	256		/* ���ջ��峤�� */


/*************	���ڲ�����	**************/
#define	UART_BaudRate1	115200UL	 /* ������ */


/*************	���ر�������	**************/
extern u8	xdata	RX1_Buffer[RX1_Length];	//���ջ���


extern u8	RX1_len;	//�������ݳ���


//========================================================================
// UART����˵��:
// UART1:(Ĭ��)P3^0,P3^1;		(��ѡ)P3^6,P3^7; P1^6,P1^7;
//========================================================================

extern bit B_TX1_Busy;	// ����æ��־

/*************	���غ�������	**************/
extern void	UART1_config(u8 brt);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.

extern void SendString1(u8 *puts);

extern void Cl_RX_Buffer(u8 *puts,u8 *len); //����BUF������

#endif