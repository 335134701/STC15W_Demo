#include "MCU_Hand_Uart.h"

//数据包序号
unsigned char Sn=0x00;


//========================================================================
// 函数: void UART_Receive_Processing()
// 描述: UART1接收处理函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.04.24
//========================================================================
void UART_Receive_Processing()
{
	//判断是否是有效的处理命令标记位
	unsigned char Uart_Receive_flag=0;
	//校验接收数据是否正常
	Uart_Receive_flag=Uart_Pretreatment();
	if(Uart_Receive_flag)
	{
		Wifi_flag=0x01;
		//获取包序号并赋值给Sn
		Sn=RX1_Buffer[5];
		switch(RX1_Buffer[4])
		{
			//WiFi模组获取设备信息
			case 0x01:Data_Encapsulation(Device_information,sizeof(Device_information),0x00,Sn,0x00);break;
			//WiFi模组控制设备,读取设备的当前状态
			case 0x03:
				//WiFi模 组 控 制 设 备
				if(RX1_Buffer[8]==0x01)
				{
					//收到数据后，mcu控制设备函数
					MCU_Application_Control(RX1_Buffer);					
					Data_Encapsulation(Mcu_send,9,0x04,Sn,0x00);
					//MCU主动上报当前状态
					Sn=Sn+0x01;
					Data_Encapsulation(Mcu_send,14,0x05,Sn,0x04);
					MCU_OLED_StatusChange(RX1_Buffer[9]);
				}
				// WiFi模 组 读 取 设 备 的 当 前 状 态
				if(RX1_Buffer[8]==0x02){Data_Encapsulation(Mcu_send,14,0x04,Sn,0x03);}break;	
			//MCU主动上报当前状态WIFI模组回复
			case 0x06:	break;
			//WiFi模组向MCU发送心跳
			case 0x07:
					//关闭定时器，将计数器置0
					TR0=0;Timer0_Count=0;
					Data_Encapsulation(Mcu_send,9,0x08,Sn,0x00);
					//打开定时器
					TR0=1;					
				break;	
			//通知WIFI模组进入配置模式后接收WIFI模组回复
			case 0x0a:
				//OLED_CLS_Local(0,2,X_WIDTH,Y_WIDTH);
				//OLED_P6x8Str(2,2,"Enter Wifi Config!");
				break;
			//重置WiFi模组后接收WIFI模组回复
			case 0x0c:
				//OLED_CLS_Local(0,2,X_WIDTH,Y_WIDTH);
				//OLED_P6x8Str(2,2,"Wifi Reset Success!");
				break;
			//WiFi模组向MCU推送WiFi状态
			case 0x0d:
					MCU_OLED_MessageShow(RX1_Buffer[4],RX1_Buffer[8],RX1_Buffer[9]);
					if(Phone_flag){MCU_OLED_StatusChange(0x00);}
					Data_Encapsulation(Mcu_send,9,0x0e,Sn,0x00);
				break;
			case 0x0f:Data_Encapsulation(Mcu_send,9,0x10,Sn,0x00);break;
			//WiFi模组非法数据包通知
			case 0x11:Data_Encapsulation(Mcu_send,10,0x12,Sn,RX1_Buffer[8]);break;			
			//MCU请求WiFi进入可绑定模式，WiFi模组回复	
			case 0x16:
				break;		
			//MCU请求获取网络时间，WiFi模组回复	
			case 0x18:
				break;
			case 0x2a:
				//MCU请求WiFi重启，WiFi模组回复
				break;
			}
			RST_Uart_Timer();
	}	
}
//========================================================================
// 函数: void UART_Send_Processing()
// 描述: UART1发送处理函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.04.24
//========================================================================
void UART_Send_Processing()
{
	
	unsigned char flag=0;
	/**  配置WiFi模式(Soft模式)  **/
	if(Set_soft_flag==0)      {Delay_ms(10);  if(Set_soft_flag==0)	    {flag=0x01;} }
	/**  配置WiFi模式(AP模式)  **/
	if(Set_AP_flag==0)        {Delay_ms(10);  if(Set_AP_flag==0)	    	{flag=0x02;} }
	/**  重置WiFi信息  **/
	if(Reset_message_flag==0) {Delay_ms(10);  if(Reset_message_flag==0)	{flag=0x03;} }
	/**  WiFi进入可绑定模式  **/
	if(Bindable_wifi_flag==0) {Delay_ms(10);  if(Bindable_wifi_flag==0)	{flag=0x04;} }
	/**   重启WiFi模组   **/
	if(Restart_wifi_flag==0)  {Delay_ms(10);  if(Restart_wifi_flag==0)	{flag=0x05;} }
	if(flag!=0&&Wifi_flag==1)
	{
		REN=0;
		if(flag<=0x05){OLED_CLS_Local(0,2,X_WIDTH,Y_WIDTH);}
		Sn=Sn+0x01;
		switch(flag)
		{
			/**  配置WiFi模式(Soft模式)  **/
			case 0x01:
					OLED_P6x8Str(2,2,"Configure Wifi:Soft");
					Data_Encapsulation(Mcu_send,10,0x09,Sn,0x01);
				break;
			/**  配置WiFi模式(AP模式)  **/
			case 0x02:
					OLED_P6x8Str(2,2,"Configure Wifi:AP");
					Data_Encapsulation(Mcu_send,10,0x09,Sn,0x02);
				break;
			/**  重置WiFi信息  **/
			case 0x03:
					OLED_P6x8Str(2,2,"Reset Wifi!");
					Data_Encapsulation(Mcu_send,9,0x0b,Sn,0x00);
				break;
			/**  WiFi进入可绑定模式  **/
			case 0x04:
					OLED_P6x8Str(2,2,"Enter bindable mode!");
					Data_Encapsulation(Mcu_send,9,0x15,Sn,0x00);
				break;
			/**   重启WiFi模组   **/
			case 0x05:
					OLED_P6x8Str(2,2,"Restart Wifi!");
					Data_Encapsulation(Mcu_send,9,0x29,Sn,0x00);
				break;
		}
	}
	while(Set_soft_flag==0||Set_AP_flag==0||Reset_message_flag==0||Bindable_wifi_flag==0||Restart_wifi_flag==0);
	RST_Uart_Timer();
}