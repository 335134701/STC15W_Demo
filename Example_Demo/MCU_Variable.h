#ifndef __MCU_VARIABLE_H__
#define __MCU_VARIABLE_H__

//wifi是否连接标记位
extern unsigned char Wifi_flag;
//手机连接信号标记位
extern unsigned char Phone_flag;
//网络连接信号标记位
extern unsigned char Net_flag;

extern unsigned int MinOrder;
//设备信息字符串
extern const unsigned char Device_information[115];

#endif