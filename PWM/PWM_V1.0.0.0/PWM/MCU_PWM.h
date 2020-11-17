#ifndef __MCU_PWM_H__
#define __MCU_PWM_H__


typedef struct
{
	u16	FirstEdge;						// ��һ����ת����, 1~32767
	u16	SecondEdge;						// �ڶ�����ת����, 1~32767
	u8	Start_IO_Level;				// ����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	u8	PWMx_IO_Select;				// PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	u8	PWMx_Interrupt;				// �ж�����,   ENABLE,DISABLE
	u8	FirstEdge_Interrupt;	// ��һ����ת�ж�����, ENABLE,DISABLE
	u8	SecondEdge_Interrupt;	// �ڶ�����ת�ж�����, ENABLE,DISABLE
} PWMx_InitDefine; 


extern void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty);
extern void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx);
extern void	PWMx_SetPwmWide(u8 PWM_id, u16 FirstEdge, u16 SecondEdge);
extern void	PWM_Config(void);


#endif