#include "MCU_Hand_Uart.h"

unsigned char ConfigWifiMode = 0x00;

//========================================================================
// 函数: unsigned char Uart_Prereception_Layer()
// 描述: 数据接收预处理函数
// 参数: 无
// 返回: 无
// 说明：此函数主要处理，接收字符串，并校验字符串
// 版本: V1.0, 2020.03.09
//========================================================================
unsigned char Uart_Prereception_Layer()
{
    //Check_protocol_flag表示接收数据是否有效标记位
    unsigned char Check_protocol_flag = 0;
    if(RX1_len > 0 && !B_TX1_Busy && RX1_Buffer[0] == 0xFF) {
        if(RX1_len > 2) {
            if(RX1_Buffer[1] == 0xFF) {
                if(RX1_len > (MinOrder + 5)) {
                    UART_BUF_Init();
                }
                if((RX1_Buffer[2] * 16 * 16 + RX1_Buffer[3] + 4) == RX1_len) {
                    Check_protocol_flag = Check_Protocol(RX1_Buffer, RX1_len);
                    if(!Check_protocol_flag) {
                        UART_BUF_Init();
                    }
                }
            } else {
                UART_BUF_Init();
            }
        }
    } else {
        UART_BUF_Init();
    }
    return Check_protocol_flag;
}

//========================================================================
// 函数: void Uart_Transmission_Layer(unsigned int Buf_len,unsigned char order,sn,action)
// 描述: 串口数据发送处理函数
// 参数: Buf_len:发送数组实际长度;order:协议命令标记;action:协议action标记
// 返回: 无
// 说明：无
// 版本: V1.0, 2020.03.09
//========================================================================
void Uart_Transmission_Layer(unsigned int Buf_len, unsigned char order, action)
{
    unsigned char Buf[116] = {0};
		unsigned char *tmp=NULL;
		if(Buf_len<MinOrder){return;}
    memcpy(Buf, PublicAgreement, sizeof(PublicAgreement));
		tmp=Buf+sizeof(PublicAgreement)-1;
    Buf[3] = Buf_len - 4;
    Buf[4] = order;
    Buf[5] = Sn;
		Buf[8] = action;
    //上传设备信息
    if(order == 0x02) {
				memcpy(tmp,SerialProVersion,sizeof(SerialProVersion));
				tmp=tmp+sizeof(SerialProVersion);
				memcpy(tmp,BusinessProVersion,sizeof(BusinessProVersion));
				tmp=tmp+sizeof(BusinessProVersion);
				memcpy(tmp,HardVersion,sizeof(HardVersion));
				tmp=tmp+sizeof(HardVersion);
				memcpy(tmp,SoftVersion,sizeof(SoftVersion));
				tmp=tmp+sizeof(SoftVersion);
				memcpy(tmp,ProductKey,sizeof(ProductKey));
				tmp=tmp+sizeof(ProductKey)+2;
				memcpy(tmp,DeviceAttributes,sizeof(DeviceAttributes));
				tmp=tmp+sizeof(DeviceAttributes);
				memcpy(tmp,ProductSecert,sizeof(ProductSecert));
    }
    //上传设备状态
    if((order == 0x04 && action == 0x03) || (order == 0x05 && action == 0x04)) {
        Buf[9] = P1 >> 4 & 0X0F;
        Buf[10] = 0;
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
    //说明wifi模块已经连接成功，开启定时器
    if((Wifi_flag == 1) && (Timer0_Count == 0)) {
        TR0 = 1;
    }
    //超过三分钟还未收到心跳包，即单片机与wifi模块失去联系
    //定时器的时间为5ms
    if(Timer0_Count >= 36000) {
        TR0 = 0;        		//定时器0 初始化关闭
        Timer0_Count = 0;   //定时器0计数位
        Wifi_flag = 0x00;   //wifi连接模块标记位初始化
        Net_flag = 0;       //网络标记位初始化
        Phone_flag = 0;     //手机连接标记位初始化
        OLED_CLS_Local(0, 2, X_WIDTH, Y_WIDTH);
        OLED_P6x8Str(36, 4, "Wifi loss!");
    }
}

//========================================================================
// 函数: void UART_Send_Servvice_Layer()
// 描述: UART1发送业务处理函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.04.24
//========================================================================
void UART_Send_Servvice_Layer()
{
    if(Set_soft_flag == 0 || Set_AP_flag == 0 || Reset_message_flag == 0 || Bindable_wifi_flag == 0 || Restart_wifi_flag == 0) {
        Delay_ms(10);
        OLED_CLS_Local(0, 2, X_WIDTH, Y_WIDTH);
        if(Sn != 0x00) {
            Sn = Sn + 0x01;
        }
        //  配置WiFi模式(Soft模式)
        if(Set_soft_flag == 0) {
            ConfigWifiMode = 0x01;
            Uart_Transmission_Layer(10, 0x09, ConfigWifiMode);
        }
        //  配置WiFi模式(AP模式)
        if(Set_AP_flag == 0)        {
            ConfigWifiMode = 0x02;
           Uart_Transmission_Layer(10, 0x09, ConfigWifiMode);
        }
        //  重置WiFi信息
        if(Reset_message_flag == 0) {
           Uart_Transmission_Layer(9, 0x0b, 0x00);
        }
        //  WiFi进入可绑定模式
        if(Bindable_wifi_flag == 0) {
           Uart_Transmission_Layer(9, 0x15, 0x00);
        }
        //   重启WiFi模组
        if(Restart_wifi_flag == 0)  {
           Uart_Transmission_Layer(9, 0x29, 0x00);
        }
        while(Set_soft_flag == 0 || Set_AP_flag == 0 || Reset_message_flag == 0 || Bindable_wifi_flag == 0 || Restart_wifi_flag == 0);
    }
	
}

//========================================================================
// 函数: void UART_Receive_Service_Layer()
// 描述: UART1接收业务处理函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.04.24
//========================================================================
void UART_Receive_Service_Layer()
{
	
	//校验接收数据的合法性
		if(Uart_Prereception_Layer()) {
				//获取包序号并赋值给Sn
				Sn = RX1_Buffer[5];
				switch(RX1_Buffer[4]) {
				//WiFi模组获取设备信息
				case 0x01:
						Uart_Transmission_Layer(115, RX1_Buffer[4] + 1, 0x00);
						break;
				//WiFi模组控制设备,读取设备的当前状态
				case 0x03:
						//WiFi模 组 控 制 设 备
						if(RX1_Buffer[8] == 0x01) {
								//收到数据后，mcu控制设备函数
								MCU_Application_Control(RX1_Buffer);
								Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
								//MCU主动上报当前状态
								Sn = Sn + 0x01;
								Uart_Transmission_Layer(14, RX1_Buffer[4] + 2, 0x04);
								MCU_OLED_StatusChange(RX1_Buffer[9]);
						}
						// WiFi模 组 读 取 设 备 的 当 前 状 态
						if(RX1_Buffer[8] == 0x02) {
								Uart_Transmission_Layer(14, RX1_Buffer[4] + 1, RX1_Buffer[8] + 1);
						}
						break;
				//MCU主动上报当前状态WIFI模组回复
				case 0x06:
						break;
				//WiFi模组向MCU发送心跳
				case 0x07:
						Wifi_flag = 0x01;
						//关闭定时器，将计数器置0
						TR0 = 0;
						Timer0_Count = 0;
						Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
						//打开定时器
						TR0 = 1;
						break;
				//通知WIFI模组进入配置模式后接收WIFI模组回复
				case 0x0a:
						if(ConfigWifiMode == 0x01) {
								OLED_P6x8Str(2, 2, "Configure Wifi:Soft");
						} else {
								OLED_P6x8Str(2, 2, "Configure Wifi:AP");
						}
						break;
				//重置WiFi模组后接收WIFI模组回复
				case 0x0c:
						OLED_P6x8Str(2, 2, "Reset Wifi!");
						break;
				//WiFi模组向MCU推送WiFi状态
				case 0x0d:
						//将手机连接标志位，网络连接标志位初始化
						Phone_flag = 0;
						Net_flag = 0;
						Wifi_flag = 0x01;
						//展示WiFi连接信息
						MCU_WIFI_MessageShow(RX1_Buffer[4], RX1_Buffer[8], RX1_Buffer[9]);
						if(RX1_Buffer[8] >= 0x00 && RX1_Buffer[8] <= 0x07 ) Net_flag = 1;
						if(RX1_Buffer[8] >= 0x08 && RX1_Buffer[8] <= 0x0F ) {
								Net_flag = 1;
								Phone_flag = 1;
						}
						//如果有手机连接 展示产品连接信息
						MCU_OLED_StatusChange(0x00);
						Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
						break;
				case 0x0f:
						Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
						break;
				//WiFi模组非法数据包通知
				case 0x11:
						Uart_Transmission_Layer(10, RX1_Buffer[4] + 1, RX1_Buffer[8]);
						break;
				//MCU请求WiFi进入可绑定模式，WiFi模组回复
				case 0x16:
						OLED_P6x8Str(2, 2, "Enter bindable mode!");
						break;
				//MCU请求获取网络时间，WiFi模组回复
				case 0x18:
						break;
				//MCU请求WiFi重启，WiFi模组回复
				case 0x2a:
						OLED_P6x8Str(2, 2, "Restart Wifi!");
						break;
				}
				UART_BUF_Init();
		}
		
}