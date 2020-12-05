#include	"MCU_Init.h"

/*************	����˵��	**************

��������Ҫִ�г�ʼ������������:
		1.GPIO���ų�ʼ��������ʹ��GPIO_Config()�������������������ģʽ��GPIO_Init()����Ĭ������GPIOΪ��׼˫���
		2.����GPIO���ų�ʼ��
		3.OLED��ʼ����OLED����
		4.UART��ʼ��
		5.Timer��ʼ��
		6.EA=1,�����ж�



******************************************/
//========================================================================
// ����: void MCU_Init(void)
// ����: ��Ƭ����ʼ������
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void MCU_Init(void)
{
    GPIO_Init();		//GPIO ��ʼ��
	  OLED_Init();		//OLED ��ʼ��
    OLED_CLS();     //OLED ����
		Uart_Init();    //UART ��ʼ��
    Timer_Config(); //��ʱ����ʼ������
		P1=0x00;
		//OLED��ʾ
    OLED_P6x8Str(8, 0, "Welcome Demo System");
		EA = 1; 					//�����ж�
}
/*
//========================================================================
// ����: void	GPIO_Config(void)
// ����: GPIO�����ù���ģʽ
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void	GPIO_Config(void)
{
	//����������������P3^4,P3^5���Ź���ģʽΪGPIO_OUT_PP(�������)
	GPIO_InitTypeDef	GPIO_InitStructure;								//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_4 | GPIO_Pin_5;	//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_OUT_PP;							//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Set(GPIO_P3,&GPIO_InitStructure);					//��ʼ��
}
*/