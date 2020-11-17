#include "MCU_OLED_Show.h"

//========================================================================
// 函数: void MCU_OLED_StatusChange(unsigned char flag)
// 描述: 手机连接后，MCU控制模块状态显示
// 参数: flag:操作标记位，根据操作符号，更改OLED状态显示
// 返回: 无
// 说明:
// 版本: V1.0, 2020.03.09
//========================================================================
void MCU_OLED_StatusChange(unsigned char flag)
{
	if(Phone_flag){
		if(flag==0x00){OLED_CLS_Local(0,4,X_WIDTH,Y_WIDTH); OLED_P6x8Str(6,4,"L1:0 L2:0 L3:0 L4:0");}
		if(flag==0x01||flag==0x00){if(P14==0x01){OLED_P6x8Str(24,4,"1");}else{OLED_P6x8Str(24,4,"0");} }
		if(flag==0x02||flag==0x00){if(P15==0x01){OLED_P6x8Str(54,4,"1");}else{OLED_P6x8Str(54,4,"0");}}
		if(flag==0x04||flag==0x00){if(P16==0x01){OLED_P6x8Str(84,4,"1");}else{OLED_P6x8Str(84,4,"0");} }
		if(flag==0x08||flag==0x00){if(P17==0x01){OLED_P6x8Str(114,4,"1");}else{OLED_P6x8Str(114,4,"0");} }
	}
	else{OLED_CLS_Local(0,4,X_WIDTH,6);}
}


//========================================================================
// 函数: void MCU_OLED_MessageShow(unsigned char Order,unsigned char Wifi_status_1,unsigned char Wifi_status_2)
// 描述: 系统OLED显示函数,主要显示WiFi连接状态
// 参数: Order:WiFi推送状态命令;Wifi_status_1,Wifi_status_2:WiFi状态标记位
// 返回: 无
// 说明:
// 版本: V1.0, 2020.03.09
//========================================================================
void MCU_OLED_MessageShow(unsigned char Order,unsigned char Wifi_status_1,unsigned char Wifi_status_2)
{
	//推送wifi状态
	if(Order==0x0d)
	{
		//清除第三行及以下所有行
		OLED_CLS_Local(0,2,X_WIDTH,4); 
		switch(Wifi_status_2)
		{
			//SoftAP模式开启
			case 0x01:OLED_P6x8Str(6,2,"M:A");
				break;
			//Station模式开启
			case 0x02:OLED_P6x8Str(6,2,"M:S");
				break;
			//SoftAP模式开启，开启配置模式,配置使用SoftAP
			case 0x05:OLED_P6x8Str(6,2,"M:A C:S");
				break;
			//Station模式开启，开启配置模式,配置使用AirLink
			case 0x06:OLED_P6x8Str(6,2,"M:S C:A");
				break;
			//Station模式开启，成功连接路由器
			case 0x12:OLED_P6x8Str(6,2,"M:S C:A W:1");
				break;
			//Station模式开启，成功连接路由器，开启绑定模式
			case 0x1A:OLED_P6x8Str(6,2,"M:S C:A W:1");
				break;
			//Station模式开启，成功连接路由器，开启绑定模式，连接上云端
			case 0x3A:
					//Station模式开启，成功连接路由器，开启绑定模式，连接上云端，无手机连接
					if(Wifi_status_1>=0x00 && Wifi_status_1<=0x07 )
					{	OLED_P6x8Str(6,2,"M:S C:A W:1 N:1");}
					//Station模式开启，成功连接路由器，开启绑定模式，连接上云端，有手机连接
					if(Wifi_status_1>=0x08 && Wifi_status_1<=0x0F )
					{	OLED_P6x8Str(6,2,"M:S C:A W:1 N:1 P:1");}
				break;	
		}
	}
}