#include	"MCU_Config.h"

/******************** Èí¼þÑÓÊ±º¯Êý **************************/
void Delay_ms(u16 time)
{
	u16 x,y;
	for(x=time;x>0;x--)
		for(y=110;y>0;y--);
}