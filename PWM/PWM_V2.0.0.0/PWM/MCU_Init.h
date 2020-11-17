#ifndef	__MCU_INIT_H
#define	__MCU_INIT_H

//========================================================================
/*************	GPIO Set定义常量	**************/
#define	GPIO_PullUp		0	//上拉准双向口
#define	GPIO_HighZ		1	//浮空输入
#define	GPIO_OUT_OD		2	//开漏输出
#define	GPIO_OUT_PP		3	//推挽输出

#define	GPIO_Pin_0		0x01	//IO引脚 Px.0
#define	GPIO_Pin_1		0x02	//IO引脚 Px.1
#define	GPIO_Pin_2		0x04	//IO引脚 Px.2
#define	GPIO_Pin_3		0x08	//IO引脚 Px.3
#define	GPIO_Pin_4		0x10	//IO引脚 Px.4
#define	GPIO_Pin_5		0x20	//IO引脚 Px.5
#define	GPIO_Pin_6		0x40	//IO引脚 Px.6
#define	GPIO_Pin_7		0x80	//IO引脚 Px.7
#define	GPIO_Pin_All	0xFF	//IO所有引脚
	
#define	GPIO_P0			0		//IO引脚 P0
#define	GPIO_P1			1		//IO引脚 P1
#define	GPIO_P2			2		//IO引脚 P2
#define	GPIO_P3			3		//IO引脚 P3
#define	GPIO_P4			4		//IO引脚 P4
#define	GPIO_P5			5		//IO引脚 P5

/*************	GPIO Set定义结构体	**************/
typedef struct
{
	u8	Mode;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	u8	Pin;		//要设置的引脚	
} GPIO_InitTypeDef;


//========================================================================

extern void MCU_Init(void);
extern void GPIO_Init(void);
extern void	GPIO_Config(void);

#endif