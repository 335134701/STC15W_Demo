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
