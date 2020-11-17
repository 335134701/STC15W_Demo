#include "MCU_OLED_Show.h"

//========================================================================
// ����: void MCU_OLED_StatusChange(unsigned char flag)
// ����: �ֻ����Ӻ�MCU����ģ��״̬��ʾ
// ����: flag:�������λ�����ݲ������ţ�����OLED״̬��ʾ
// ����: ��
// ˵��:
// �汾: V1.0, 2020.03.09
//========================================================================
void MCU_OLED_StatusChange(unsigned char flag)
{
    if(Phone_flag) {
        if(flag == 0x00) {
            OLED_CLS_Local(0, 4, X_WIDTH, Y_WIDTH);
            OLED_P6x8Str(6, 4, "L1:0 L2:0 L3:0 L4:0");
        }
        if(flag == 0x01 || flag == 0x00) {
            if(P14 == 0x01) {
                OLED_P6x8Str(24, 4, "1");
            } else {
                OLED_P6x8Str(24, 4, "0");
            }
        }
        if(flag == 0x02 || flag == 0x00) {
            if(P15 == 0x01) {
                OLED_P6x8Str(54, 4, "1");
            } else {
                OLED_P6x8Str(54, 4, "0");
            }
        }
        if(flag == 0x04 || flag == 0x00) {
            if(P16 == 0x01) {
                OLED_P6x8Str(84, 4, "1");
            } else {
                OLED_P6x8Str(84, 4, "0");
            }
        }
        if(flag == 0x08 || flag == 0x00) {
            if(P17 == 0x01) {
                OLED_P6x8Str(114, 4, "1");
            } else {
                OLED_P6x8Str(114, 4, "0");
            }
        }
    } else {
        OLED_CLS_Local(0, 4, X_WIDTH, 6);
    }
}


//========================================================================
// ����: void MCU_OLED_MessageShow(unsigned char Order,unsigned char Wifi_status_1,unsigned char Wifi_status_2)
// ����: ϵͳOLED��ʾ����,��Ҫ��ʾWiFi����״̬
// ����: Order:WiFi����״̬����;Wifi_status_1,Wifi_status_2:WiFi״̬���λ
// ����: ��
// ˵��:
// �汾: V1.0, 2020.03.09
//========================================================================
void MCU_OLED_MessageShow(unsigned char Order, unsigned char Wifi_status_1, unsigned char Wifi_status_2)
{
    //����wifi״̬
    if(Order == 0x0d) {
        //��������м�����������
        OLED_CLS_Local(0, 2, X_WIDTH, 4);
        switch(Wifi_status_2) {
        //SoftAPģʽ����
        case 0x01:
            OLED_P6x8Str(6, 2, "M:A");
            break;
        //Stationģʽ����
        case 0x02:
            OLED_P6x8Str(6, 2, "M:S");
            break;
        //SoftAPģʽ��������������ģʽ,����ʹ��SoftAP
        case 0x05:
            OLED_P6x8Str(6, 2, "M:A C:S");
            break;
        //Stationģʽ��������������ģʽ,����ʹ��AirLink
        case 0x06:
            OLED_P6x8Str(6, 2, "M:S C:A");
            break;
        //Stationģʽ�������ɹ�����·����
        case 0x12:
            OLED_P6x8Str(6, 2, "M:S C:A W:1");
            break;
        //Stationģʽ�������ɹ�����·������������ģʽ
        case 0x1A:
            OLED_P6x8Str(6, 2, "M:S C:A W:1");
            break;
        //Stationģʽ�������ɹ�����·������������ģʽ���������ƶ�
        case 0x3A:
            //Stationģʽ�������ɹ�����·������������ģʽ���������ƶˣ����ֻ�����
            if(Wifi_status_1 >= 0x00 && Wifi_status_1 <= 0x07 ) {
                OLED_P6x8Str(6, 2, "M:S C:A W:1 N:1");
            }
            //Stationģʽ�������ɹ�����·������������ģʽ���������ƶˣ����ֻ�����
            if(Wifi_status_1 >= 0x08 && Wifi_status_1 <= 0x0F ) {
                OLED_P6x8Str(6, 2, "M:S C:A W:1 N:1 P:1");
            }
            break;
        }
    }
}