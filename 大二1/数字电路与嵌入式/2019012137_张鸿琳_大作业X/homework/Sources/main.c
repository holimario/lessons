/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "OLED.h"
#include "handle.h"
#include "sound.h"

unsigned short pNote=0,nDuration=0;//记录播放的音符和剩余音长
extern unsigned char state[128][8];//声明为OLED.c中的外部变量，也就是单点操作函数dot的信息存储二维数组
extern const unsigned short note[520];//声明为sound.c中的外部变量，记录音高
extern const unsigned short duration[520];//声明为sound.c中的外部变量，记录音长
extern int all;//声明为handle.c中的外部变量，记录现在正在操作的块的类型
extern unsigned char pos;//声明为handle.c中的外部变量，记录现在正在操作的块的姿态
extern int next;//声明为handle.c中的外部变量，记录下一个刷新的块的类型
extern char str[5];//声明为handle.c中的外部变量，用于分数的显示
extern unsigned char sc;//声明为handle.c中的外部变量，记录分数
extern unsigned char now[4][2];//声明为handle.c中的外部变量，记录正在移动的块的四个单位格子的左下角位置，4代表每种块都是由四个单位格子构成，2代表单位格子左下角的坐标(x,y)
extern unsigned char test[4][2];//声明为handle.c中的外部变量，记录模拟某种变化后块的四个单位格子的左下角位置，4代表每种块都是由四个单位格子构成，2代表单位格子左下角的坐标(x,y)
extern unsigned char lightened[64][80];//声明为handle.c中的外部变量，记录现在已经点亮位置，对应游戏区域的64*80个像素点
extern unsigned char high;//声明为handle.c中的外部变量，记录某一个块落到底部后，其底部位置，方便检测是否可以消去
extern unsigned char low;//声明为handle.c中的外部变量，记录某一个块落到底部后，其顶部位置，方便检测是否可以消去
extern unsigned char min;//声明为handle.c中的外部变量，记录现在的整个堆积的最高点


void SysTick_Handler (void) {//时钟中断函数，用于播放音乐
unsigned int i;
if(nDuration==0) {
if(note[pNote]==0xff) pNote=0;//设置播放新的音
TPM0_Set ((unsigned short)( note[pNote])); 
nDuration = duration[pNote];
pNote++;
} 
nDuration--; 
i = SYST_CSR; //读操作清除标志位
}

void PORTA_IRQHandler(){//按键中断函数，判定中断源，并执行相应的操作
	if((GPIOA_PDIR & 0b1000000000000)==0)//逆时针旋转
	{
		if(testlrotate()==1)
		{
			lrotate();
		}

	}
	else if((GPIOA_PDIR & 0b10000000000000)==0)//顺时针旋转
	{
		if(testrrotate()==1)
		{
			rrotate();
		}
	}
	else if((GPIOA_PDIR & 0b100000000000000)==0)//向左平移一整格
	{
		if(testleft()==1)
		{
			left();
		}
	}
	else if((GPIOA_PDIR & 0b10000000000000000)==0)//向右平移一整格
	{
		if(testright()==1)
		{
			right();
		}
	}
	else if((GPIOA_PDIR & 0b1000000000000000)==0)//快速向下平移
		{
		if(testmove()==1)
		{
			move();
		}
		if(testmove()==1)
		{
			move();
		}
		if(testmove()==1)
		{
			move();
		}
		if(testmove()==1)
		{
			move();
		}
		}
	delay();//通过延时缓解按键震颤
	PORTA_PCR12|=0x01000000;//标志位清除
	PORTA_PCR13|=0x01000000;//标志位清除
	PORTA_PCR14|=0x01000000;//标志位清除
	PORTA_PCR15|=0x01000000;//标志位清除
	PORTA_PCR16|=0x01000000;//标志位清除
}



int main(void) {
	Inintstate();//state初始化
	Initlight();//lightened初始化
	
	SIM_SCGC5|=((1<<11)|(1<<9));// 启用模块PORTC时钟
	
	asm("CPSIE i");//开启全局中断
	NVIC_ISER|=0x40000000;//开启PORTA中断
	
	PORTA_PCR12=0x000A0102;//左侧左键下降触发中断
	PORTA_PCR12|=0x01000000;//清除其标志位
	
	PORTA_PCR13=0x000A0102;//左侧右键下降触发中断
	PORTA_PCR13|=0x01000000;//清除其标志位
	
	PORTA_PCR14=0x000A0102;//右侧左键下降触发中断
	PORTA_PCR14|=0x01000000;//清除其标志位
		
	PORTA_PCR15=0x000A0102;//右侧左键下降触发中断
	PORTA_PCR15|=0x01000000;//清除其标志位
	
	PORTA_PCR16=0x000A0102;//右侧右键下降触发中断
	PORTA_PCR16|=0x01000000;//清除其标志位
	
	// 指定用作GPIO
	PORTC_PCR0 = 0x0100;
	PORTC_PCR3 = 0x0100;
	
	GPIOC_PDDR |= 0x09;
	GPIOC_PDOR &= (~0x09);
	
	
	OLED_Init();//OLED初始化
	
	
	OLED_Clr();//清屏
	
	TPM0_Init();
	SYSTICK_Init();
	
	//画分割线
	OLED_W_Dot(0,80,0b11111111);
	OLED_W_Dot(8,80,0b11111111);
	OLED_W_Dot(16,80,0b11111111);
	OLED_W_Dot(24,80,0b11111111);
	OLED_W_Dot(32,80,0b11111111);
	OLED_W_Dot(40,80,0b11111111);
	OLED_W_Dot(48,80,0b11111111);
	OLED_W_Dot(56,80,0b11111111);
	OLED_W_Dot(61,80,0b11111111);
	
	OLED_W_Str(0,82,"score:");
	addscore();
	OLED_W_Str(4,85,"next:");
	int i;
	next=(rand()%7)+1;//随机生成块
	for(;;)
	{
		all=next;
		next=(rand()%7)+1;
		getnext();//更新下一个块的信息
		lighten(all);//点亮新的下落的块
		move();
		move();
		for(;testmove()==1;)//在没有撞到下面的块之前进行向下移动
		{
			move();
			delay();
		}
		for(i=0;i<=3;i++)//记录点亮相应的块的信息
		{
			lightened[now[i][0]][now[i][1]]=1;
			lightened[now[i][0]-1][now[i][1]]=1;
			lightened[now[i][0]][now[i][1]+1]=1;
			lightened[now[i][0]-1][now[i][1]+1]=1;
		}
		if(min>mmin(now[0][0],now[1][0],now[2][0],now[3][0]))//更新整个堆积的最高处信息
		{
			min=mmin(now[0][0],now[0][0],now[2][0],now[3][0]);
		}
		high=mmax(now[0][0],now[1][0],now[2][0],now[3][0]);//更新刚刚落下的块的范围信息，方便判定和计算得分
		low=mmin(now[0][0],now[1][0],now[2][0],now[3][0]);//更新刚刚落下的块的范围信息，方便判定和计算得分
		score();//计算得分并更新
		lose();//判断是否过界
	}
}



