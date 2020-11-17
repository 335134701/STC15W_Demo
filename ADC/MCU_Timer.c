#include	"MCU_Config.h"

u16 Timer1_Count;

/*************	功能说明	**************

本程序演示3个定时器的使用。
注意：高速时钟输出定义的引脚是根据原理图上引脚定义得来的。
			P3.4,P3.5 中断和高速时钟输出在同一引脚上，故需要引脚复用。
			设置P3.4,P3.5引脚为推挽输出，
			若设置P3.4,P3.5高速时钟输出为不允许，则无需设置引脚推挽输出，默认即可

定时器0配置为16位自动重装, 20000HZ中断率(50us定时)
         允许高速时钟输出时从P3.4输出10KHZ时钟信号。
         允许中断时从P1.0取反输出10KHZ方波信号。
定时器1配置为16位自动重装, 2000HZ中断率(500us定时)
         允许高速时钟输出时从P3.5输出1000HZ时钟信号。
         允许中断时从P1.1取反输出1000HZ方波信号。
定时器2固定为16位自动重装, 1000HZ中断率(1ms定时)
         允许高速时钟输出时从P3.0输出500HZ时钟信号。
         允许中断时从P1.2取反输出500HZ方波信号。
定时器3固定为16位自动重装, 200HZ中断率(5ms定时)
         允许高速时钟输出时从P0.6输出100HZ时钟信号。
         允许中断时从P1.3取反输出100HZ方波信号。
定时器4固定为16位自动重装, 100HZ中断率(10ms定时)
         允许高速时钟输出时从P0.4输出50HZ时钟信号。
         允许中断时从P1.4取反输出50HZ方波信号。

用户可以修改输出频率，但注意时间不要太高（一般100KHZ以下）。


******************************************/

//========================================================================
// 函数: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2020.03.09
//========================================================================
u8	Timer_Init(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer4)	return 1;	//空操作

	if(TIM == Timer0)
	{
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TR0 = 0;		//停止计数
		ET0 = 0;	//禁止中断
		PT0 = 0;	//低优先级中断
		TMOD &= 0xf0;	//定时模式, 16位自动重装
		AUXR &= ~0x80;	//12T模式, 
		INT_CLKO &= ~0x01;	//不输出时钟
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//允许中断
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		TMOD |= TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//对外计数或分频
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//输出时钟
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}
	return 2;	//错误
}
//========================================================================
// 函数: void	Timer_config(void)
// 描述: 定时器配置函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void	Timer_Config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//指定中断优先级, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);		//初值,
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Init(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
}


/********************* Timer0中断函数************************/
void Timer0_Int (void) interrupt TIMER0_VECTOR
{
   Timer1_Count++;
}
