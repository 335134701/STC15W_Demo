#include	"MCU_Init.h"

/*************	功能说明	**************

本程序主要执行初始化函数，包括:
		1.GPIO引脚初始化，可以使用GPIO_Config()方法设置引脚输入输出模式，GPIO_Init()方法默认设置GPIO为标准双向口
		2.部分GPIO引脚初始化
		3.OLED初始化，OLED清屏
		4.UART初始化
		5.Timer初始化
		6.EA=1,打开总中断

******************************************/

//========================================================================
// 函数: void MCU_Init(void)
// 描述: 单片机初始化函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void MCU_Init(void)
{
    GPIO_Init();		//GPIO 初始化
	  OLED_Init();		//OLED 初始化
    OLED_CLS();     //OLED 清屏
		Uart_Init();    //UART 初始化
    Timer_Config(); //定时器初始化函数
		P1=0x00;        //引脚初始化
		//OLED显示
    OLED_P6x8Str(8, 0, "Welcome Demo System");
		EA = 1; 					//开总中断
}
/*
//========================================================================
// 函数: void	GPIO_Config(void)
// 描述: GPIO口设置工作模式
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void	GPIO_Config(void)
{
	//本方法例程是设置P3^4,P3^5引脚工作模式为GPIO_OUT_PP(推挽输出)
	GPIO_InitTypeDef	GPIO_InitStructure;								//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_4 | GPIO_Pin_5;	//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_OUT_PP;							//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Set(GPIO_P3,&GPIO_InitStructure);					//初始化
}
*/