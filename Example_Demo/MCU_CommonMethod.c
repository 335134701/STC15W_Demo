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
// ����: void memcat(unsigned char *dest, const unsigned char *src,unsigned int index,len)
// ����: �ַ�����ƴ�Ӻ���
// ����: destĿ���ַ�����,srcԴ�ַ�����,indexƴ��λ��,lenƴ�ӳ���
// ����: ��
// ˵�����˺�����Ҫ��ʼ���������ò���
// �汾: V1.0, 2020.03.09
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


