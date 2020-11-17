#include "MCU_Method.h"

//========================================================================
// ����: void Delay_ms(unsigned int time)
// ����: �����ʱ����
// ����: time:��ʱʱ��
// ����: ��
// ˵������Ƭ��Ƶ�ʲ�ͬ����ʱЧ����ͬ
// �汾: V1.0, 2020.03.09
//========================================================================
void Delay_ms(unsigned int time)
{
	unsigned int x,y;
	for(x=time;x>0;x--)
		for(y=110;y>0;y--);
}
//========================================================================
// ����: void RST_Uart_Timer()
// ����: ��ʼ�����ڽ�����ز���������
// ����: ��
// ����: ��
// ˵�����˺�����Ҫ��ʼ���������ò���
// �汾: V1.0, 2020.03.09
//========================================================================
void RST_Uart_Timer()
{
		RX1_len=0;
		memset(RX1_Buffer,0,sizeof(RX1_Buffer));
		//�򿪴��ڽ��պ���
		REN=1;
}
//========================================================================
// ����: unsigned char Uart_Pretreatment()
// ����: ���ݽ���Ԥ������
// ����: ��
// ����: ��
// ˵�����˺�����Ҫ���������ַ�������У���ַ���
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned char Uart_Pretreatment()
{
	//Check_protocol_flag��ʾ���������Ƿ���Ч���λ
	unsigned char Check_protocol_flag=0;
	if((RX1_len>0)&&!B_TX1_Busy)
	{
			//********************************
			Delay_ms(500);
			//ֹͣ���ڽ���
			REN=0;
			//����2���������ӡ����
			Printf(0,RX1_Buffer,RX1_len);
			//����У���
			Check_protocol_flag=Check_Protocol(RX1_Buffer,RX1_len);	
			if(!Check_protocol_flag) { RST_Uart_Timer();}
	}
	else{RST_Uart_Timer();}
	return Check_protocol_flag;
}

//========================================================================
// ����: unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len)
// ����: ����У���
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len)
{
	unsigned char checksum=0x00;
	unsigned int i=0,len=Buf_len;
	for(i=2;i<(len-1);i++)
	{
		checksum=checksum+Buf[i];
	}
	checksum=checksum%256;
	return checksum;
}

//========================================================================
// ����: unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len)
// ����: ����У����Ƿ�һ��
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵��������˼��Ϊ�����յ���BUF��ȡУ��ͣ������µ�У��ͣ��Ա��Ƿ�һ�£�����һ�£���������Ч
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len)
{
	unsigned char Check_protocol_flag=0;
	//��ԭBUF��У�����ȡ
	unsigned char old_checksum=Buf[Buf_len-1];
	unsigned char new_checksum=0x00;
	//�����µ�У��Ͳ���ֵ��new_checksum
	new_checksum=Calculate_Checksum(Buf,Buf_len);
	//�Ƚ�ԭУ�������У����Ƿ�һ��
	if(new_checksum==old_checksum){Check_protocol_flag=1;}	
	return Check_protocol_flag;
}

//========================================================================
// ����: void Data_Encapsulation(unsigned char *Buf,unsigned int Buf_len,unsigned char order,sn,action)
// ����: ������Ҫ��������ݲ�����
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void Data_Encapsulation(unsigned char *Buf,unsigned int Buf_len,unsigned char order,sn,action)
{
		//�ж��Ƿ�ѯ�ʲ�Ʒ��Ϣ
	  if(Buf_len!=sizeof(Device_information))
		{
			switch(Buf_len)
			{
				case 9:	Buf[3]=0x05;break;
				case 10:Buf[3]=0x06;break;
				case 11:Buf[3]=0x07;break;
				case 12:Buf[3]=0x08;break;
				case 14:Buf[3]=0x0A;Buf[9]=(P1 >> 4 &0X0F);Buf[10]=1;Buf[11]=0x00;Buf[12]=0x00;break;
			}
			Buf[4]=order;
			Buf[5]=sn;
			if(Buf_len!=9){Buf[8]=action;}
		}
		//����У���
		Buf[Buf_len-1]=Calculate_Checksum(Buf,Buf_len);
		//����1�ظ�����
		SendString1(Buf,Buf_len);
		//����2ת����������
		Printf(1,Buf,Buf_len);
}
//========================================================================
// ����: void IsConnect_wifi()
// ����: �ж��Ƿ���յ������������û�н��յ���ʾ������wifiʧ��
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void IsConnect_wifi()
{
	if((Wifi_flag==1)&&(Timer0_Count==0)){TR0=1;}
	//����һ���ӻ�δ�յ�������������Ƭ����wifiģ��ʧȥ��ϵ
	if(Timer0_Count>=12000){
			TR0=0;Timer0_Count=0;
			Wifi_flag=0x00;
			Net_flag=0;
			Phone_flag=0;
			OLED_CLS_Local(0,2,X_WIDTH,Y_WIDTH);
			OLED_P6x8Str(36,4,"Wifi loss!");
	}
}
//========================================================================
// ����: void Printf(unsigned char flag,unsigned char *Buf,unsigned int len)
// ����: UART2���
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void Printf(unsigned char flag,unsigned char *Buf,unsigned int len)
{
	unsigned char Buf_HEX[RX1_Length]={0};
	switch(flag)
	{
		case 0:
					SendString2("RX:",3);
			break;
		case 1:
					SendString2("TX:",3);
			break;
	}
	HexToAscii(Buf_HEX,Buf,len);
	SendString2(Buf_HEX,(len*3-1));
	SendString2("\r\n",2);
}
//========================================================================
// ����: void HexToAscii(unsigned char *Buf_Dest,unsigned char *Buf_Src,unsigned int Buf_len)
// ����: HexתAscii
// ����: Buf_Dest:Ŀ���ַ���,Buf_Src:ԭ�ַ���,Buf_len:ԭ�ַ���ʵ�ʳ���;
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void HexToAscii(unsigned char *Buf_Dest,unsigned char *Buf_Src,unsigned int Buf_len)
{
	unsigned char Nibble[3]={0};
	unsigned char Buffer[RX1_Length]={0};
	int i = 0,j=0;
	for(i=0;i<Buf_len;i++)
	{
	
		Nibble[0]=Buf_Src[i] >> 4 & 0X0F;
		Nibble[1]=Buf_Src[i] & 0x0F;
		for(j=0;j<sizeof(Nibble)-1;j++)
		{
			if((Nibble[j]>=0x00)&&(Nibble[j]<0x0A)){Nibble[j]=Nibble[j]+'0';}
			else if((Nibble[j]>=0x0A)&&(Nibble[j]<=0x0F)){Nibble[j]=Nibble[j]-10+'A';}
			else{return;}
		}
		if(i<(Buf_len-1)){Nibble[2]=' ';}
		else{Nibble[2]='\0';}
		memcpy(Buffer+i*sizeof(Nibble),Nibble,sizeof(Nibble));
	}
	memcpy(Buf_Dest,Buffer,sizeof(Nibble)*Buf_len);
	return ;
}
/*
//========================================================================
// ����: void IntToHEX(unsigned char* str,int number)
// ����: ʮ����תʮ������
// ����: str:Ŀ���ַ���,number:ʮ��������
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void IntToHEX(unsigned char* str,int number)
{
    unsigned char i=0,j=0,CLen=0,index=0,RLen=0,TRlen=0;
    unsigned char tmp[16]={0};
    if(number==0){ str[0]=0x00;return;}
    while (number!=0)
    {
        i = number%2;
        number /= 2;
        tmp[index++] = i+48;
    }
    RLen=strlen(tmp);
    if(RLen%8==0){CLen=RLen/8;}else{CLen=RLen/8+1;}
    for(i=0;i<CLen;i++)
    {
        if(i==(CLen-1)){TRlen=RLen%8;}
        else{TRlen=8;}
        index=i*8;
        for(j=0;j<TRlen;j++){
            str[i]= ((tmp[index*i+j]-0x30) << j | str[i]);
        }
    }
}

//========================================================================
// ����: void AsciiToHex(unsigned char *Buf_Dest,unsigned char *Buf_Src,unsigned int Buf_len)
// ����: ASCIIתHEX
// ����: Buf_Dest:Ŀ���ַ���,Buf_Src:ԭ�ַ���,Buf_len:ԭ�ַ���ʵ�ʳ���;
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void AsciiToHex(unsigned char *Buf_Dest,unsigned char *Buf_Src,unsigned int Buf_len)
{
	unsigned int nHexLen = (Buf_len+1) / 3;
	unsigned char Nibble[3] = {0};
	unsigned int i = 0,j=0;
	if ((Buf_len+1)%3){return;}
	for (i = 0; i < nHexLen; i ++)
	{
		Nibble[0] = *Buf_Src ++;		
		Nibble[1] = *Buf_Src ++;
		if(i!=(nHexLen-1)){Nibble[2] = *Buf_Src ++;}
		for (j = 0; j < (sizeof(Nibble)-1); j ++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble [j] = Nibble[j] - '0';
			else
				return ;//Nibble[j] = Nibble[j] - 'a' + 10;
			
		}	// for (int j = ...)
		Buf_Dest[i] = Nibble[0] << 4;	// Set the high nibble
		Buf_Dest[i] |= Nibble[1];	//Set the low nibble
	}	// for (int i = ...)
	return;
}
*/
