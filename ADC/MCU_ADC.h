#ifndef __MCU_ADC_H__
#define __MCU_ADC_H__


extern void ADC_Init(void);
extern u16	Get_ADC10bitResult(u8 channel);
extern void Int_cov_Str(u8 *buf,u16 buf_len,u16 num);
#endif