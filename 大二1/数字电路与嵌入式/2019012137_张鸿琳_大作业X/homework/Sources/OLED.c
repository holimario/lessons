/*
 * OLED.C
 *
 *  Created on: Jan 2, 2014
 *      Author: millin
 */


#include "derivative.h" /* include peripheral declarations */
#include "OLED.H"

unsigned char state[128][8];//全局二维数组，存储目前的像素点是否点亮的信息，以8位为一组

void Inintstate(){//初始化state数组
	int i,j;
	for(i=0;i<=127;i++)
	{
		for(j=0;j<=7;j++)
		{
			state[i][j]=0b00000000;
		}
	}
}


void OLED_SPI0_Init(void)
{
	unsigned short i;
	  
	/* enable PORTD clock */
	SIM_SCGC5|=SIM_SCGC5_PORTD_MASK;	//PORTD1-3对应OLED控制
	SIM_SCGC5|=SIM_SCGC5_PORTE_MASK; //PTE31
	SIM_SCGC4|=SIM_SCGC4_SPI0_MASK;
	
	/*portD set to GPIO*/	    
	PORTE_PCR31=PORT_PCR_MUX(0X1); //PTE31:OLED RESET
	PORTD_PCR2=PORT_PCR_MUX(0X1); //PTD2:OLED D/C
	
	PORTD_PCR1=PORT_PCR_MUX(0X2); //PTD1:OLED SPI SCK
	PORTD_PCR3=PORT_PCR_MUX(0X5); //PTD3:OLED SPI MOSI
	
	//Init SPI0
	SPI0_C1 |= 0x5C; //SPOL=1,CPHA=1,LSBFE=0
	SPI0_BR = 0x10; //Bus Clock 再2分频	
	
	//set as output
	DDR_OLED_DC;
	DDR_OLED_RESET; 
	
	OLED_DC_H;
	
	//产生硬件RESET信号
	OLED_RESET_L;
	for(i=0;i<30000;i++) {
		asm("nop");
	}
	OLED_RESET_H;
}

void OLED_Init(void) //系统初始化调用这个
{

  OLED_SPI0_Init();
  
  if (OLED_TYPE==SSD1325) {
		OLED_W_Ctl(0xae); //OLED off
		OLED_W_Ctl(0xb3); //Clock div
		OLED_W_Ctl(0x91); 
		OLED_W_Ctl(0xa8); //设置为64行
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0xa2); //offset = 76？
		OLED_W_Ctl(0x4C); 
		OLED_W_Ctl(0xa1); //从0开始
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0xa0); //remap，A[6]=1 A[4]=1
		OLED_W_Ctl(0x50);
		OLED_W_Ctl(0xad); //启用外来VCC
		OLED_W_Ctl(0x02); 
		OLED_W_Ctl(0x81); //对比度
		OLED_W_Ctl(0x40); 
		OLED_W_Ctl(0x86); //Current Range
		OLED_W_Ctl(0xbe); //Vcomh设置
		OLED_W_Ctl(0x02);
		OLED_W_Ctl(0xbf); //Set Seg Low Voltage
		OLED_W_Ctl(0x0e); 
		OLED_W_Ctl(0xa4); //Normal Mode
		OLED_W_Ctl(0x23); //Graphic 加速设置，启用了Rect绘制
		OLED_W_Ctl(0x01); 
		OLED_W_Ctl(0x24); //设置Rect范围
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0xaf); //OLED on
  }
  
  if (OLED_TYPE==SSD1306) {
		OLED_W_Ctl(0xae); //OLED off
		OLED_W_Ctl(0xd5); //Set Clock
		OLED_W_Ctl(0x80); 
		OLED_W_Ctl(0xa8); //行数
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0xd3); //行offset
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0x40); //Start Line
		OLED_W_Ctl(0x8D); //电荷泵
		OLED_W_Ctl(0x14); 
		OLED_W_Ctl(0xa1); //设置方向 127对应Seg0
		OLED_W_Ctl(0xc8); //Com[n-1] -> Com0
		OLED_W_Ctl(0xda); //无Left/Right Remap，Alter Com Pin，A[5]=0 A[4]=1
		OLED_W_Ctl(0x12); 
		OLED_W_Ctl(0x81); //对比度
		OLED_W_Ctl(0xcf); 
		OLED_W_Ctl(0xd9); //PreCharge
		OLED_W_Ctl(0xf1); 
		OLED_W_Ctl(0xdb); //Vcom
		OLED_W_Ctl(0x40); 
		OLED_W_Ctl(0xa4); //显示
		OLED_W_Ctl(0xa6); //1对应像素on
		OLED_W_Ctl(0xaf); //OLED on
  }
  
  OLED_Clr();
  
}



//write a control word 'cw' to OLED 'cs'(CSA/CSB)
void OLED_W_Ctl(unsigned char cw) {
	unsigned char i;
	
	OLED_DC_L;//write ctl

	while ((SPI0_S & 0x20) == 0); //SPTEF发送不为空
	
	SPI0_D = cw;
		
	while ((SPI0_S & 0x80) == 0); //SPRF接收未满
	
	i=SPI0_D;
	  
	OLED_DC_H;
 
}

//write a data word 'dw' to OLED 'cs'(CSA/CSB)
void OLED_W_Dat(unsigned char dw) {
	unsigned char i;
	
	OLED_DC_H;//write data
	
	while ((SPI0_S & 0x20) == 0); //SPTEF发送不为空
	
	SPI0_D = dw;
		
	while ((SPI0_S & 0x80) == 0); //SPRF接收未满
	
	i=SPI0_D;
	
	OLED_DC_H;
	
}


//clear OLED screen
void OLED_Clr(void) {
	unsigned char i,j;
	
	if (OLED_TYPE==SSD1325) {
		OLED_W_Ctl(0x75); /* set row address */
		OLED_W_Ctl(0x00); /* set row start address */
		OLED_W_Ctl(0x4f); /* set row end address */
		OLED_W_Ctl(0x15); /* set column address */
		OLED_W_Ctl(0x00); /* set column start address */
		OLED_W_Ctl(0x3f); /* set column end address */
		for(i=0;i<64;i++) {
			for(j=0;j<80;j++) {
				OLED_W_Dat(0x00);
			}
		}
	}

	if (OLED_TYPE==SSD1306) {
		for(i=0;i<8;i++) {
			OLED_W_Ctl(0xB0+i);	//选择行
			OLED_W_Ctl(0x00);	//选择列（0-127的Low）
			OLED_W_Ctl(0x10);	//选择列（0-127的High）
			for(j=0;j<128;j++) {
				OLED_W_Dat(0x00);
			}
		}
	}
}

void OLED_W_Test(void) {
	unsigned char i,j;

	if (OLED_TYPE==SSD1325) {
		OLED_W_Ctl(0x75); /* set row address */
		OLED_W_Ctl(0x00); /* set row start address */
		OLED_W_Ctl(0x3f); /* set row end address */
		OLED_W_Ctl(0x15); /* set column address */
		OLED_W_Ctl(0x00); /* set column start address */
		OLED_W_Ctl(0x3f); /* set column end address */
		for(i=0;i<64;i++) {
			for(j=0;j<64;j++) {
				OLED_W_Dat(((j/4)<<4)+(j/4));
			}
		}
	}
	
	if (OLED_TYPE==SSD1306) {
		for(i=0;i<4;i++) {
			OLED_W_Ctl(0xB0+i);	//选择行
			OLED_W_Ctl(0x00);	//选择列（0-127的Low）
			OLED_W_Ctl(0x10);	//选择列（0-127的High）
			for(j=0;j<58;j++) {
				OLED_W_Dat(0x98);
			}
		}
	}
	
}

void OLED_W_Dot(unsigned char lx,unsigned char ly,char val) {
	unsigned char temp;	//i,j,

	if (OLED_TYPE==SSD1325) {
		//Not finished yet
	}
	

	if (OLED_TYPE==SSD1306) {
		OLED_W_Ctl(0xB0+((lx/8)%8));
		
		temp = (ly%128);  
		OLED_W_Ctl(0x00+(temp&0x0f));//低四位
		OLED_W_Ctl(0x10+((temp>>4)&0x0f));//高四位
		
		temp = lx%8;
		
		OLED_W_Dat(val);
	}
}


void dot(unsigned char lx,unsigned char ly,char val){//以函数OLED_W_Dot和全局二维数组state为基础的单点操作函数，lx为范围从0到63的行坐标，ly为0到127的列坐标，val表示操作，1为点亮，0为熄灭
	char temp=lx%8;
	int t=lx/8;
	char vall;
	if(val==1){
	switch(temp)
	{
	case 0:vall=0b00000001;break;
	case 1:vall=0b00000010;break;
	case 2:vall=0b00000100;break;
	case 3:vall=0b00001000;break;
	case 4:vall=0b00010000;break;
	case 5:vall=0b00100000;break;
	case 6:vall=0b01000000;break;
	case 7:vall=0b10000000;break;
	}
	state[ly][t]|=vall;
	OLED_W_Dot(lx,ly,state[ly][t]);
	}
	else if(val==0){
	switch(temp)
		{
		case 0:vall=0b11111110;break;
		case 1:vall=0b11111101;break;
		case 2:vall=0b11111011;break;
		case 3:vall=0b11110111;break;
		case 4:vall=0b11101111;break;
		case 5:vall=0b11011111;break;
		case 6:vall=0b10111111;break;
		case 7:vall=0b01111111;break;
		}
	state[ly][t]&=vall;
	OLED_W_Dot(lx,ly,state[ly][t]);
	}
}

//write a 8*8 character 'ch' to OLED at (lx,ly)
//don't set the 'ly' equal to 121-???
//don't set the 'lx' equal to 8-??
void OLED_W_Ch(unsigned char lx,unsigned char ly,char ch) {
	unsigned char i,j,nChar;
	unsigned short temp;

	if (OLED_TYPE==SSD1325) {
		OLED_W_Ctl(0x75); /* set row address */
		OLED_W_Ctl((lx%8)*8); /* set row start address */
		OLED_W_Ctl((lx%8)*8+7); /* set row end address */
		OLED_W_Ctl(0x15); /* set column address */
		OLED_W_Ctl((ly%128)/2); /* set column start address */
		OLED_W_Ctl((ly%128)/2+3); /* set column end address */
		for(i=0;i<8;i++) {
			for(j=0;j<4;j++) {
				temp = (ch-0x20)*8;
				nChar=	(ASCII[temp+j*2]&(1<<i))?0x0F:0x00;
				nChar|=	(ASCII[temp+j*2+1]&(1<<i))?0xF0:0x00;
				OLED_W_Dat(nChar);
			}
		}		
	}
	
	if (OLED_TYPE==SSD1306) {
		OLED_W_Ctl(0xB0+(lx%8));
		nChar=(ly%128);  
		OLED_W_Ctl(0x00+(nChar&0x0f));//低四位
		OLED_W_Ctl(0x10+((nChar>>4)&0x0f));//高四位
		temp = (ch-0x20)*8;
		for(i=0;i<8;i++) {
			OLED_W_Dat(ASCII[temp+i]);
		}
	}
}

//write a string 'sch' to OLED  at (lx,ly)
void OLED_W_Str(unsigned char lx,unsigned char ly,char *sch) {
	char *p2ch = sch;
	unsigned char L_y = ly;
	while (*p2ch) {
		OLED_W_Ch(lx,L_y,*p2ch++);
		L_y += 8;
	}
}

//write a 128*64 bmp to OLED
void OLED_W_Bmp(char *bmp) {
	char *p2bmp = bmp;
	unsigned char i,j;
	j = 0;

	if (OLED_TYPE==SSD1325) {
		//Not finished yet
	}
	
	if (OLED_TYPE==SSD1306) {
		OLED_W_Ctl(0xB0);   //X
		OLED_W_Ctl(0x00);  //Y Low
		OLED_W_Ctl(0x10);  //Y High
		for(i=0;i<8;i++) {
			for(j=0;j<128;j++) {
				OLED_W_Dat(*p2bmp++);
			}
		}
	}
}


//#pragma CONST_SEG DATAS  //Tell the linker to allocate the words in ROM.
//ASCII Table from 0x20 to 7F
const unsigned char ASCII[]={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //' '
0x00, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00, //'!'
0x00, 0x00, 0x0F, 0x03, 0x00, 0x0F, 0x03, 0x00, //'"'
0x0c, 0x1e, 0x3f, 0x7e, 0x7e, 0x3f, 0x1e ,0x0c, //'#'//已改成心形
0x00, 0x00, 0x66, 0x49, 0xC9, 0x33, 0x00, 0x00, //'$'
0x00, 0x12, 0x15, 0x52, 0xA8, 0x48, 0x00, 0x00, //'%'
0x00, 0x00, 0x60, 0x9C, 0xB2, 0xC2, 0xA2, 0x00, //'&'
0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, //'''
0x00, 0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, //'('
0x00, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x00, 0x00, //')'
0x00, 0x00, 0x02, 0x1A, 0x07, 0x1A, 0x02, 0x00, //'*'
0x00, 0x10, 0x10, 0x10, 0xFE, 0x10, 0x10, 0x10, //'+'
0x00, 0x00, 0x00, 0xC0, 0x40, 0x00, 0x00, 0x00, //','
0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, //'-'
0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, //'.'
0x00, 0x80, 0x60, 0x18, 0x06, 0x01, 0x00, 0x00, //'/'
0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x7E, 0x00, //'0'
0x00, 0x00, 0x82, 0x82, 0xFF, 0x80, 0x80, 0x00, //'1'
0x00, 0xC2, 0xA1, 0x91, 0x89, 0xC6, 0x00, 0x00, //'2'
0x00, 0x42, 0x81, 0x89, 0x89, 0x76, 0x00, 0x00, //'3'
0x00, 0x10, 0x1C, 0x12, 0x91, 0xFF, 0x90, 0x00, //'4'
0x00, 0x40, 0x8F, 0x89, 0x89, 0x89, 0x71, 0x00, //'5'
0x00, 0x00, 0x7C, 0x8A, 0x89, 0x89, 0x71, 0x00, //'6'
0x00, 0x03, 0x01, 0x01, 0xE1, 0x19, 0x07, 0x00, //'7'
0x00, 0x76, 0x89, 0x89, 0x89, 0x89, 0x76, 0x00, //'8'
0x00, 0x8E, 0x91, 0x91, 0x91, 0x51, 0x3E, 0x00, //'9'
0x00, 0x00, 0x00, 0xCC, 0xCC, 0x00, 0x00, 0x00, //':'
0x00, 0x00, 0x80, 0xCC, 0x4C, 0x00, 0x00, 0x00, //';'
0x00, 0x10, 0x10, 0x28, 0x44, 0x44, 0x82, 0x00, //'<'
0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, //'='
0x00, 0x82, 0x44, 0x44, 0x28, 0x10, 0x10, 0x00, //'>'
0x00, 0x00, 0x02, 0x81, 0xA1, 0x11, 0x0E, 0x00, //'?'
0x00, 0x7e, 0x81, 0x99, 0xa5, 0xbd, 0xa1, 0x7e,	//'@'
0x00, 0x80, 0xC0, 0xBD, 0x23, 0xBC, 0xC0, 0x80, //'A'
0x00, 0x81, 0xFF, 0x89, 0x89, 0x89, 0x76, 0x00, //'B'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x81, 0x43, 0x00, //'C'
0x00, 0x81, 0xFF, 0x81, 0x81, 0x42, 0x3C, 0x00, //'D'
0x00, 0x81, 0xFF, 0x89, 0x9D, 0x81, 0xC3, 0x00, //'E'
0x00, 0x81, 0xFF, 0x89, 0x1D, 0x01, 0x03, 0x00, //'F'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x91, 0x73, 0x10, //'G'
0x00, 0x81, 0xFF, 0x89, 0x08, 0x89, 0xFF, 0x81, //'H'
0x00, 0x00, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x00, //'I'
0x00, 0x70, 0x80, 0x81, 0x81, 0x7F, 0x01, 0x00, //'J'
0x00, 0x81, 0xFF, 0x91, 0x18, 0x25, 0xC3, 0x81, //'K'
0x00, 0x81, 0xFF, 0x81, 0x80, 0x80, 0xE0, 0x00, //'L'
0x00, 0x81, 0xFF, 0x87, 0x18, 0x87, 0xFF, 0x81, //'M'
0x81, 0xFF, 0x83, 0x0C, 0x30, 0xC1, 0xFF, 0x01, //'N'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, //'O'
0x00, 0x81, 0xFF, 0x91, 0x11, 0x11, 0x0E, 0x00, //'P'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, //'Q'
0x00, 0x81, 0xFF, 0x91, 0x11, 0x31, 0x4E, 0x80, //'R'
0x00, 0xC6, 0x49, 0x89, 0x89, 0x8A, 0x73, 0x00, //'S'
0x00, 0x03, 0x01, 0x81, 0xFF, 0x81, 0x01, 0x03, //'T'
0x00, 0x01, 0x7F, 0x81, 0x80, 0x81, 0x7F, 0x01, //'U'
0x01, 0x07, 0x39, 0xC0, 0xC0, 0x39, 0x07, 0x01, //'V'
0x00, 0x01, 0x7F, 0x81, 0x78, 0x81, 0x7F, 0x01, //'W'
0x00, 0x81, 0xC3, 0xA5, 0x18, 0xA5, 0xC3, 0x81, //'X'
0x00, 0x01, 0x03, 0x8D, 0xF0, 0x8D, 0x03, 0x01, //'Y'
0x00, 0x00, 0xC3, 0xA1, 0x99, 0x85, 0xC3, 0x00, //'Z'
0x00, 0x00, 0x00, 0xFF, 0x01, 0x01, 0x00, 0x00, //'['
0x00, 0x01, 0x06, 0x38, 0xC0, 0x00, 0x00, 0x00, //'\'
0x00, 0x01, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, //']'
0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00, //'^'
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //'_'
0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, //'`'
0x00, 0x68, 0x94, 0x94, 0x94, 0x54, 0xF8, 0x80, //'a'
0x81, 0xFF, 0x48, 0x84, 0x84, 0x84, 0x78, 0x00, //'b'
0x00, 0x78, 0x84, 0x84, 0x84, 0x88, 0x4C, 0x00, //'c'
0x00, 0x78, 0x84, 0x84, 0x84, 0x49, 0xFF, 0x80, //'d'
0x00, 0x78, 0x94, 0x94, 0x94, 0x94, 0x98, 0x00, //'e'
0x00, 0x84, 0x84, 0xFE, 0x85, 0x85, 0x85, 0x00, //'f'
0x00, 0x1e, 0xa1, 0xa1, 0xa1, 0x92, 0x7f, 0x01, //'g'
0x00, 0x81, 0xFF, 0x88, 0x04, 0x84, 0xF8, 0x80, //'h'
0x00, 0x00, 0x84, 0x84, 0xFD, 0x80, 0x80, 0x00, //'i'
0x00, 0x80, 0x84, 0x84, 0x85, 0x7C, 0x00, 0x00, //'j'
0x00, 0x81, 0xFF, 0x10, 0x34, 0xCC, 0x84, 0x84, //'k'
0x00, 0x00, 0x80, 0x81, 0xFF, 0x80, 0x80, 0x00, //'l'
0x84, 0xFC, 0x88, 0x04, 0xF8, 0x88, 0x04, 0xF8, //'m'
0x00, 0x84, 0xFC, 0x88, 0x04, 0x84, 0xF8, 0x80, //'n'
0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x78, 0x00, //'o'
0x00, 0x04, 0xFC, 0x88, 0x84, 0x84, 0x78, 0x00, //'p'
0x00, 0x78, 0x84, 0x84, 0x84, 0x48, 0xFC, 0x04, //'q'
0x00, 0x84, 0xFC, 0x88, 0x84, 0x84, 0x04, 0x00, //'r'
0x00, 0xC8, 0x94, 0x94, 0x94, 0x94, 0x6C, 0x00, //'s'
0x00, 0x04, 0x7E, 0x84, 0x84, 0x84, 0x40, 0x00, //'t'
0x00, 0x04, 0x7C, 0x80, 0x80, 0x44, 0xFC, 0x80, //'u'
0x04, 0x0C, 0x34, 0xC0, 0xC0, 0x34, 0x0C, 0x04, //'v'
0x00, 0x04, 0x7C, 0x84, 0x70, 0x84, 0x7C, 0x04, //'w'
0x00, 0x84, 0xCC, 0x30, 0x30, 0xCC, 0x84, 0x00, //'x'
0x00, 0x01, 0x87, 0x99, 0xe0, 0x19, 0x07, 0x01, //'y'
0x00, 0x00, 0xCC, 0xA4, 0x94, 0x8C, 0xC4, 0x00, //'z'
0x00, 0x00, 0x10, 0xEE, 0x01, 0x00, 0x00, 0x00, //'{'
0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, //'|'
0x00, 0x00, 0x01, 0xEE, 0x10, 0x00, 0x00, 0x00, //'}'
0x00, 0x10, 0x08, 0x08, 0x10, 0x10, 0x08, 0x00, //'~'
0x01, 0x3D, 0x42, 0x81, 0x81, 0x81, 0x43, 0x00, //'DEL'
};


