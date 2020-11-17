#include	"MCU_Config.h"


//========================================================================
// 函数: void ADC_Init(void)
// 描述: ADC初始化
// 参数: channel: 选择要转换的ADC.
// 返回: 10位ADC结果.
// 版本: V1.0, 2020.03.09
//========================================================================
void ADC_Init(void)
{
			P1ASF=0x01;		//根据原理图引脚定义，使用P1.0~P1.7做ADC，若使用某一位，则将该位置1，如P1.2，则值为0x04
			//sfr ADC_CONTR = 0xBC;		ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0 0000,0000	/* AD 转换控制寄存器 */ 
			ADC_CONTR = 0xE0;			//90T, ADC power on
}
//========================================================================
// 函数: u16	Get_ADC10bitResult(u8 channel)
// 描述: 查询法读一次ADC结果.
// 参数: channel: 选择要转换的ADC.
// 返回: 10位ADC结果.
// 版本: V1.0, 2020.03.09
//========================================================================
u16	Get_ADC10bitResult(u8 channel)	//channel = 0~7
{
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | 0x08 | channel; 	//start the ADC
	NOP(4);

	while((ADC_CONTR & 0x10) == 0)	;	//wait for ADC finish
	ADC_CONTR &= ~0x10;		//清除ADC结束标志
	return	(((u16)ADC_RES << 2) | (ADC_RESL & 3));
}
//========================================================================
// 函数: void Int_cov_Str(u8 *buf,u16 buf_len,u16 num)
// 描述: 将数值转为字符数组
// 参数: buf转换后的字符数组，buf_len字符数组长度，num需要进行转换的数字
// 返回: 10位ADC结果.
// 版本: V1.0, 2020.03.09
//========================================================================
void Int_cov_Str(u8 *buf,u16 buf_len,u16 num)
{	
		u16 len=0,i=0,j=0,tem=0,mem=0,count=0;
		if(num>0&&num<10){count=1;}
		if(num>=10&&num<100){count=2;}
		if(num>=100&&num<1000){count=3;}
		if(num>=1000&&num<10000){count=4;}
		if(count>buf_len){return ;}
		if(count>2){
				for(i=0;i<count-2;i++)
				{
				    for(mem=1,j=0;j<count-1;j++){mem=mem*10;}
						tem=num/mem;
						num=num-tem*mem;
						buf[i]=tem+'0';
				}
				buf[count-2]=num/10+'0';buf[count-1]=num%10+'0';
		}
		else if(count==2){buf[0]=num/10+'0';buf[1]=num%10+'0';}
		else if(count==1){buf[0]=num+'0';}
}