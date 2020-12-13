#include	"MCU_Uart.h"

/*************	本地变量声明	**************/
unsigned char xdata	RX1_Buffer[RX1_Length];	//接收缓冲
//unsigned char xdata	RX2_Buffer[RX2_Length];	//接收缓冲
//unsigned char xdata	RX3_Buffer[RX3_Length];	//接收缓冲
//unsigned char xdata	RX4_Buffer[RX4_Length];	//接收缓冲

unsigned char RX1_len;	//接收数据长度
//unsigned char RX2_len;	//接收数据长度
//unsigned char RX3_len;	//接收数据长度
//unsigned char RX4_len;	//接收数据长度

bit B_TX1_Busy;	// 发送忙标志
//bit B_TX1_Busy,B_TX2_Busy,B_TX3_Busy,B_TX4_Busy;	// 发送忙标志
//========================================================================
// UART引脚说明:
// UART1:(默认)P3^0,P3^1;		(可选)P3^6,P3^7; P1^6,P1^7;
// UART2:(默认)P1^0,P1^1;		(可选)P4^6,P4^7;
// UART3:(默认)P0^0,P0^1;		(可选)P5^0,P5^1;
// UART4:(默认)P0^2,P0^3;		(可选)P5^2,P5^3;
//========================================================================

void	UART1_config(unsigned char brt);
//void	UART2_config(unsigned char brt);
//void	UART3_config(unsigned char brt);
//void	UART4_config(unsigned char brt);


//========================================================================
// 函数: void Uart_Init(void)
// 描述: Uart初始化函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void Uart_Init(void)
{
	UART1_config(2);	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
	//UART2_config(2);	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 无效.
	/*
	UART2_config(2);	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 无效.
	UART3_config(3);	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer3做波特率.
	UART4_config(4);	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer4做波特率.
	*/
}
//========================================================================
// 函数: SetTimer2Baudraye(unsigned int dat)
// 描述: 设置Timer2做波特率发生器。
// 参数: dat: Timer2的重装值.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void	SetTimer2Baudraye(unsigned int dat)	//使用Timer2做波特率
{
	AUXR &= ~(1<<4);	//Timer stop
	AUXR &= ~(1<<3);	//Timer2 set As Timer
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	TH2 = dat / 256;
	TL2 = dat % 256;
	IE2  &= ~(1<<2);	//禁止中断
	AUXR |=  (1<<4);	//Timer run enable
}

//========================================================================
// 函数: void	UART1_config(unsigned char brt)
// 描述: UART1初始化函数。
// 参数: brt: 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void	UART1_config(unsigned char brt)	
{
	// 波特率使用定时器2
	if(brt == 2)
	{
		AUXR |= 0x01;		//S1 BRT Use Timer2;
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate1);
	}

	// 波特率使用定时器1
	else
	{
		TR1 = 0;
		AUXR &= ~0x01;		//S1 BRT Use Timer1;
		AUXR |=  (1<<6);	//Timer1 set as 1T mode
		TMOD &= ~(1<<6);	//Timer1 set As Timer
		TMOD &= ~0x30;		//Timer1_16bitAutoReload;
		TH1 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate1) / 256;
		TL1 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate1) % 256;
		ET1 = 0;	//禁止中断
		INT_CLKO &= ~0x02;	//不输出时钟
		TR1  = 1;
	}
	/*************************************************/
	SCON = (SCON & 0x3f) | (1<<6);	// 8位数据, 1位起始位, 1位停止位, 无校验
//PS  = 1;	//高优先级中断
	ES  = 1;	//允许中断
	REN = 1;	//允许接收
	P_SW1 = P_SW1 & 0x3f;	//切换到 P3.0 P3.1

//P_SW1 = (P_SW1 & 0x3f) | (1<<6);	//切换到P3.6 P3.7
//P_SW1 = (P_SW1 & 0x3f) | (2<<6);	//切换到P1.6 P1.7 (必须使用内部时钟)

	memset(RX1_Buffer,0,RX1_Length);
	B_TX1_Busy  = 0;
	RX1_len   = 0;
}

/*
//========================================================================
// 函数: void	UART2_config(unsigned char brt)
// 描述: UART2初始化函数。
// 参数: brt: 选择波特率, 2: 使用Timer2(定时器工作方式1)做波特率, 其它值: 无效.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void	UART2_config(unsigned char brt)	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 无效.
{
	// 波特率固定使用定时器2
	if(brt == 2)	SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate2);

	S2CON &= ~(1<<7);	// 8位数据, 1位起始位, 1位停止位, 无校验
	IE2   |= 1;			//允许中断
	S2CON |= (1<<4);	//允许接收
	P_SW2 &= ~1;		//切换到 P1.0 P1.1
//P_SW2 |= 1;			//切换到 P4.6 P4.7

	memset(RX2_Buffer,0,RX2_Length);
	B_TX2_Busy  = 0;
	RX2_len   = 0;
}

//========================================================================
// 函数: void	UART3_config(unsigned char brt)
// 描述: UART3初始化函数。
// 参数: brt: 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer3做波特率.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void	UART3_config(unsigned char brt)	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer3做波特率.
{
	//波特率固定使用定时器2 
	if(brt == 2)
	{
		S3CON &= ~(1<<6);	//BRT select Timer2
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate3);
	}
	// 波特率使用定时器3
	else
	{
		S3CON |= (1<<6);	//BRT select Timer3
		T4T3M &= 0xf0;		//停止计数, 清除控制位
		IE2  &= ~(1<<5);	//禁止中断
		T4T3M |=  (1<<1);	//1T
		T4T3M &= ~(1<<2);	//定时
		T4T3M &= ~1;		//不输出时钟
		TH3 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate3) / 256;
		TL3 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate3) % 256;
		T4T3M |=  (1<<3);	//开始运行
	}
	S3CON &= ~(1<<5);	//禁止多机通讯方式
	S3CON &= ~(1<<7);	// 8位数据, 1位起始位, 1位停止位, 无校验
	IE2   |=  (1<<3);	//允许中断
	S3CON |=  (1<<4);	//允许接收
	P_SW2 &= ~2;		//切换到 P0.0 P0.1
//	P_SW2 |= 2;			//切换到 P5.0 P5.1

	memset(RX3_Buffer,0,RX3_Length);
	B_TX3_Busy  = 0;
	RX3_len   = 0;
}

//========================================================================
// 函数: void	UART4_config(unsigned char brt)
// 描述: UART4初始化函数。
// 参数: brt: 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer4做波特率.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void	UART4_config(unsigned char brt)	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer4做波特率.
{
	// 波特率固定使用定时器2
	if(brt == 2)
	{
		S4CON &= ~(1<<6);	//BRT select Timer2
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / UART_BaudRate4);
	}
	// 波特率使用定时器3
	else
	{
		S4CON |= (1<<6);	//BRT select Timer4
		T4T3M &= 0x0f;		//停止计数, 清除控制位
		IE2   &= ~(1<<6);	//禁止中断
		T4T3M |=  (1<<5);	//1T
		T4T3M &= ~(1<<6);	//定时
		T4T3M &= ~(1<<4);	//不输出时钟
		TH4 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate4) / 256;
		TL4 = (65536UL - (MAIN_Fosc / 4) / UART_BaudRate4) % 256;
		T4T3M |=  (1<<7);	//开始运行
	}
	
	S4CON &= ~(1<<5);	//禁止多机通讯方式
	S4CON &= ~(1<<7);	// 8位数据, 1位起始位, 1位停止位, 无校验
	IE2   |=  (1<<4);	//允许中断
	S4CON |=  (1<<4);	//允许接收
	P_SW2 &= ~4;		//切换到 P0.2 P0.3
//	P_SW2 |= 4;			//切换到 P5.2 P5.3

	memset(RX4_Buffer,0,RX4_Length);
	B_TX4_Busy  = 0;
	RX4_len   = 0;
}
*/
//========================================================================
// 函数: void SendString1(unsigned char *puts,unsigned int len)
// 描述: Uart1发送数据函数
// 参数: *puts: 发送数据
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void SendString1(unsigned char *puts,unsigned int len)
{
   unsigned int i=0;
   for (i=0; i<len;	i++)
	 {
			B_TX1_Busy = 1;		//标志发送忙
			SBUF = puts[i];		//发一个字节
			while(B_TX1_Busy);	//等待发送完成
		}
}
/*
//========================================================================
// 函数: void SendString2(unsigned char *puts,unsigned int len)
// 描述: Uart1发送数据函数
// 参数: *puts: 发送数据
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void SendString2(unsigned char *puts,unsigned int len)
{
	 unsigned int i=0;
   for (i=0; i<len;	i++)
	 {
			B_TX2_Busy = 1;		//标志发送忙
			S2BUF = puts[i];		//发一个字节
			while(B_TX2_Busy);	//等待发送完成
		}
}

//========================================================================
// 函数: SendString3(unsigned char *puts)
// 描述: Uart1发送数据函数
// 参数: *puts: 发送数据
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void SendString3(unsigned char *puts)
{
    for (; *puts != 0;	puts++)
		{
			B_TX3_Busy = 1;		//标志发送忙
			S3BUF = *puts;		//发一个字节
			while(B_TX3_Busy);	//等待发送完成
		}
}
//========================================================================
// 函数: SendString4(unsigned char *puts)
// 描述: Uart1发送数据函数
// 参数: *puts: 发送数据
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
//========================================================================
void SendString4(unsigned char *puts)
{
    for (; *puts != 0;	puts++)
		{
			B_TX4_Busy = 1;		//标志发送忙
			S4BUF = *puts;		//发一个字节
			while(B_TX4_Busy);	//等待发送完成
		}
}
*/
//========================================================================
// 函数: void UART1_int (void) interrupt UART1_VECTOR
// 描述: Uart1中断触发函数	
// 参数: none
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
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
// 函数: void UART2_int (void) interrupt UART2_VECTOR
// 描述: Uart2中断触发函数
// 参数: none
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
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
// 函数: void UART3_int (void) interrupt UART3_VECTOR
// 描述: Uart3中断触发函数
// 参数: none
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
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
// 函数: void UART4_int (void) interrupt UART4_VECTOR
// 描述: Uart4中断触发函数
// 参数: none
// 返回: none.
// 版本: VER1.0
// 日期: 2020-03-08
// 备注: 
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