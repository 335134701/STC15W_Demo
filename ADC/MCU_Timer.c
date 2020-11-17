#include	"MCU_Config.h"

u16 Timer1_Count;

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
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);		//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Init(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
}


/********************* Timer0�жϺ���************************/
void Timer0_Int (void) interrupt TIMER0_VECTOR
{
   Timer1_Count++;
}
