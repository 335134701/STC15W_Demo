#include "MCU_Hand_Uart.h"

unsigned char ConfigWifiMode = 0x00;

//========================================================================
// ����: unsigned char Uart_Prereception_Layer()
// ����: ���ݽ���Ԥ������
// ����: ��
// ����: ��
// ˵�����˺�����Ҫ���������ַ�������У���ַ���
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned char Uart_Prereception_Layer()
{
    //Check_protocol_flag��ʾ���������Ƿ���Ч���λ
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
// ����: void Uart_Transmission_Layer(unsigned int Buf_len,unsigned char order,sn,action)
// ����: �������ݷ��ʹ�����
// ����: Buf_len:��������ʵ�ʳ���;order:Э��������;action:Э��action���
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void Uart_Transmission_Layer(unsigned int Buf_len, unsigned char order, action)
{
    unsigned char Buf[116] = {0};
    memcpy(Buf, PublicAgreement, sizeof(PublicAgreement));
    Buf[3] = Buf_len - 4;
    Buf[4] = order;
    Buf[5] = Sn;
    //�ϴ��豸��Ϣ
    if(order == 0x02) {
        memcat(Buf, SerialProVersion, 8, sizeof(SerialProVersion));
        memcat(Buf, BusinessProVersion, 16, sizeof(BusinessProVersion));
        memcat(Buf, HardVersion, 24, sizeof(HardVersion));
        memcat(Buf, SoftVersion, 32, sizeof(SoftVersion));
        memcat(Buf, ProductKey, 40, sizeof(ProductKey));
        memcat(Buf, DeviceAttributes, 74, sizeof(DeviceAttributes));
        memcat(Buf, ProductSecert, 82, sizeof(ProductSecert));
    }
    //���շǷ����ݰ�
    if(order == 0x12) {
        Buf[8] = action;
    }
    //�ϴ��豸״̬
    if((order == 0x04 && action == 0x03) || (order == 0x05 && action == 0x04)) {
        Buf[8] = action;
        Buf[9] = P1 >> 4 & 0X0F;
        Buf[10] = 0;
        Buf[11] = 0x00;
        Buf[12] = 0x00;
    }
    //����У���
    Buf[Buf_len - 1] = Calculate_Checksum(Buf, Buf_len);
    //����1�ظ�����
    SendString1(Buf, Buf_len);
}
/*
void Uart_Transmission_Layer(unsigned int Buf_len, unsigned char order, action)
{
    unsigned char Buf[116] = {0};
		unsigned char *tmp=NULL;
    memcpy(Buf, PublicAgreement, sizeof(PublicAgreement));
		tmp=Buf+sizeof(PublicAgreement);
    Buf[3] = Buf_len - 4;
    Buf[4] = order;
    Buf[5] = Sn;
    //�ϴ��豸��Ϣ
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
    //���շǷ����ݰ�
    if(order == 0x12) {
        Buf[8] = action;
    }
    //�ϴ��豸״̬
    if((order == 0x04 && action == 0x03) || (order == 0x05 && action == 0x04)) {
        Buf[8] = action;
        Buf[9] = P1 >> 4 & 0X0F;
        Buf[10] = 0;
        Buf[11] = 0x00;
        Buf[12] = 0x00;
    }
    //����У���
    Buf[Buf_len - 1] = Calculate_Checksum(Buf, Buf_len);
    //����1�ظ�����
    SendString1(Buf, Buf_len);
}
*/
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
    //˵��wifiģ���Ѿ����ӳɹ���������ʱ��
    if((Wifi_flag == 1) && (Timer0_Count == 0)) {
        TR0 = 1;
    }
    //���������ӻ�δ�յ�������������Ƭ����wifiģ��ʧȥ��ϵ
    //��ʱ����ʱ��Ϊ5ms
    if(Timer0_Count >= 36000) {
        TR0 = 0;        		//��ʱ��0 ��ʼ���ر�
        Timer0_Count = 0;   //��ʱ��0����λ
        Wifi_flag = 0x00;   //wifi����ģ����λ��ʼ��
        Net_flag = 0;       //������λ��ʼ��
        Phone_flag = 0;     //�ֻ����ӱ��λ��ʼ��
        OLED_CLS_Local(0, 2, X_WIDTH, Y_WIDTH);
        OLED_P6x8Str(36, 4, "Wifi loss!");
    }
}

//========================================================================
// ����: void UART_Send_Servvice_Layer()
// ����: UART1����ҵ������
// ����: ��
// ����: ��
// �汾: V1.0, 2020.04.24
//========================================================================
void UART_Send_Servvice_Layer()
{
    if(Set_soft_flag == 0 || Set_AP_flag == 0 || Reset_message_flag == 0 || Bindable_wifi_flag == 0 || Restart_wifi_flag == 0) {
        Delay_ms(10);
        OLED_CLS_Local(0, 2, X_WIDTH, Y_WIDTH);
        if(Sn != 0x00) {
            Sn = Sn + 0x01;
        }
        //  ����WiFiģʽ(Softģʽ)
        if(Set_soft_flag == 0) {
            ConfigWifiMode = 0x01;
            Uart_Transmission_Layer(10, 0x09, ConfigWifiMode);
        }
        //  ����WiFiģʽ(APģʽ)
        if(Set_AP_flag == 0)        {
            ConfigWifiMode = 0x02;
           Uart_Transmission_Layer(10, 0x09, ConfigWifiMode);
        }
        //  ����WiFi��Ϣ
        if(Reset_message_flag == 0) {
           Uart_Transmission_Layer(9, 0x0b, 0x00);
        }
        //  WiFi����ɰ�ģʽ
        if(Bindable_wifi_flag == 0) {
           Uart_Transmission_Layer(9, 0x15, 0x00);
        }
        //   ����WiFiģ��
        if(Restart_wifi_flag == 0)  {
           Uart_Transmission_Layer(9, 0x29, 0x00);
        }
        while(Set_soft_flag == 0 || Set_AP_flag == 0 || Reset_message_flag == 0 || Bindable_wifi_flag == 0 || Restart_wifi_flag == 0);
    }
	
}

//========================================================================
// ����: void UART_Receive_Service_Layer()
// ����: UART1����ҵ������
// ����: ��
// ����: ��
// �汾: V1.0, 2020.04.24
//========================================================================
void UART_Receive_Service_Layer()
{
	
	//У��������ݵĺϷ���
		if(Uart_Prereception_Layer()) {
				//��ȡ����Ų���ֵ��Sn
				Sn = RX1_Buffer[5];
				switch(RX1_Buffer[4]) {
				//WiFiģ���ȡ�豸��Ϣ
				case 0x01:
						Uart_Transmission_Layer(115, RX1_Buffer[4] + 1, 0x00);
						break;
				//WiFiģ������豸,��ȡ�豸�ĵ�ǰ״̬
				case 0x03:
						//WiFiģ �� �� �� �� ��
						if(RX1_Buffer[8] == 0x01) {
								//�յ����ݺ�mcu�����豸����
								MCU_Application_Control(RX1_Buffer);
								Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
								//MCU�����ϱ���ǰ״̬
								Sn = Sn + 0x01;
								Uart_Transmission_Layer(14, RX1_Buffer[4] + 2, 0x04);
								MCU_OLED_StatusChange(RX1_Buffer[9]);
						}
						// WiFiģ �� �� ȡ �� �� �� �� ǰ ״ ̬
						if(RX1_Buffer[8] == 0x02) {
								Uart_Transmission_Layer(14, RX1_Buffer[4] + 1, RX1_Buffer[8] + 1);
						}
						break;
				//MCU�����ϱ���ǰ״̬WIFIģ��ظ�
				case 0x06:
						break;
				//WiFiģ����MCU��������
				case 0x07:
						Wifi_flag = 0x01;
						//�رն�ʱ��������������0
						TR0 = 0;
						Timer0_Count = 0;
						Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
						//�򿪶�ʱ��
						TR0 = 1;
						break;
				//֪ͨWIFIģ���������ģʽ�����WIFIģ��ظ�
				case 0x0a:
						if(ConfigWifiMode == 0x01) {
								OLED_P6x8Str(2, 2, "Configure Wifi:Soft");
						} else {
								OLED_P6x8Str(2, 2, "Configure Wifi:AP");
						}
						break;
				//����WiFiģ������WIFIģ��ظ�
				case 0x0c:
						OLED_P6x8Str(2, 2, "Reset Wifi!");
						break;
				//WiFiģ����MCU����WiFi״̬
				case 0x0d:
						//���ֻ����ӱ�־λ���������ӱ�־λ��ʼ��
						Phone_flag = 0;
						Net_flag = 0;
						Wifi_flag = 0x01;
						//չʾWiFi������Ϣ
						MCU_WIFI_MessageShow(RX1_Buffer[4], RX1_Buffer[8], RX1_Buffer[9]);
						if(RX1_Buffer[8] >= 0x00 && RX1_Buffer[8] <= 0x07 ) Net_flag = 1;
						if(RX1_Buffer[8] >= 0x08 && RX1_Buffer[8] <= 0x0F ) {
								Net_flag = 1;
								Phone_flag = 1;
						}
						//������ֻ����� չʾ��Ʒ������Ϣ
						MCU_OLED_StatusChange(0x00);
						Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
						break;
				case 0x0f:
						Uart_Transmission_Layer(9, RX1_Buffer[4] + 1, 0x00);
						break;
				//WiFiģ��Ƿ����ݰ�֪ͨ
				case 0x11:
						Uart_Transmission_Layer(10, RX1_Buffer[4] + 1, RX1_Buffer[8]);
						break;
				//MCU����WiFi����ɰ�ģʽ��WiFiģ��ظ�
				case 0x16:
						OLED_P6x8Str(2, 2, "Enter bindable mode!");
						break;
				//MCU�����ȡ����ʱ�䣬WiFiģ��ظ�
				case 0x18:
						break;
				//MCU����WiFi������WiFiģ��ظ�
				case 0x2a:
						OLED_P6x8Str(2, 2, "Restart Wifi!");
						break;
				}
				UART_BUF_Init();
		}
		
}