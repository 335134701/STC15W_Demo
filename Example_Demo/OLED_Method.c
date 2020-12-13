#include "OLED_Method.h"



/************************************************************************************
*
* 2. void IIC_Start() -- 开启I2C总线
* 3. void IIC_Stop() -- 关闭I2C总线
* 4. void Write_IIC_Byte(unsigned char IIC_Byte) -- 通过I2C总线写一个byte的数据
* 5. void OLED_WrDat(unsigned char dat) -- 向OLED屏写数据
* 6. void OLED_WrCmd(unsigned char cmd) -- 向OLED屏写命令
* 7. void OLED_Set_Pos(unsigned char x, unsigned char y) -- 设置显示坐标
* 8. void OLED_Fill(unsigned char bmp_dat) -- 全屏显示(显示BMP图片时才会用到此功能)
* 9. void OLED_CLS(void) -- 复位/清屏
* 10. void OLED_CLS_Local(unsigned char first_x,first_y,last_x,last_y) -- OLED局部复位/清屏
* 11. void OLED_Init(void) -- OLED屏初始化程序，此函数应在操作屏幕之前最先调用
* 12. void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]) -- 6x8点整，用于显示ASCII码的最小阵列，不太清晰
* 13. void OLED_P8x16Str(unsigned char x, y,unsigned char ch[]) -- 8x16点整，用于显示ASCII码，非常清晰
* 14. void OLED_P16x16Ch(unsigned char x, y, N) -- 16x16点整，用于显示汉字的最小阵列，可设置各种字体、加粗、倾斜、下划线等
* 15. void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- 将128x64像素的BMP位图在取字软件中算出字表，然后复制到codetab中，此函数调用即可
*
*************************************************************************************/

//========================================================================
// 函数: void IIC_Start()
// 描述: 开启I2C总线
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void IIC_Start()
{
   SCL = Hight_Voltage;		
   SDA = Hight_Voltage;
   SDA = Low_Voltage;
   SCL = Low_Voltage;
}

//========================================================================
// 函数: void IIC_Stop()
// 描述: 关闭I2C总线
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void IIC_Stop()
{
   SCL = Low_Voltage;
   SDA = Low_Voltage;
   SCL = Hight_Voltage;
   SDA = Hight_Voltage;
}

//========================================================================
// 函数: void Write_IIC_Byte(unsigned char IIC_Byte)
// 描述: 通过I2C总线写一个byte的数据
// 参数: IIC_Byte:需要写入的一个byte数据
// 返回: 无
// 版本: V1.0, 2020.03.09
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
// 函数: void OLED_WrDat(unsigned char IIC_Data)
// 描述: 向OLED屏写数据
// 参数: IIC_Data:向OLED屏写入一个byte数据
// 返回: 无
// 版本: V1.0, 2020.03.09
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
// 函数: void OLED_WrCmd(unsigned char IIC_Command)
// 描述: 向OLED屏写命令
// 参数: IIC_Command:需要写入的命令
// 返回: 无
// 版本: V1.0, 2020.03.09
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
// 函数: void OLED_Set_Pos(unsigned char x, unsigned char y) 
// 描述: 设置显示坐标
// 参数: x:横坐标; y:纵坐标;
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
//========================================================================
// 函数: void OLED_Fill(unsigned char bmp_dat) 
// 描述: 全屏显示(显示BMP图片时才会用到此功能)
// 参数: bmp_dat:显示BPM格式图片数据
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
/*********************OLED全屏************************************/
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
// 函数: void OLED_CLS(void)
// 描述: 复位/清屏
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
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
// 函数: void OLED_CLS_Local(unsigned char first_x,first_y,last_x,last_y)
// 描述: OLED局部复位/清屏
// 参数: first_x:横坐标起始位置;first_y:纵坐标起始位置;last_x:横坐标终止位置;last_y:纵坐标终止位置;
// 返回: 无
// 版本: V1.0, 2020.03.09
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
// 函数: void OLED_Init(void)
// 描述: OLED初始化
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
void OLED_Init(void)
{
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set Low_Voltage column address
	OLED_WrCmd(0x10);//---set Hight_Voltage column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
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
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
} 
//========================================================================
// 函数: void OLED_P6x8Str(unsigned char x, y,unsigned char ch[])
// 描述: 根据ch[]显示OLED
// 参数: x:起始横坐标;y:起始纵坐标;ch[]:显示字符集
// 返回: 无
// 版本: V1.0, 2020.03.09
//========================================================================
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），ch[]为需要输出的字符串****************/
//注意：如果Code中的字符与ASCII不一致，则会出现错误显示
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