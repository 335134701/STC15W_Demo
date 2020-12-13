#ifndef __MCU_TIMER_H__
#define __MCU_TIMER_H__

#include	"MCU_Config.h"

#define	Timer0						0
#define	Timer1						1
#define	Timer2						2
#define	Timer3						3
#define	Timer4						4

#define	TIM_16BitAutoReload				0
#define	TIM_16Bit									1
#define	TIM_8BitAutoReload				2
#define	TIM_16BitAutoReloadNoMask	3

#define	TIM_CLOCK_1T				0
#define	TIM_CLOCK_12T				1
#define	TIM_CLOCK_Ext				2

typedef struct
{
	unsigned char	TIM_Mode;				//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	unsigned char	TIM_Polity;			//优先级设置	PolityHigh,PolityLow
	unsigned char	TIM_Interrupt;	//中断允许		ENABLE,DISABLE
	unsigned char	TIM_ClkSource;	//时钟源		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	unsigned char	TIM_ClkOut;			//可编程时钟输出,	ENABLE,DISABLE
	unsigned int	TIM_Value;			//装载初值
	unsigned char	TIM_Run;				//是否运行		ENABLE,DISABLE
} TIM_InitTypeDef;

extern int Timer0_Count;
//extern int Timer1_Count;
//extern int Timer2_Count;
//extern int Timer3_Count;
//extern int Timer4_Count;


extern void	Timer_Config(void);


#endif