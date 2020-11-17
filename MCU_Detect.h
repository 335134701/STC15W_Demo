#ifndef __MCU_DETECT_H__
#define __MCU_DETECT_H__


#include "MCU_Config.h"
#include "MCU_Method.h"
#include "MCU_Variable.h"


extern void Dect_Init();
//单片机按键检测程序
extern unsigned char Detect_Key(void);

#endif