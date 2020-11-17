#include	"MCU_Config.h"

u16	PWM_high,PWM_low;	//�м�������û������޸ġ�

//========================================================================
// ����: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2020.03.09
//========================================================================
u8	Timer_Init(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer4)	return 1;	//�ղ���

	if(TIM == Timer0)
	{
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR0 = 0;		//ֹͣ����
		ET0 = 0;	//��ֹ�ж�
		PT0 = 0;	//�����ȼ��ж�
		TMOD &= 0xf0;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x80;	//12Tģʽ, 
		INT_CLKO &= ~0x01;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		TMOD |= TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//���ʱ��
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR1 = 0;	//ֹͣ����
		ET1 = 0;	//��ֹ�ж�
		PT1 = 0;	//�����ȼ��ж�
		TMOD &=  0x0f;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x40;	//12Tģʽ, 
		INT_CLKO &= ~0x02;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		TMOD |= (TIMx->TIM_Mode << 4);	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//���ʱ��
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		AUXR &= ~0x1c;		//ֹͣ����, ��ʱģʽ, 12Tģʽ
		IE2  &= ~(1<<2);	//��ֹ�ж�
		INT_CLKO &= ~0x04;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//���ʱ��

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer3)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0xf0;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2  &= ~(1<<5);	//��ֹ�ж�
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<5);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<1);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<1);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  1;	//���ʱ��

		TH3 = (u8)(TIMx->TIM_Value >> 8);
		TL3 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<3);	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer4)		//Timer4,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0x0f;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2  &= ~(1<<6);	//��ֹ�ж�
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<6);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<5);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<5);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  (1<<4);	//���ʱ��

		TH4 = (u8)(TIMx->TIM_Value >> 8);
		TL4 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<7);	//��ʼ����
		return	0;		//�ɹ�
	}
	return 2;	//����
}

//========================================================================
// ����: void	Timer_config(void)
// ����: ��ʱ�����ú���
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void	Timer_Config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 200);		//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
/*
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 2000);		//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer1,&TIM_InitStructure);				//��ʼ��Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (1000*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer2,&TIM_InitStructure);				//��ʼ��Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer3�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (200*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer3,&TIM_InitStructure);				//��ʼ��Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = DISABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer4�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (100*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer4,&TIM_InitStructure);				//��ʼ��Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
	*/
}
//========================================================================
// ����: void PWM_Set(u16 duty)
// ����: PWM����ռ�ձȺ���(ռ�ձȼ��ߵ�ѹ������PWM�����еı���)
// ����: duty: �ߵ�ѹռ��ʱ��������
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2020.03.09
//========================================================================
void PWM_Set(u16 duty)
{
	if( duty > PWM_HIGH_MAX)		duty = PWM_HIGH_MAX;	//���д��������ռ�ձ����ݣ���ǿ��Ϊ���ռ�ձȡ�
	if( duty < PWM_HIGH_MIN)		duty = PWM_HIGH_MIN;	//���д��С����Сռ�ձ����ݣ���ǿ��Ϊ��Сռ�ձȡ�
	EA = 0;
	PWM_high = 65536UL- duty;	//װ��PWM�ߵ�ƽʱ��
	PWM_low  = 65536UL- (PWM_CYCLE - duty);							//װ��PWM�͵�ƽʱ��
	EA = 1;
}



/********************* Timer0�жϺ���************************/
void Timer0_Int (void) interrupt TIMER0_VECTOR
{
   if(P35)
	{
		TH0 = (u8)(PWM_low >> 8);	//���������ߵ�ƽ����װ�ص͵�ƽʱ�䡣
		TL0 = (u8)PWM_low;
	}
	else
	{
		TH0 = (u8)(PWM_high >> 8);	//���������͵�ƽ����װ�ظߵ�ƽʱ�䡣
		TL0 = (u8)PWM_high;
	}
}

/********************* Timer1�жϺ���************************/
/*
void Timer1_Int (void) interrupt TIMER1_VECTOR
{
   P11 = ~P11;

}
*/
/********************* Timer2�жϺ���************************/
/*
void Timer2_Int (void) interrupt TIMER2_VECTOR
{
	P12 = ~P12;
}
*/
/********************* Timer3�жϺ���************************/
/*
void Timer3_Int (void) interrupt TIMER3_VECTOR
{
	P13 = ~P13;
}
*/
/********************* Timer4�жϺ���************************/
/*
void Timer5_Int (void) interrupt TIMER4_VECTOR
{
	P14 = ~P14;
}
*/