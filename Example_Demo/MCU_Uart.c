#include	"MCU_Uart.h"

/*************	���ر�������	**************/
unsigned char xdata	RX1_Buffer[RX1_Length];	//���ջ���
//unsigned char xdata	RX2_Buffer[RX2_Length];	//���ջ���
//unsigned char xdata	RX3_Buffer[RX3_Length];	//���ջ���
//unsigned char xdata	RX4_Buffer[RX4_Length];	//���ջ���

unsigned char RX1_len;	//�������ݳ���
//unsigned char RX2_len;	//�������ݳ���
//unsigned char RX3_len;	//�������ݳ���
//unsigned char RX4_len;	//�������ݳ���

bit B_TX1_Busy;	// ����æ��־
//bit B_TX1_Busy,B_TX2_Busy,B_TX3_Busy,B_TX4_Busy;	// ����æ��־
//========================================================================
// UART����˵��:
// UART1:(Ĭ��)P3^0,P3^1;		(��ѡ)P3^6,P3^7; P1^6,P1^7;
// UART2:(Ĭ��)P1^0,P1^1;		(��ѡ)P4^6,P4^7;
// UART3:(Ĭ��)P0^0,P0^1;		(��ѡ)P5^0,P5^1;
// UART4:(Ĭ��)P0^2,P0^3;		(��ѡ)P5^2,P5^3;
//========================================================================

void	UART1_config(unsigned char brt);
//void	UART2_config(unsigned char brt);
//void	UART3_config(unsigned char brt);
//void	UART4_config(unsigned char brt);


//========================================================================
// ����: void Uart_Init(void)
// ����: Uart��ʼ������
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void Uart_Init(void)
{
	UART1_config(2);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
	//UART2_config(2);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
	/*
	UART2_config(2);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
	UART3_config(3);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
	UART4_config(4);	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
	*/
}
//========================================================================
// ����: SetTimer2Baudraye(unsigned int dat)
// ����: ����Timer2�������ʷ�������
// ����: dat: Timer2����װֵ.
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void	SetTimer2Baudraye(unsigned int dat)	//ʹ��Timer2��������
{
	AUXR &= ~(1<<4);	//Timer stop
	AUXR &= ~(1<<3);	//Timer2 set As Timer
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	TH2 = dat / 256;
	TL2 = dat % 256;
	IE2  &= ~(1<<2);	//��ֹ�ж�
	AUXR |=  (1<<4);	//Timer run enable
}

//========================================================================
// ����: void	UART1_config(unsigned char brt)
// ����: UART1��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void	UART1_config(unsigned char brt)	
{
	// ������ʹ�ö�ʱ��2
	if(brt == 2)
	{
		AUXR |= 0x01;		//S1 BRT Use Timer2;
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate1);
	}

	// ������ʹ�ö�ʱ��1
	else
	{
		TR1 = 0;
		AUXR &= ~0x01;		//S1 BRT Use Timer1;
		AUXR |=  (1<<6);	//Timer1 set as 1T mode
		TMOD &= ~(1<<6);	//Timer1 set As Timer
		TMOD &= ~0x30;		//Timer1_16bitAutoReload;
		TH1 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate1) / 256;
		TL1 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate1) % 256;
		ET1 = 0;	//��ֹ�ж�
		INT_CLKO &= ~0x02;	//�����ʱ��
		TR1  = 1;
	}
	/*************************************************/
	SCON = (SCON & 0x3f) | (1<<6);	// 8λ����, 1λ��ʼλ, 1λֹͣλ, ��У��
//PS  = 1;	//�����ȼ��ж�
	ES  = 1;	//�����ж�
	REN = 1;	//�������
	P_SW1 = P_SW1 & 0x3f;	//�л��� P3.0 P3.1

//P_SW1 = (P_SW1 & 0x3f) | (1<<6);	//�л���P3.6 P3.7
//P_SW1 = (P_SW1 & 0x3f) | (2<<6);	//�л���P1.6 P1.7 (����ʹ���ڲ�ʱ��)

	memset(RX1_Buffer,0,RX1_Length);
	B_TX1_Busy  = 0;
	RX1_len   = 0;
}

/*
//========================================================================
// ����: void	UART2_config(unsigned char brt)
// ����: UART2��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2(��ʱ��������ʽ1)��������, ����ֵ: ��Ч.
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void	UART2_config(unsigned char brt)	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
{
	// �����ʹ̶�ʹ�ö�ʱ��2
	if(brt == 2)	SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate2);

	S2CON &= ~(1<<7);	// 8λ����, 1λ��ʼλ, 1λֹͣλ, ��У��
	IE2   |= 1;			//�����ж�
	S2CON |= (1<<4);	//�������
	P_SW2 &= ~1;		//�л��� P1.0 P1.1
//P_SW2 |= 1;			//�л��� P4.6 P4.7

	memset(RX2_Buffer,0,RX2_Length);
	B_TX2_Busy  = 0;
	RX2_len   = 0;
}

//========================================================================
// ����: void	UART3_config(unsigned char brt)
// ����: UART3��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void	UART3_config(unsigned char brt)	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
{
	//�����ʹ̶�ʹ�ö�ʱ��2 
	if(brt == 2)
	{
		S3CON &= ~(1<<6);	//BRT select Timer2
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate3);
	}
	// ������ʹ�ö�ʱ��3
	else
	{
		S3CON |= (1<<6);	//BRT select Timer3
		T4T3M &= 0xf0;		//ֹͣ����, �������λ
		IE2  &= ~(1<<5);	//��ֹ�ж�
		T4T3M |=  (1<<1);	//1T
		T4T3M &= ~(1<<2);	//��ʱ
		T4T3M &= ~1;		//�����ʱ��
		TH3 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate3) / 256;
		TL3 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate3) % 256;
		T4T3M |=  (1<<3);	//��ʼ����
	}
	S3CON &= ~(1<<5);	//��ֹ���ͨѶ��ʽ
	S3CON &= ~(1<<7);	// 8λ����, 1λ��ʼλ, 1λֹͣλ, ��У��
	IE2   |=  (1<<3);	//�����ж�
	S3CON |=  (1<<4);	//�������
	P_SW2 &= ~2;		//�л��� P0.0 P0.1
//	P_SW2 |= 2;			//�л��� P5.0 P5.1

	memset(RX3_Buffer,0,RX3_Length);
	B_TX3_Busy  = 0;
	RX3_len   = 0;
}

//========================================================================
// ����: void	UART4_config(unsigned char brt)
// ����: UART4��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void	UART4_config(unsigned char brt)	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
{
	// �����ʹ̶�ʹ�ö�ʱ��2
	if(brt == 2)
	{
		S4CON &= ~(1<<6);	//BRT select Timer2
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate4);
	}
	// ������ʹ�ö�ʱ��3
	else
	{
		S4CON |= (1<<6);	//BRT select Timer4
		T4T3M &= 0x0f;		//ֹͣ����, �������λ
		IE2   &= ~(1<<6);	//��ֹ�ж�
		T4T3M |=  (1<<5);	//1T
		T4T3M &= ~(1<<6);	//��ʱ
		T4T3M &= ~(1<<4);	//�����ʱ��
		TH4 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate4) / 256;
		TL4 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate4) % 256;
		T4T3M |=  (1<<7);	//��ʼ����
	}
	
	S4CON &= ~(1<<5);	//��ֹ���ͨѶ��ʽ
	S4CON &= ~(1<<7);	// 8λ����, 1λ��ʼλ, 1λֹͣλ, ��У��
	IE2   |=  (1<<4);	//�����ж�
	S4CON |=  (1<<4);	//�������
	P_SW2 &= ~4;		//�л��� P0.2 P0.3
//	P_SW2 |= 4;			//�л��� P5.2 P5.3

	memset(RX4_Buffer,0,RX4_Length);
	B_TX4_Busy  = 0;
	RX4_len   = 0;
}
*/
//========================================================================
// ����: void SendString1(unsigned char *puts,unsigned int len)
// ����: Uart1�������ݺ���
// ����: *puts: ��������
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void SendString1(unsigned char *puts,unsigned int len)
{
   unsigned int i=0;
   for (i=0; i<len;	i++)
	 {
			B_TX1_Busy = 1;		//��־����æ
			SBUF = puts[i];		//��һ���ֽ�
			while(B_TX1_Busy);	//�ȴ��������
		}
}
/*
//========================================================================
// ����: void SendString2(unsigned char *puts,unsigned int len)
// ����: Uart1�������ݺ���
// ����: *puts: ��������
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void SendString2(unsigned char *puts,unsigned int len)
{
	 unsigned int i=0;
   for (i=0; i<len;	i++)
	 {
			B_TX2_Busy = 1;		//��־����æ
			S2BUF = puts[i];		//��һ���ֽ�
			while(B_TX2_Busy);	//�ȴ��������
		}
}

//========================================================================
// ����: SendString3(unsigned char *puts)
// ����: Uart1�������ݺ���
// ����: *puts: ��������
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void SendString3(unsigned char *puts)
{
    for (; *puts != 0;	puts++)
		{
			B_TX3_Busy = 1;		//��־����æ
			S3BUF = *puts;		//��һ���ֽ�
			while(B_TX3_Busy);	//�ȴ��������
		}
}
//========================================================================
// ����: SendString4(unsigned char *puts)
// ����: Uart1�������ݺ���
// ����: *puts: ��������
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void SendString4(unsigned char *puts)
{
    for (; *puts != 0;	puts++)
		{
			B_TX4_Busy = 1;		//��־����æ
			S4BUF = *puts;		//��һ���ֽ�
			while(B_TX4_Busy);	//�ȴ��������
		}
}
*/
//========================================================================
// ����: void UART1_int (void) interrupt UART1_VECTOR
// ����: Uart1�жϴ�������	
// ����: none
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void UART1_int (void) interrupt UART1_VECTOR
{
	if(RI)
	{
		RI = 0;
		RX1_Buffer[RX1_len] = SBUF;
		if(++RX1_len >= RX1_Length)	RX1_len = 0;
	}

	if(TI)
	{
		TI = 0;
		B_TX1_Busy = 0;
	}
}
/*
//========================================================================
// ����: void UART2_int (void) interrupt UART2_VECTOR
// ����: Uart2�жϴ�������
// ����: none
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void UART2_int (void) interrupt UART2_VECTOR
{
	if(RI2)
	{
		CLR_RI2();
		//RX2_Buffer[RX2_len] = S2BUF;
		//if(++RX2_len >= RX2_Length)	RX2_len = 0;
	}

	if(TI2)
	{
		CLR_TI2();
		B_TX2_Busy = 0;
	}

}

//========================================================================
// ����: void UART3_int (void) interrupt UART3_VECTOR
// ����: Uart3�жϴ�������
// ����: none
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void UART3_int (void) interrupt UART3_VECTOR
{
	if(RI3)
	{
		CLR_RI3();
		RX3_Buffer[RX3_len] = S3BUF;
		if(++RX3_len >= RX3_Length)	RX3_len = 0;
	}
	if(TI3)
	{
		CLR_TI3();
		B_TX3_Busy = 0;
	}

}

//========================================================================
// ����: void UART4_int (void) interrupt UART4_VECTOR
// ����: Uart4�жϴ�������
// ����: none
// ����: none.
// �汾: VER1.0
// ����: 2020-03-08
// ��ע: 
//========================================================================
void UART4_int (void) interrupt UART4_VECTOR
{
	if(RI4)
	{
		CLR_RI4();
		RX4_Buffer[RX4_len] = S4BUF;
		if(++RX4_len >= RX4_Length)	RX4_len = 0;
	}

	if(TI4)
	{
		CLR_TI4();
		B_TX4_Busy = 0;
	}
}
*/