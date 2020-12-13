#include "OLED_Method.h"



/************************************************************************************
*
* 2. void IIC_Start() -- ����I2C����
* 3. void IIC_Stop() -- �ر�I2C����
* 4. void Write_IIC_Byte(unsigned char IIC_Byte) -- ͨ��I2C����дһ��byte������
* 5. void OLED_WrDat(unsigned char dat) -- ��OLED��д����
* 6. void OLED_WrCmd(unsigned char cmd) -- ��OLED��д����
* 7. void OLED_Set_Pos(unsigned char x, unsigned char y) -- ������ʾ����
* 8. void OLED_Fill(unsigned char bmp_dat) -- ȫ����ʾ(��ʾBMPͼƬʱ�Ż��õ��˹���)
* 9. void OLED_CLS(void) -- ��λ/����
* 10. void OLED_CLS_Local(unsigned char first_x,first_y,last_x,last_y) -- OLED�ֲ���λ/����
* 11. void OLED_Init(void) -- OLED����ʼ�����򣬴˺���Ӧ�ڲ�����Ļ֮ǰ���ȵ���
* 12. void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]) -- 6x8������������ʾASCII�����С���У���̫����
* 13. void OLED_P8x16Str(unsigned char x, y,unsigned char ch[]) -- 8x16������������ʾASCII�룬�ǳ�����
* 14. void OLED_P16x16Ch(unsigned char x, y, N) -- 16x16������������ʾ���ֵ���С���У������ø������塢�Ӵ֡���б���»��ߵ�
* 15. void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- ��128x64���ص�BMPλͼ��ȡ�����������ֱ�Ȼ���Ƶ�codetab�У��˺������ü���
*
*************************************************************************************/

//========================================================================
// ����: void IIC_Start()
// ����: ����I2C����
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void IIC_Start()
{
   SCL = Hight_Voltage;		
   SDA = Hight_Voltage;
   SDA = Low_Voltage;
   SCL = Low_Voltage;
}

//========================================================================
// ����: void IIC_Stop()
// ����: �ر�I2C����
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void IIC_Stop()
{
   SCL = Low_Voltage;
   SDA = Low_Voltage;
   SCL = Hight_Voltage;
   SDA = Hight_Voltage;
}

//========================================================================
// ����: void Write_IIC_Byte(unsigned char IIC_Byte)
// ����: ͨ��I2C����дһ��byte������
// ����: IIC_Byte:��Ҫд���һ��byte����
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(IIC_Byte & 0x80)
			SDA=Hight_Voltage;
		else
			SDA=Low_Voltage;
		SCL=Hight_Voltage;
		SCL=Low_Voltage;
		IIC_Byte<<=1;
	}
	SDA=1;
	SCL=1;
	SCL=0;
}
//========================================================================
// ����: void OLED_WrDat(unsigned char IIC_Data)
// ����: ��OLED��д����
// ����: IIC_Data:��OLED��д��һ��byte����
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Byte(IIC_Data);
	IIC_Stop();
}
//========================================================================
// ����: void OLED_WrCmd(unsigned char IIC_Command)
// ����: ��OLED��д����
// ����: IIC_Command:��Ҫд�������
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	Write_IIC_Byte(0x00);			//write command
	Write_IIC_Byte(IIC_Command);
	IIC_Stop();
}
//========================================================================
// ����: void OLED_Set_Pos(unsigned char x, unsigned char y) 
// ����: ������ʾ����
// ����: x:������; y:������;
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
/*********************OLED ��������************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
//========================================================================
// ����: void OLED_Fill(unsigned char bmp_dat) 
// ����: ȫ����ʾ(��ʾBMPͼƬʱ�Ż��õ��˹���)
// ����: bmp_dat:��ʾBPM��ʽͼƬ����
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
/*********************OLEDȫ��************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*
//========================================================================
// ����: void OLED_CLS(void)
// ����: ��λ/����
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}
*/
//========================================================================
// ����: void OLED_CLS_Local(unsigned char first_x,first_y,last_x,last_y)
// ����: OLED�ֲ���λ/����
// ����: first_x:��������ʼλ��;first_y:��������ʼλ��;last_x:��������ֹλ��;last_y:��������ֹλ��;
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void OLED_CLS_Local(unsigned char first_x,first_y,last_x,last_y)
{
	unsigned char y,x;
	for(y=first_y;y<=last_y;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=first_x;x<last_x;x++)
		OLED_WrDat(0);
	}
}
//========================================================================
// ����: void OLED_Init(void)
// ����: OLED��ʼ��
// ����: ��
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
void OLED_Init(void)
{
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set Low_Voltage column address
	OLED_WrCmd(0x10);//---set Hight_Voltage column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //��ʼ����
	OLED_Set_Pos(0,0);
} 
//========================================================================
// ����: void OLED_P6x8Str(unsigned char x, y,unsigned char ch[])
// ����: ����ch[]��ʾOLED
// ����: x:��ʼ������;y:��ʼ������;ch[]:��ʾ�ַ���
// ����: ��
// �汾: V1.0, 2020.03.09
//========================================================================
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����ch[]Ϊ��Ҫ������ַ���****************/
//ע�⣺���Code�е��ַ���ASCII��һ�£������ִ�����ʾ
void OLED_P6x8Str(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	}
}