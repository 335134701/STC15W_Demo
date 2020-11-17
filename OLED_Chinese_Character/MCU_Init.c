#include	"MCU_Config.h"


/******************** MCU初始化函数 **************************/
void MCU_Init(void)
{
		GPIO_Init();		//GPIO 初始化
		OLED_Init(); 		//OLED初始化
}

/******************** IO配置函数 **************************/
//注意:   STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
//        高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
void GPIO_Init(void)
{
	//第一种方式：使用P0n_standard()函数将所有IO口设置为准双向口，默认选择第一种
	P0n_standard(0xff);	//设置为准双向口
	P1n_standard(0xff);	//设置为准双向口
	P2n_standard(0xff);	//设置为准双向口
	P3n_standard(0xff);	//设置为准双向口
	P4n_standard(0xff);	//设置为准双向口
	P5n_standard(0xff);	//设置为准双向口
}
