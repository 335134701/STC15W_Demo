#include "MCU_Timer.h"

int Timer0_Count=0;
int Timer1_Count=0;
int Timer2_Count=0;
int Timer3_Count=0;
int Timer4_Count=0;

/*************	����˵��	**************

��������ʾ3����ʱ����ʹ�á�
ע�⣺����ʱ���������������Ǹ���ԭ��ͼ�����Ŷ�������ġ�
			P3.4,P3.5 �жϺ͸���ʱ�������ͬһ�����ϣ�����Ҫ���Ÿ��á�
			����P3.4,P3.5����Ϊ���������
			������P3.4,P3.5����ʱ�����Ϊ�����������������������������Ĭ�ϼ���

��ʱ��0����Ϊ16λ�Զ���װ, 20000HZ�ж���(50us��ʱ)
         �������ʱ�����ʱ��P3.4���10KHZʱ���źš�
         �����ж�ʱ��P1.0ȡ�����10KHZ�����źš�
��ʱ��1����Ϊ16λ�Զ���װ, 2000HZ�ж���(500us��ʱ)
         �������ʱ�����ʱ��P3.5���1000HZʱ���źš�
         �����ж�ʱ��P1.1ȡ�����1000HZ�����źš�
��ʱ��2�̶�Ϊ16λ�Զ���װ, 1000HZ�ж���(1ms��ʱ)
         �������ʱ�����ʱ��P3.0���500HZʱ���źš�
         �����ж�ʱ��P1.2ȡ�����500HZ�����źš�
��ʱ��3�̶�Ϊ16λ�Զ���װ, 200HZ�ж���(5ms��ʱ)
         �������ʱ�����ʱ��P0.6���100HZʱ���źš�
         �����ж�ʱ��P1.3ȡ�����100HZ�����źš�
��ʱ��4�̶�Ϊ16λ�Զ���װ, 100HZ�ж���(10ms��ʱ)
         �������ʱ�����ʱ��P0.4���50HZʱ���źš�
         �����ж�ʱ��P1.4ȡ�����50HZ�����źš�

�û������޸����Ƶ�ʣ���ע��ʱ�䲻Ҫ̫�ߣ�һ��100KHZ���£���


******************************************/

//========================================================================
// ����: unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned char	Timer_Init(unsigned char TIM, TIM_InitTypeDef *TIMx)
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
		
		TH0 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL0 = (unsigned char)TIMx->TIM_Value;
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
		
		TH1 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL1 = (unsigned char)TIMx->TIM_Value;
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

		TH2 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL2 = (unsigned char)TIMx->TIM_Value;
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

		TH3 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL3 = (unsigned char)TIMx->TIM_Value;
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

		TH4 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL4 = (unsigned char)TIMx->TIM_Value;
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
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 20000);		//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	Timer0_Count=0;

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 2000);		//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer1,&TIM_InitStructure);				//��ʼ��Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4
	Timer1_Count=0;
/*
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (1000*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer2,&TIM_InitStructure);				//��ʼ��Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	Timer2_Count=0;
*/
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer3�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (200*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer3,&TIM_InitStructure);				//��ʼ��Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4
	Timer3_Count=0;

	TIM_InitStructure.TIM_Interrupt = DISABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer4�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (100*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer4,&TIM_InitStructure);				//��ʼ��Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
	Timer4_Count=0;

}


//========================================================================
// ����: void Timer0_Int (void) interrupt TIMER0_VECTOR
// ����: ��ʱ��0�жϺ���
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void Timer0_Int (void) interrupt TIMER0_VECTOR
{
   Timer0_Count++;
}

//========================================================================
// ����: void Timer1_Int (void) interrupt TIMER1_VECTOR
// ����: ��ʱ��1�жϺ���
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void Timer1_Int (void) interrupt TIMER1_VECTOR
{
    Timer1_Count++;
}

//========================================================================
// ����: void Timer2_Int (void) interrupt TIMER2_VECTOR
// ����: ��ʱ��2�жϺ���
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void Timer2_Int (void) interrupt TIMER2_VECTOR
{
	 Timer2_Count++;
}

//========================================================================
// ����: Timer3_Int (void) interrupt TIMER3_VECTOR
// ����: ��ʱ��3�жϺ���
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void Timer3_Int (void) interrupt TIMER3_VECTOR
{
	 Timer3_Count++;
}

//========================================================================
// ����: void Timer4_Int (void) interrupt TIMER4_VECTOR
// ����: ��ʱ��4�жϺ���
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void Timer4_Int (void) interrupt TIMER4_VECTOR
{
	 Timer4_Count++;
}