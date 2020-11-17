#ifndef __OLED_Method_H__
#define __OLED_Method_H__

#include "MCU_Config.h"

// ------------------------------------------------------------
// IO口模拟I2C通信
// SCL接P1^3
// SDA接P1^2
// ------------------------------------------------------------
sbit SCL=P4^1; //串行时钟
sbit SDA=P2^2; //串行数据

#define Hight_Voltage 1
#define Low_Voltage 0
#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	8


extern void OLED_CLS(void);
extern void OLED_CLS_Local(unsigned char first_x,first_y,last_x,last_y);
extern void OLED_Init(void);
extern void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]);

#endif