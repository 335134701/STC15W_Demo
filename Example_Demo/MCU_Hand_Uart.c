#include "MCU_Hand_Uart.h"

//========================================================================
// ����: void UART_Receive_Processing()
// ����: UART1���մ�����
// ����: ��
// ����: ��
// �汾: V1.0, 2020.04.24
//========================================================================
void UART_Receive_Processing()
{
    //У��������ݵĺϷ���
    if(Uart_Pretreatment()) {
        //��ȡ����Ų���ֵ��Sn
        Sn = RX1_Buffer[5];
        switch(RX1_Buffer[4]) {
        //WiFiģ���ȡ�豸��Ϣ
        case 0x01:
            Data_Encapsulation(115, RX1_Buffer[4]+1, 0x00);
            break;
        //WiFiģ������豸,��ȡ�豸�ĵ�ǰ״̬
        case 0x03:
            //WiFiģ �� �� �� �� ��
            if(RX1_Buffer[8] == 0x01) {
                //�յ����ݺ�mcu�����豸����
                //MCU_Application_Control(RX1_Buffer);
                Data_Encapsulation(9, RX1_Buffer[4]+1, 0x00);
                //MCU�����ϱ���ǰ״̬
                Sn = Sn + 0x01;
                Data_Encapsulation(14, RX1_Buffer[4]+2,0x04);
                MCU_OLED_StatusChange(RX1_Buffer[9]);
            }
            // WiFiģ �� �� ȡ �� �� �� �� ǰ ״ ̬
            if(RX1_Buffer[8] == 0x02) {
                Data_Encapsulation(14, RX1_Buffer[4]+1, 0x03);
            }
            break;
        //MCU�����ϱ���ǰ״̬WIFIģ��ظ�
        case 0x06:
            break;
        //WiFiģ����MCU��������
        case 0x07:
            //�رն�ʱ��������������0
            //TR0 = 0;Timer0_Count = 0;
            Data_Encapsulation(9, RX1_Buffer[4]+1,0x00);
            //�򿪶�ʱ��
            //TR0 = 1;
            break;
        //֪ͨWIFIģ���������ģʽ�����WIFIģ��ظ�
        case 0x0a:
            break;
        //����WiFiģ������WIFIģ��ظ�
        case 0x0c:
            break;
        //WiFiģ����MCU����WiFi״̬
        case 0x0d:
            //���ֻ����ӱ�־λ���������ӱ�־λ��ʼ��
            Phone_flag = 0;Net_flag = 0;
            //չʾWiFi������Ϣ
            MCU_WIFI_MessageShow(RX1_Buffer[4], RX1_Buffer[8], RX1_Buffer[9]);
            if(RX1_Buffer[8] >= 0x00 && RX1_Buffer[8] <= 0x07 ) Net_flag = 1;
            if(RX1_Buffer[8] >= 0x08 && RX1_Buffer[8] <= 0x0F ) { Net_flag = 1;Phone_flag = 1;}
            //������ֻ����� չʾ��Ʒ������Ϣ
            MCU_OLED_StatusChange(0x00);
            Data_Encapsulation(9, RX1_Buffer[4]+1,0x00);
            break;
        case 0x0f:
            Data_Encapsulation(9, RX1_Buffer[4]+1, 0x00);
            break;
        //WiFiģ��Ƿ����ݰ�֪ͨ
        case 0x11:
            Data_Encapsulation(10, RX1_Buffer[4]+1, RX1_Buffer[8]);
            break;
        //MCU����WiFi����ɰ�ģʽ��WiFiģ��ظ�
        case 0x16:
            break;
        //MCU�����ȡ����ʱ�䣬WiFiģ��ظ�
        case 0x18:
            break;
        case 0x2a:
            //MCU����WiFi������WiFiģ��ظ�
            break;
        }
        UART_BUF_Init();
    }
}
//========================================================================
// ����: void UART_Send_Processing()
// ����: UART1���ʹ�����
// ����: ��
// ����: ��
// �汾: V1.0, 2020.04.24
//========================================================================
void UART_Send_Processing()
{
    unsigned char flag = 0;
    //  ����WiFiģʽ(Softģʽ)  
    if(Set_soft_flag == 0)      {
        Delay_ms(10);
        if(Set_soft_flag == 0)	    {
            flag = 0x01;
        }
    }
    //  ����WiFiģʽ(APģʽ)  
    if(Set_AP_flag == 0)        {
        Delay_ms(10);
        if(Set_AP_flag == 0)	    	{
            flag = 0x02;
        }
    }
    //  ����WiFi��Ϣ  
    if(Reset_message_flag == 0) {
        Delay_ms(10);
        if(Reset_message_flag == 0)	{
            flag = 0x03;
        }
    }
    //  WiFi����ɰ�ģʽ 
    if(Bindable_wifi_flag == 0) {
        Delay_ms(10);
        if(Bindable_wifi_flag == 0)	{
            flag = 0x04;
        }
    }
    //   ����WiFiģ��   
    if(Restart_wifi_flag == 0)  {
        Delay_ms(10);
        if(Restart_wifi_flag == 0)	{
            flag = 0x05;
        }
    }
    if(flag != 0 && Wifi_flag == 1) {
        if(flag <= 0x05) {
            OLED_CLS_Local(0, 2, X_WIDTH, Y_WIDTH);
        }
        if(Sn != 0x00) {
            Sn = Sn + 0x01;
        }
        switch(flag) {
        //  ����WiFiģʽ(Softģʽ)  
        case 0x01:
            OLED_P6x8Str(2, 2, "Configure Wifi:Soft");
            Data_Encapsulation(10, 0x09,0x01);
            break;
        //  ����WiFiģʽ(APģʽ) 
        case 0x02:
            OLED_P6x8Str(2, 2, "Configure Wifi:AP");
            Data_Encapsulation(10, 0x09,0x02);
            break;
        //  ����WiFi��Ϣ 
        case 0x03:
            OLED_P6x8Str(2, 2, "Reset Wifi!");
            Data_Encapsulation(9, 0x0b, 0x00);
            break;
        //  WiFi����ɰ�ģʽ 
        case 0x04:
            OLED_P6x8Str(2, 2, "Enter bindable mode!");
            Data_Encapsulation(9, 0x15, 0x00);
            break;
        //   ����WiFiģ�� 
        case 0x05:
            OLED_P6x8Str(2, 2, "Restart Wifi!");
            Data_Encapsulation(9, 0x29,0x00);
            break;
        }
        while(Set_soft_flag == 0 || Set_AP_flag == 0 || Reset_message_flag == 0 || Bindable_wifi_flag == 0 || Restart_wifi_flag == 0);
    }
}