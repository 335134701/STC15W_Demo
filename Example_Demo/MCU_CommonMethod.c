#include "MCU_CommonMethod.h"

//========================================================================
// ����: void Delay_ms(unsigned int time)
// ����: �����ʱ����
// ����: time:��ʱʱ��
// ����: ��
// ˵������Ƭ��Ƶ�ʲ�ͬ����ʱЧ����ͬ
// �汾: V1.0, 2020.03.09
//========================================================================
void Delay_ms(unsigned int time)
{
    unsigned int x, y;
    for(x = time; x > 0; x--)
        for(y = 110; y > 0; y--);
}
//========================================================================
// ����: void UART_BUF_Init()
// ����: ��ʼ�����ڽ�����ز���������
// ����: ��
// ����: ��
// ˵�����˺�����Ҫ��ʼ���������ò���
// �汾: V1.0, 2020.03.09
//========================================================================
void UART_BUF_Init()
{
    RX1_len = 0;
    memset(RX1_Buffer, 0, sizeof(RX1_Buffer));
}
//========================================================================
// ����: unsigned char Uart_Pretreatment()
// ����: ���ݽ���Ԥ������
// ����: ��
// ����: ��
// ˵�����˺�����Ҫ���������ַ�������У���ַ���
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned char Uart_Pretreatment()
{
    //Check_protocol_flag��ʾ���������Ƿ���Ч���λ
    unsigned char Check_protocol_flag = 0;
		if((RX1_len > 0) && !B_TX1_Busy) {
				if( RX1_Buffer[0]==0xFF || RX1_Buffer[1]==0xFF )
				{
						if(RX1_len>(MinOrder+5)){UART_BUF_Init();}	
						if(RX1_len>=MinOrder && (HexToInt(RX1_Buffer[2])*pow(16,2)+HexToInt(RX1_Buffer[3])+4)==RX1_len){
								Check_protocol_flag = Check_Protocol(RX1_Buffer, RX1_len);
						}	
				}else{
						UART_BUF_Init();
				}
    }else{
				UART_BUF_Init();
		}
    return Check_protocol_flag;
}

//========================================================================
// ����: unsigned char Calculate_Checksum(unsigned char *Buf,unsigned int Buf_len)
// ����: ����У���
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
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
// ����: unsigned char Check_Protocol(unsigned char *Buf,unsigned int Buf_len)
// ����: ����У����Ƿ�һ��
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵��������˼��Ϊ�����յ���BUF��ȡУ��ͣ������µ�У��ͣ��Ա��Ƿ�һ�£�����һ�£���������Ч
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned char Check_Protocol(unsigned char *Buf, unsigned int Buf_len)
{
    unsigned char Check_protocol_flag = 0;
    //��ԭBUF��У�����ȡ
    unsigned char old_checksum = 0xFF;
    unsigned char new_checksum = 0x00;
		if(Buf_len>0){old_checksum = Buf[Buf_len - 1];}
    //�����µ�У��Ͳ���ֵ��new_checksum
    new_checksum = Calculate_Checksum(Buf, Buf_len);
    //�Ƚ�ԭУ�������У����Ƿ�һ��
    if(new_checksum == old_checksum) {
        Check_protocol_flag = 1;
    }
    return Check_protocol_flag;
}

//========================================================================
// ����: void Data_Encapsulation(unsigned int Buf_len,unsigned char order,sn,action)
// ����: ������Ҫ��������ݲ�����
// ����: *Buf:�ַ�����,Buf_len:����ʵ�ʳ���
// ����: ��
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
void Data_Encapsulation(unsigned int Buf_len, unsigned char order, sn, action)
{
		unsigned char *Buf;
    //�ж��Ƿ�ѯ�ʲ�Ʒ��Ϣ
    if(Buf_len != sizeof(Device_information)) {
				Buf=(unsigned char*)calloc(Buf_len,sizeof(unsigned char));
				memset(Buf, 0, sizeof(Buf));
				Buf[0]=0xFF;Buf[1]=0xFF;
        switch(Buf_len) {
        case 9:
            Buf[3] = 0x05;
            break;
        case 10:
            Buf[3] = 0x06;
            break;
        case 11:
            Buf[3] = 0x07;
            break;
        case 12:
            Buf[3] = 0x08;
            break;
        case 14:
            Buf[3] = 0x0A;
            Buf[9] = (P1 >> 4 & 0X0F);
            Buf[10] = 1;
            Buf[11] = 0x00;
            Buf[12] = 0x00;
            break;
        }
        Buf[4] = order;
        Buf[5] = sn;
        if(Buf_len != 9) {
            Buf[8] = action;
        }
    }
    //����У���
    Buf[Buf_len - 1] = Calculate_Checksum(Buf, Buf_len);
    //����1�ظ�����
    SendString1(Buf, Buf_len);
}
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
    if((Wifi_flag == 1) && (Timer0_Count == 0)) {
        TR0 = 1;
    }
    //����һ���ӻ�δ�յ�������������Ƭ����wifiģ��ʧȥ��ϵ
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
//========================================================================
// ����: void HexToInt(unsigned char Buf)
// ����: ʮ����תʮ����
// ����: Buf:ʮ�����ַ�
// ����: ʮ������
// ˵������
// �汾: V1.0, 2020.03.09
//========================================================================
unsigned int HexToInt(unsigned char Buf)
{
    unsigned char Nibble[2]={0};
    unsigned int tmp=0;
    Nibble[0] = Buf & 0x0F;
    Nibble[1] = Buf >> 4 & 0X0F;
    tmp = Nibble[0]*pow(16,0);
    tmp = tmp+Nibble[1]*pow(16,1);
    return tmp;
}
