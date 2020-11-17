#include	"MCU_Config.h"


//========================================================================
// ����: void ADC_Init(void)
// ����: ADC��ʼ��
// ����: channel: ѡ��Ҫת����ADC.
// ����: 10λADC���.
// �汾: V1.0, 2020.03.09
//========================================================================
void ADC_Init(void)
{
			P1ASF=0x01;		//����ԭ��ͼ���Ŷ��壬ʹ��P1.0~P1.7��ADC����ʹ��ĳһλ���򽫸�λ��1����P1.2����ֵΪ0x04
			//sfr ADC_CONTR = 0xBC;		ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0 0000,0000	/* AD ת�����ƼĴ��� */ 
			ADC_CONTR = 0xE0;			//90T, ADC power on
}
//========================================================================
// ����: u16	Get_ADC10bitResult(u8 channel)
// ����: ��ѯ����һ��ADC���.
// ����: channel: ѡ��Ҫת����ADC.
// ����: 10λADC���.
// �汾: V1.0, 2020.03.09
//========================================================================
u16	Get_ADC10bitResult(u8 channel)	//channel = 0~7
{
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | 0x08 | channel; 	//start the ADC
	NOP(4);

	while((ADC_CONTR & 0x10) == 0)	;	//wait for ADC finish
	ADC_CONTR &= ~0x10;		//���ADC������־
	return	(((u16)ADC_RES << 2) | (ADC_RESL & 3));
}
//========================================================================
// ����: void Int_cov_Str(u8 *buf,u16 buf_len,u16 num)
// ����: ����ֵתΪ�ַ�����
// ����: bufת������ַ����飬buf_len�ַ����鳤�ȣ�num��Ҫ����ת��������
// ����: 10λADC���.
// �汾: V1.0, 2020.03.09
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