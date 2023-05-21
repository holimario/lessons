/*
 * OLED.H
 *
 *  Created on: Jan 2, 2014
 *      Author: millin
 */

#ifndef OLED_H_
#define OLED_H_

#ifndef _GLOBAL_DECL_
#define _GLOBAL_DECL_ extern
#endif

/******************************************/
/*****              OLED Define        ****/
/******************************************/

#define SSD1325			1		//另一个型号OLED，TW28642270B，2.7吋
#define SSD1306			2		//教学系统标配屏幕，型号OLED_UG2864HSWEG01，0.97吋

#define OLED_TYPE		SSD1306


/******************************************/
//相应标志位赋值与检测功能
/******************************************/
#define BIT0 0x01
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)
#define BIT8 (1<<8)
#define BIT9 (1<<9)
#define BIT10 (1<<10)
#define BIT11 (1<<11)
#define BIT12 (1<<12)
#define BIT13 (1<<13)
#define BIT14 (1<<14)
#define BIT15 (1<<15)
#define BIT16 (1<<16)
#define BIT17 (1<<17)
#define BIT18 (1<<18)
#define BIT19 (1<<19)
#define BIT20 (1<<20)
#define BIT21 (1<<21)
#define BIT22 (1<<22)
#define BIT23 (1<<23)
#define BIT24 (1<<24)
#define BIT25 (1<<25)
#define BIT26 (1<<26)
#define BIT27 (1<<27)
#define BIT28 (1<<28)
#define BIT29 (1<<29)
#define BIT30 (1<<30)
#define BIT31 (1<<31)

//请根据实际连接的引脚修改以下宏定义
#define OLED_DC_H     (GPIOD_PDOR|=BIT2)
#define OLED_RESET_H  (GPIOE_PDOR|=BIT31)

//请根据实际连接的引脚修改以下宏定义
#define OLED_DC_L     (GPIOD_PDOR&=~BIT2)
#define OLED_RESET_L  (GPIOE_PDOR&=~BIT31)


#define DDR_OLED_DC     (GPIOD_PDDR|=BIT2)
#define DDR_OLED_RESET  (GPIOE_PDDR|=BIT31)

//////////////////////////////////////////////////////

_GLOBAL_DECL_ const unsigned char ASCII[];

void OLED_Init(void);//系统初始化
void OLED_W_Ctl(unsigned char cw);
void OLED_W_Dat(unsigned char dw);
void OLED_Clr(void);
void OLED_W_Test(void);
void OLED_W_Ch(unsigned char lx,unsigned char ly,char ch);
void OLED_W_Str(unsigned char lx,unsigned char ly,char *sch);
void OLED_W_Dot(unsigned char lx,unsigned char ly,char val);
void Inintstate();//初始化state数组
void dot(unsigned char lx,unsigned char ly,char val);//以函数OLED_W_Dot和全局二维数组state为基础的单点操作函数，lx为范围从0到63的行坐标，ly为0到127的列坐标，val表示操作，1为点亮，0为熄灭




#endif /* OLED_H_ */
