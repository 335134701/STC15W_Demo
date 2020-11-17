#include	"MCU_Config.h"

//========================================================================
// ����: void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty)
// ����: ����PWMʱ��Դ�����ں�����
// ����: PWM_SourceClk: PWMʱ��Դ, 0~15��Ӧ ��ʱ��/(PWM_SourceClk + 1), 16Ϊѡ��ʱ��2�������ʱ��.
//                      PwmClk_1T,PwmClk_2T, ... PwmClk_16T, PwmClk_T2.
//       init_duty: PWM���ڳ���, 1~32767.
// ����: none.
// �汾: VER1.0
// ����: 2020.03.09
// ��ע: 
//========================================================================
void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty)
{
	u8	xdata	*px;

	EAXSFR();		// ����XFR
	px  = PWMCKS;	// PWMʱ��ѡ��
	*px = PWM_SourceClk;
	px  = PWMCH;	// PWM�������ĸ��ֽ�
	*px = (u8)(init_duty >> 8);
	px++;
	*px = (u8)init_duty;	// PWM�������ĵ��ֽ�
	EAXRAM();	//�ָ�����XRAM
}


//========================================================================
// ����: void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx)
// ����: PWM���ú�����
// ����: PWM_id: PWMͨ��, PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID.
//       *PWMx:  ���ýṹָ��.
// ����: none.
// �汾: VER1.0
// ����: 2020.03.09
// ��ע: 
//========================================================================
void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx)
{
	u8	xdata	*px;

	EAXSFR();		//����XFR
	px = PWM2T1H + (PWM_id << 4);
	*px = (u8)(PWMx->FirstEdge >> 8);	//��һ����ת�������ֽ�
	px++;
	*px = (u8)PWMx->FirstEdge;			//��һ����ת�������ֽ�
	px++;
	*px = (u8)(PWMx->SecondEdge >> 8);	//�ڶ�����ת�������ֽ�
	px++;
	*px = (u8)PWMx->SecondEdge;			//�ڶ�����ת�������ֽ�
	px++;
	*px = (PWMx->PWMx_IO_Select & 0x08)					// PWM���IOѡ��
	    | ((PWMx->PWMx_Interrupt << 2) & 0x04)			// �ж�����
		| ((PWMx->SecondEdge_Interrupt << 1) & 0x02)	// �ڶ�����ת�ж�����
		| (PWMx->FirstEdge_Interrupt & 0x01);			// ��һ����ת�ж�����
	PWMCR |= (1 << PWM_id);	// ��ӦPWMͨ���Ķ˿�ΪPWM����ڣ���PWM���η���������
	PWMCFG = (PWMCFG & ~(1 << PWM_id)) | ((PWMx->Start_IO_Level & 1) << PWM_id);	//����PWM����˿ڵĳ�ʼ��ƽ
	EAXRAM();		//�ָ�����XRAM
}

//========================================================================
// ����: void	PWMx_SetPwmWide(u8 PWM_id, u16 FirstEdge, u16 SecondEdge)
// ����: PWM���������Ⱥ�����
// ����: PWM_id: PWMͨ��, PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID.
//       FirstEdge:   ��һ����ת����.
//       SecondEdge:  ��һ����ת����.
// ����: none.
// �汾: VER1.0
// ����: 2020.03.09
// ��ע: 
//========================================================================

void	PWMx_SetPwmWide(u8 PWM_id, u16 FirstEdge, u16 SecondEdge)
{
	u8	xdata	*px;

	EAXSFR();		//����XFR
	px = PWM2T1H + (PWM_id << 4);
	*px = (u8)(FirstEdge >> 8);	//��һ����ת�������ֽ�
	px++;
	*px = (u8)FirstEdge;			//��һ����ת�������ֽ�
	px++;
	*px = (u8)(SecondEdge >> 8);	//�ڶ�����ת�������ֽ�
	px++;
	*px = (u8)SecondEdge;			//�ڶ�����ת�������ֽ�
	EAXRAM();		//�ָ�����XRAM
}



//========================================================================
// ����: void	PWM_config(void)
// ����: PWM���ú�����
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2020.03.09
// ��ע: 
//========================================================================
void	PWM_Config(void)
{
	PWMx_InitDefine		PWMx_InitStructure;					//�ṹ����
	
	PWMx_InitStructure.PWMx_IO_Select       = PWM2_P37;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 0;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = DISABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = DISABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 64;			//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 192;			//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM2_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P3n_standard(1<<7);										//IO��ʼ��, �ϵ�ʱΪ����

	PWMx_InitStructure.PWMx_IO_Select       = PWM3_P21;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 0;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = DISABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = DISABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 64;			//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 192;			//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM3_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P2n_standard(1<<1);										//IO��ʼ��, �ϵ�ʱΪ����

	PWMx_InitStructure.PWMx_IO_Select       = PWM4_P22;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 0;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = DISABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = DISABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 64;			//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 192;			//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM4_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P2n_standard(1<<2);										//IO��ʼ��, �ϵ�ʱΪ����

	PWMx_InitStructure.PWMx_IO_Select       = PWM5_P23;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 0;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = DISABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = DISABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 64;			//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 192;			//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM5_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P2n_standard(1<<3);										//IO��ʼ��, �ϵ�ʱΪ����

	PWMx_InitStructure.PWMx_IO_Select       = PWM6_P07;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 0;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = DISABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = DISABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 64;			//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 192;			//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM6_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P0n_standard(1<<7);										//IO��ʼ��, �ϵ�ʱΪ����

	PWMx_InitStructure.PWMx_IO_Select       = PWM7_P06;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 0;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = ENABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = ENABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 64;			//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 192;			//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM7_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P0n_standard(1<<6);										//IO��ʼ��, �ϵ�ʱΪ����

	TH2 = (u8)((65536UL - MAIN_Fosc / 500000UL) / 256);	//������ʹ��Timer2
	TL2 = (u8)((65536UL - MAIN_Fosc / 500000UL) % 256);
	AUXR = 0x14;		//Timer2 set As Timer, Timer2 set as 1T mode;
	PWM_SourceClk_Duty(PwmClk_T2, 256);	//ʱ��Դ: PwmClk_1T,PwmClk_2T, ... PwmClk_16T, PwmClk_T2,   PWM����: 1~32767
	
	PWMCR |= ENPWM;		// ʹ��PWM���η�������PWM��������ʼ����
	PWMCR &= ~ECBI;		//��ֹPWM�����������ж�
//	PWMCR |=  ECBI;		//����PWM�����������жϣ������������жϣ�����Ҫ�����жϱ�ǣ���EA=1;

//	PWMFDCR = ENFD | FLTFLIO | FDIO;	//PWMʧЧ�жϿ���,  ENFD | FLTFLIO | EFDI | FDCMP | FDIO
}



/********************* PWM�жϺ���************************/
void PWM_int (void) interrupt PWM_VECTOR
{
	if(PWMIF & CBIF)	//PWM�����������жϱ�־
	{
		PWMIF &= ~CBIF;	//����жϱ�־
	}
	if(PWMIF & C2IF)	//PWM2�жϱ�־
	{
		PWMIF &= ~C2IF;	//����жϱ�־
	}
	if(PWMIF & C3IF)	//PWM3�жϱ�־
	{
		PWMIF &= ~C3IF;	//����жϱ�־
	}
	if(PWMIF & C4IF)	//PWM4�жϱ�־
	{
		PWMIF &= ~C4IF;	//����жϱ�־
	}
	if(PWMIF & C5IF)	//PWM5�жϱ�־
	{
		PWMIF &= ~C5IF;	//����жϱ�־
	}
	if(PWMIF & C6IF)	//PWM6�жϱ�־
	{
		PWMIF &= ~C6IF;	//����жϱ�־
	}
	if(PWMIF & C7IF)	//PWM7�жϱ�־
	{
		PWMIF &= ~C7IF;	//����жϱ�־
	}
}

/********************* PWMʧЧ�жϺ���************************/
void PWMFD_int (void) interrupt PWMFD_VECTOR
{
	if(PWMFDCR & FDIF) 		//PWM�쳣����жϱ�־λ
	{
		PWMFDCR &= ~FDIF;	//����жϱ�־
	}
}

