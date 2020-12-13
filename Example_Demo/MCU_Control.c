#include "MCU_Control.h"


//========================================================================
// 函数: void MCU_Application_Control(unsigned char* Buf)
// 描述: MCU控制处理函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2020.04.24
//========================================================================
void MCU_Application_Control(unsigned char* Buf)
{

    switch(Buf[9]) {
    case 0x01:
        if(Buf[10] == 0x01) {
            P14 = 1;
        } else {
            P14 = 0;
        }
        break;
    case 0x02:
        if(Buf[10] == 0x02) {
            P15 = 1;
        } else {
            P15 = 0;
        }
        break;
    case 0x04:
        if(Buf[10] == 0x04) {
            P16 = 1;
        } else {
            P16 = 0;
        }
        break;
    case 0x08:
        if(Buf[10] == 0x08) {
            P17 = 1;
        } else {
            P17 = 0;
        }
        break;
    }
}
