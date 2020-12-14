#ifndef __MCU_PWM_H__
#define __MCU_PWM_H__


#define		PWM_CYCLE		6000											//����PWM�����ڣ�����ֵΪһ����ʱ�����ڼ������Զ��壬���Ը���ʵ���޸�
#define		PWM_HIGH_MIN	32											//����PWM�������Сռ�ձȡ�
#define		PWM_HIGH_MAX	(PWM_CYCLE-PWM_HIGH_MIN)	//����PWM��������ռ�ձȡ��û������޸ġ�

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
	u8	TIM_Mode;				//����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	u8	TIM_Polity;			//���ȼ�����	PolityHigh,PolityLow
	u8	TIM_Interrupt;	//�ж�����		ENABLE,DISABLE
	u8	TIM_ClkSource;	//ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	u8	TIM_ClkOut;			//�ɱ��ʱ�����,	ENABLE,DISABLE
	u16	TIM_Value;			//װ�س�ֵ
	u8	TIM_Run;				//�Ƿ�����		ENABLE,DISABLE
} TIM_InitTypeDef;

extern void	Timer_Config(void);
extern void PWM_Set(u16 duty);
#endif