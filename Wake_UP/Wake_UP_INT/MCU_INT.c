#include	"MCU_Config.h"


//========================================================================
// 函数: void INT_Init(void)
// 描述: 外部中断初始化函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void INT_Init(void)
{
		IE1  = 0;			//外中断1标志位
		IE0  = 0;			//外中断0标志位
		EX1 = 1;			//INT1 Enable
		EX0 = 1;			//INT0 Enable

		IT0 = 1;			//INT0 下降沿中断		
	//IT0 = 0;			//INT0 上升,下降沿中断	
		IT1 = 1;			//INT1 下降沿中断		
	//IT1 = 0;			//INT1 上升,下降沿中断	
}

/********************* INT0中断函数 *************************/
void INT0_int (void) interrupt INT0_VECTOR		//进中断时已经清除标志
{
			//EX0 = 0;	//INT0 Disable
			//IE0 = 0;	//外中断0标志位
}

/********************* INT1中断函数 *************************/
void INT1_int (void) interrupt INT1_VECTOR		//进中断时已经清除标志
{
		EX1 = 0;	//INT1 Disable
		IE1 = 0;	//外中断1标志位
}
