#ifndef __MCU_VARIABLE_H__
#define __MCU_VARIABLE_H__

//wifi模块是否连接标记位
extern unsigned char Wifi_flag;
//手机连接信号标记位
extern unsigned char Phone_flag;
//网络连接信号标记位
extern unsigned char Net_flag;
//接收串口数据最小命令单位长度
extern unsigned int MinOrder;
//数据包序号
extern unsigned char Sn;
//========================================================================
// 描述: 设备信息组成
// 参数: 公共基础协议(8),
//			 通用串口协议版本号(8),
//			 业务协议版本号(8)
//			 硬件版本号(8)
//			 软件版本号(8)
//			 产品标示码(32)
//			 可绑定状态失效时间(2)
//			 设备属性(8)
//			 产品密钥(32)
//			 校验和(1)
// 版本: V1.0, 2020.12.02
//========================================================================
//硬件版本号
extern const unsigned char HardVersion[8];
//软件版本号
extern const unsigned char SoftVersion[8];
//产品标识码
extern const unsigned char ProductKey[32];
//产品密钥
extern const unsigned char ProductSecert[32];
//设备属性
extern const unsigned char	DeviceAttributes[8];
//串口协议版本号
extern const unsigned char SerialProVersion[8];
//业务协议版本号
extern const unsigned char BusinessProVersion[8];
//公共基础协议
extern const unsigned char PublicAgreement[9];

#endif