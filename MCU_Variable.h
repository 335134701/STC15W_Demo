#ifndef __MCU_VARIABLE_H__
#define __MCU_VARIABLE_H__

//wifiģ���Ƿ����ӱ��λ
extern unsigned char Wifi_flag;
//�ֻ������źű��λ
extern unsigned char Phone_flag;
//���������źű��λ
extern unsigned char Net_flag;
//���մ���������С���λ����
extern unsigned int MinOrder;
//���ݰ����
extern unsigned char Sn;
//========================================================================
// ����: �豸��Ϣ���
// ����: ��������Э��(8),
//			 ͨ�ô���Э��汾��(8),
//			 ҵ��Э��汾��(8)
//			 Ӳ���汾��(8)
//			 ����汾��(8)
//			 ��Ʒ��ʾ��(32)
//			 �ɰ�״̬ʧЧʱ��(2)
//			 �豸����(8)
//			 ��Ʒ��Կ(32)
//			 У���(1)
// �汾: V1.0, 2020.12.02
//========================================================================
//Ӳ���汾��
extern const unsigned char code  HardVersion[8];
//����汾��
extern const unsigned char code SoftVersion[8];
//��Ʒ��ʶ��
extern const unsigned char xdata ProductKey[32];
//��Ʒ��Կ
extern const unsigned char xdata ProductSecert[32];
//�豸����
extern const unsigned char code	DeviceAttributes[8];
//����Э��汾��
extern const unsigned char code SerialProVersion[8];
//ҵ��Э��汾��
extern const unsigned char code BusinessProVersion[8];
//��������Э��
extern const unsigned char PublicAgreement[9];

#endif