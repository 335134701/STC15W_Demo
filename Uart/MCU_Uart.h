#ifndef	__MCU_UART_H
#define	__MCU_UART_H

#include <string.h>

/*************	���س�������	**************/
#define	RX1_Length	256		/* ���ջ��峤�� */
#define	RX2_Length	256		/* ���ջ��峤�� */
#define	RX3_Length	256		/* ���ջ��峤�� */
#define	RX4_Length	256		/* ���ջ��峤�� */

/*************	���ڲ�����	**************/
#define	UART_BaudRate1	115200UL	 /* ������ */
#define	UART_BaudRate2	115200UL	 /* ������ */
#define	UART_BaudRate3	115200UL	 /* ������ */
#define	UART_BaudRate4	115200UL	 /* ������ */
//#define	UART_BaudRate2	 57600UL	 /* ������ */
//#define	UART_BaudRate3	 38400UL	 /* ������ */
//#define	UART_BaudRate4	 19200UL	 /* ������ */


/*************	���ر�������	**************/
extern u8	xdata	RX1_Buffer[RX1_Length];	//���ջ���
extern u8	xdata	RX2_Buffer[RX2_Length];	//���ջ���
extern u8	xdata	RX3_Buffer[RX3_Length];	//���ջ���
extern u8	xdata	RX4_Buffer[RX4_Length];	//���ջ���

extern u8	RX1_len;	//�������ݳ���
extern u8	RX2_len;	//�������ݳ���
extern u8	RX3_len;	//�������ݳ���
extern u8	RX4_len;	//�������ݳ���

//========================================================================
// UART����˵��:
// UART1:(Ĭ��)P3^0,P3^1;		(��ѡ)P3^6,P3^7; P1^6,P1^7;
// UART2:(Ĭ��)P1^0,P1^1;		(��ѡ)P4^6,P4^7;
// UART3:(Ĭ��)P0^0,P0^1;		(��ѡ)P5^0,P5^1;
// UART4:(Ĭ��)P0^2,P0^3;		(��ѡ)P5^2,P5^3;
//========================================================================

extern bit B_TX1_Busy,B_TX2_Busy,B_TX3_Busy,B_TX4_Busy;	// ����æ��־

/*************	���غ�������	**************/
extern void Uart_Init(void);
extern void	UART1_config(u8 brt);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
extern void	UART2_config(u8 brt);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
extern void	UART3_config(u8 brt);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
extern void	UART4_config(u8 brt);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
extern void SendString1(u8 *puts);
extern void SendString2(u8 *puts);
extern void SendString3(u8 *puts);
extern void SendString4(u8 *puts);
extern void Cl_RX_Buffer(u8 *puts,u8 *len); //����BUF������

#endif