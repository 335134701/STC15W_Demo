#include	"MCU_Config.h"



void main()
{
		//num为采样次数，sum为计算值
		u16 num=16,sum=0,i=0,tem=0;
		u8 buf[6]={0};
		MCU_Init();
		Delay_ms(10);
		EA=1; 		//打开总中断
		
		SendString1("Test  111111111\n");
		
		while(1){
				if(Timer1_Count==1000)
				{
						TR0 = 0;
						Timer1_Count=0;
						for(sum=0,i=0;i<num;i++) {sum+=Get_ADC10bitResult(0);}//读内部基准ADC, P1ASF=0, 读0通道
						sum = sum / num;	
						Int_cov_Str(buf,sizeof(buf),sum);
						SendString1("Tem:");
						SendString1(buf);
						SendString1("\n");
						memset(buf,0,sizeof(buf));
						TR0 =1;
				}
		}
	
}