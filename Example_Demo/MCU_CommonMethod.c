#include "MCU_CommonMethod.h"

//========================================================================
// 函数: void Delay_ms(unsigned int time)
// 描述: 软件延时函数
// 参数: time:延时时间
// 返回: 无
// 说明：单片机频率不同，延时效果不同
// 版本: V1.0, 2020.03.09
//========================================================================
void Delay_ms(unsigned int time)
{
    unsigned int x, y;
    for(x = time; x > 0; x--)
        for(y = 110; y > 0; y--);
}
//========================================================================
// 函数: void UART_BUF_Init()
// 描述: 初始化串口接收相关参数或设置
// 参数: 无
// 返回: 无
// 说明：此函数主要初始化串口设置参数
// 版本: V1.0, 2020.03.09
//========================================================================
void UART_BUF_Init()
{
    RX1_len = 0;
    memset(RX1_Buffer, 0, sizeof(RX1_Buffer));
}
//========================================================================
// 函数: void memcat(unsigned char *dest, const unsigned char *src,unsigned int index,len)
// 描述: 字符数组拼接函数
// 参数: dest目的字符数组,src源字符数组,index拼接位置,len拼接长度
// 返回: 无
// 说明：此函数主要初始化串口设置参数
// 版本: V1.0, 2020.03.09
//========================================================================
void memcat(unsigned char *dest, const unsigned char *src,unsigned int index, len)
{
    unsigned int i=0;
    if(index<0){ return;}
    for (i = index;  i< len+index; i++) {
        dest[i]=src[i-index];
    }
}
//========================================================================
// 函数: unsigned char Uart_Pretreatment()
// 描述: 数据接收预处理函数
// 参数: 无
// 返回: 无
// 说明：此函数主要处理，接收字符串，并校验字符串
// 版本: V1.0, 2020.03.09
//========================================================================
unsigned char Uart_Pretreatment()
{
    //Check_protocol_flag表示接收数据是否有效标记位
    unsigned char Check_protocol_flag = 0;
		if(RX1_len > 0 && !B_TX1_Busy && RX1_Buffer[0]==0xFF){
				if(RX1_len>2)
				{
							if(RX1_Buffer[1]==0xFF){
									if(RX1_len>(MinOrder+5)){UART_BUF_Init();}	
									if(RX1_len>=MinOrder && (RX1_Buffer[2]*16*16+RX1_Buffer[3]+4)==RX1_len){
											Check_protocol_flag = Check_Protocol(RX1_Buffer, RX1_len);
											if(!Check_protocol_flag){UART_BUF_Init();}
									}
							}
							else{
									UART_BUF_Init();
							}
				}
		}else{
				UART_BUF_Init();
		}
    return Check_protocol_flag;
}

//========================================================================
// 函数: unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len)
// 描述: 计算校验和
// 参数: *Buf:字符数组,Buf_len:数组实际长度
// 返回: 无
// 说明：无
// 版本: V1.0, 2020.03.09
//========================================================================
unsigned char Calculate_Checksum(unsigned char *Buf, unsigned int Buf_len)
{
    unsigned char checksum = 0x00;
    unsigned int i = 0, len = Buf_len;
    for(i = 2; i < (len - 1); i++) {
        checksum = checksum + Buf[i];
    }
    checksum = checksum % 256;
    return checksum;
}

//========================================================================
// 函数: unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len)
// 描述: 检验校验和是否一致
// 参数: *Buf:字符数组,Buf_len:数组实际长度
// 返回: 无
// 说明：具体思想为：接收到的BUF，取校验和，计算新的校验和，对比是否一致，若不一致，则数据无效
// 版本: V1.0, 2020.03.09
//========================================================================
unsigned char Check_Protocol(unsigned char *Buf, unsigned int Buf_len)
{
    unsigned char Check_protocol_flag = 0;
    //将原BUF的校验和提取
    unsigned char old_checksum = 0xFF;
    unsigned char new_checksum = 0x00;
		if(Buf_len>0){old_checksum = Buf[Buf_len - 1];}
    //计算新的校验和并赋值给new_checksum
    new_checksum = Calculate_Checksum(Buf, Buf_len);
    //比较原校验和与新校验和是否一致
    if(new_checksum == old_checksum) {
        Check_protocol_flag = 1;
    }
    return Check_protocol_flag;
}

//========================================================================
// 函数: void Data_Encapsulation(unsigned int Buf_len,unsigned char order,sn,action)
// 描述: 根据需要，打包数据并发送
// 参数: *Buf:字符数组,Buf_len:数组实际长度
// 返回: 无
// 说明：无
// 版本: V1.0, 2020.03.09
//========================================================================
void Data_Encapsulation(unsigned int Buf_len, unsigned char order, action)
{
		unsigned char Buf[116]={0};
		memcpy(Buf,PublicAgreement,sizeof(PublicAgreement));
		Buf[3] = Buf_len-4;
		Buf[4] = order;
    Buf[5] = Sn;
		//上传设备信息
		if(order==0x02){
				memcat(Buf,SerialProVersion,8,sizeof(SerialProVersion));
				memcat(Buf,BusinessProVersion,16,sizeof(BusinessProVersion));
				memcat(Buf,HardVersion,24,sizeof(HardVersion));
				memcat(Buf,SoftVersion,32,sizeof(SoftVersion));
				memcat(Buf,ProductKey,40,sizeof(ProductKey));
				memcat(Buf,DeviceAttributes,74,sizeof(DeviceAttributes));
				memcat(Buf,ProductSecert,82,sizeof(ProductSecert));
		}
		//接收非法数据包
		if(order==0x12){Buf[8] = action;}
		//上传设备状态
		if((order==0x04&&action==0x03)||(order==0x05&&action==0x04)){
				Buf[8] = action;
				Buf[9] = (P1 >> 4 & 0X0F);
				Buf[10] = 1;
				Buf[11] = 0x00;
				Buf[12] = 0x00;
		}
    //计算校验和
    Buf[Buf_len - 1] = Calculate_Checksum(Buf, Buf_len);
    //串口1回复数据
    SendString1(Buf, Buf_len);
}
//========================================================================
// 函数: void IsConnect_wifi()
// 描述: 判断是否接收到心跳包，如果没有接收到表示，连接wifi失败
// 参数: *Buf:字符数组,Buf_len:数组实际长度
// 返回: 无
// 说明：无
// 版本: V1.0, 2020.03.09
//========================================================================
void IsConnect_wifi()
{
    if((Wifi_flag == 1) && (Timer0_Count == 0)) {
        TR0 = 1;
    }
    //超过一分钟还未收到心跳包，即单片机与wifi模块失去联系
    if(Timer0_Count >= 12000) {
        TR0 = 0;
        Timer0_Count = 0;
        Wifi_flag = 0x00;
        Net_flag = 0;
        Phone_flag = 0;
        OLED_CLS_Local(0, 2, X_WIDTH, Y_WIDTH);
        OLED_P6x8Str(36, 4, "Wifi loss!");
    }
}
