/*
 * handle.c
 *
 *  Created on: Jul 7, 2021
 *      Author: 惠普
 */

#include "derivative.h"
#include "OLED.h"
#include "handle.h"

int all;//记录现在正在操作的块的类型
unsigned char pos;//记录现在正在操作的块的姿态
int next;//记录下一个刷新的块的类型
char str[5];//用于分数的显示
unsigned char sc=0;//记录分数
unsigned char now[4][2];//记录正在移动的块的四个单位格子的左下角位置，4代表每种块都是由四个单位格子构成，2代表单位格子左下角的坐标(x,y)
unsigned char test[4][2];//记录模拟某种变化后块的四个单位格子的左下角位置，4代表每种块都是由四个单位格子构成，2代表单位格子左下角的坐标(x,y)
unsigned char lightened[64][80];//记录现在已经点亮位置，对应游戏区域的64*80个像素点
unsigned char high=0;//记录某一个块落到底部后，其底部位置，方便检测是否可以消去
unsigned char low=100;//记录某一个块落到底部后，其顶部位置，方便检测是否可以消去
unsigned char min=100;//记录现在的整个堆积的最高点


unsigned char dtoa(unsigned char c1)//转化函数
{
  return (c1>=10)? (c1+'A'-10):(c1+'0');
}

void delay()//延时
{
   unsigned short i,j;
   for(i=0;i<3000;i++)
	{
   		for(j=0;j<100;j++)
      		asm("nop");
	}
}

void Initlight(){//对lightened数组进行初始化
	unsigned char i,j;
	for(i=0;i<=63;i++)
	{
		for(j=0;j<=79;j++)
		{
			lightened[i][j]=0;
		}
	}
}

void ll(unsigned char x,unsigned char y)//light，点亮某处(lx,ly)处的2*2的单位格，方便移动块
{
	dot(x,y,1);
	dot(x-1,y,1);
	dot(x,y+1,1);
	dot(x-1,y+1,1);
}

void dd(unsigned char x,unsigned char y)//destroy，熄灭某处(lx,ly)处的2*2的单位格，方便移动块
{
	dot(x,y,0);
	dot(x-1,y,0);
	dot(x,y+1,0);
	dot(x-1,y+1,0);
}


int crash0(unsigned char x,unsigned char y){//辅助函数，判断某个像素点是否可以达到
	if((lightened[x][y]==1)||(x>=64)||(y>=80)||(x<0)||(y<0))
	{
		return 0;
	}
	return 1;
}

int crash(unsigned char x,unsigned char y){//辅助函数，判定一个组块是否会发生冲撞
	int i=crash0(x,y)*crash0(x,y+1)*crash0(x-1,y)*crash0(x-1,y+1);
	return i;
}

int testmove(){//模拟并判定是否可以向下移动一个像素点
	int k;
	for(k=0;k<=3;k++)
	{
		if(crash(now[k][0]+1,now[k][1])==0)
		{
			return 0;
		}
	}
	return 1;
}

int testrrotate(){//模拟向右旋转，判定是否可以旋转
	switch(all)
		{
		case 1:{switch(pos){
		case 1:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0]+2;test[2][1]=now[1][1];test[3][0]=now[1][0]+4;test[3][1]=now[1][1];break;
		case 2:test[0][0]=now[1][0];test[0][1]=now[1][1]-4;test[1][0]=now[0][0];test[1][1]=now[0][1]+2;test[2][0]=now[0][0];test[2][1]=now[1][1]+2;test[3][0]=now[0][0];test[3][1]=now[2][1]+2;break;
		}
		break;
		}
		case 2:{switch(pos){
		case 1:test[0][0]=now[1][0];test[0][1]=now[1][1]+2;test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0]+2;test[2][1]=now[1][1];test[3][0]=now[1][0]+4;test[3][1]=now[1][1];break;
		case 2:test[0][0]=now[1][0]+2;test[0][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]-4;break;
		case 3:test[0][0]=now[1][0];test[0][1]=now[1][1]-2;test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]-4;test[3][1]=now[1][1];break;
		case 4:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]+2;test[3][0]=now[1][0];test[3][1]=now[1][1]+4;break;
		}
		break;
		}
		case 3:{switch(pos){
		case 1:test[0][0]=now[1][0];test[0][1]=now[1][1]+2;test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]-4;test[3][1]=now[1][1];break;
		case 2:test[0][0]=now[1][0]+2;test[0][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]+2;test[3][0]=now[1][0];test[3][1]=now[1][1]+4;break;
		case 3:test[0][0]=now[1][0];test[0][1]=now[1][1]-2;test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0]+2;test[2][1]=now[1][1];test[3][0]=now[1][0]+4;test[3][1]=now[1][1];break;
		case 4:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]-4;break;
		}
		break;
		}
		case 4:test[0][0]=now[0][0];test[0][1]=now[0][1];test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[2][0];test[2][1]=now[2][1];test[3][0]=now[3][0];test[3][1]=now[3][1];break;
		case 5:{switch(pos){
		case 1:test[0][0]=now[1][0]+2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0]-2;test[3][1]=now[1][1]-2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 2:test[0][0]=now[2][0];test[0][1]=now[2][1]+2;test[1][0]=now[2][0];test[1][1]=now[2][1];test[2][0]=now[1][0]+2;test[2][1]=now[1][1];test[3][0]=now[2][0];test[3][1]=now[2][1]-2;break;
		}
		break;
		}
		case 6:{switch(pos){
		case 1:test[0][0]=now[1][0];test[0][1]=now[1][1]+2;test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]+2;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 2:test[0][0]=now[1][0]+2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]+2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 3:test[0][0]=now[1][0];test[0][1]=now[1][1]-2;test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]+2;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 4:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]+2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		}
		break;
		}
		case 7:{switch(pos){
		case 1:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0]+2;test[3][1]=now[1][1]-2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 2:test[0][0]=now[2][0];test[0][1]=now[2][1]-2;test[1][0]=now[2][0];test[1][1]=now[2][1];test[2][0]=now[1][0]+2;test[3][0]=now[2][0];test[3][1]=now[2][1]+2;test[2][1]=now[2][1];break;
		}
		break;
		}
	}
	int i;
	for(i=0;i<=3;i++)
	{
		if(crash(test[i][0],test[i][1])==0)
		{
			return 0;
		}
	}
	return 1;
}

int testlrotate(){//模拟向左旋转，判定是否可以旋转
	switch(all)
		{
		case 1:{switch(pos){
		case 1:test[0][0]=now[2][0]-2;test[0][1]=now[2][1];test[1][0]=now[2][0];test[1][1]=now[2][1];test[2][0]=now[1][0]+2;test[2][1]=now[2][1];test[3][0]=now[1][0]+4;test[3][1]=now[1][1];break;
		case 2:test[0][0]=now[2][0];test[0][1]=now[2][1]-4;test[1][0]=now[2][0];test[1][1]=now[2][1]-2;test[3][0]=now[2][0];test[3][1]=now[2][1]+2;test[2][0]=now[2][0];test[2][1]=now[2][1];break;
		}
		break;
		}
		case 2:{switch(pos){
		case 1:test[0][0]=now[1][0];test[0][1]=now[1][1]-2;test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]-4;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 2:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]+2;test[3][0]=now[1][0];test[3][1]=now[1][1]+4;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 3:test[0][0]=now[1][0];test[0][1]=now[1][1]+2;test[2][0]=now[1][0]+2;test[2][1]=now[1][1];test[3][0]=now[1][0]+4;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 4:test[0][0]=now[1][0]+2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]-4;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		}
		break;
		}
		case 3:{switch(pos){
		case 1:test[0][0]=now[1][0];test[0][1]=now[1][1]-2;test[2][0]=now[1][0]+2;test[2][1]=now[1][1];test[3][0]=now[1][0]+4;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 2:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]-4;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 3:test[0][0]=now[1][0];test[0][1]=now[1][1]+2;test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]-4;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 4:test[0][0]=now[1][0]+2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]+2;test[3][0]=now[1][0];test[3][1]=now[1][1]+4;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		}
		break;
		}
		case 4:test[0][0]=now[0][0];test[0][1]=now[0][1];test[1][0]=now[1][0];test[1][1]=now[1][1];test[2][0]=now[2][0];test[2][1]=now[2][1];test[3][0]=now[3][0];test[3][1]=now[3][1];break;
		case 5:{switch(pos){
		case 1:test[0][0]=now[2][0]+2;test[0][1]=now[2][1];test[1][0]=now[2][0];test[1][1]=now[2][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[2][0]-2;test[3][1]=now[1][1]-2;break;
		case 2:test[0][0]=now[1][0];test[0][1]=now[1][1]+2;test[2][0]=now[1][0]+2;test[2][1]=now[1][1];test[3][0]=now[2][0];test[3][1]=now[2][1]-2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		}
		break;
		}
		case 6:{switch(pos){
		case 1:test[0][0]=now[1][0];test[0][1]=now[1][1]-2;test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]+2;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 2:test[0][0]=now[1][0]-2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]+2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 3:test[0][0]=now[1][0];test[0][1]=now[1][1]+2;test[2][0]=now[1][0]-2;test[2][1]=now[1][1];test[3][0]=now[1][0]+2;test[3][1]=now[1][1];test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		case 4:test[0][0]=now[1][0]+2;test[0][1]=now[1][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0];test[3][1]=now[1][1]+2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		}
		break;
		}
		case 7:{switch(pos){
		case 1:test[0][0]=now[2][0]-2;test[0][1]=now[2][1];test[1][0]=now[2][0];test[1][1]=now[2][1];test[2][0]=now[1][0];test[2][1]=now[1][1]-2;test[3][0]=now[1][0]+2;test[3][1]=now[1][1]-2;break;
		case 2:test[0][0]=now[1][0];test[0][1]=now[1][1]-2;test[2][1]=now[1][1];test[2][0]=now[1][0]+2;test[3][0]=now[2][0];test[3][1]=now[2][1]+2;test[1][0]=now[1][0];test[1][1]=now[1][1];break;
		}
		break;
		}
	}
	int i;
		for(i=0;i<=3;i++)
		{
			if(crash(test[i][0],test[i][1])==0)
			{
				return 0;
			}
		}
	return 1;
}

int testright(){//模拟并检验是否可以向右移动一整格
	int i;
	for(i=0;i<=3;i++)
	{
		if(crash(now[i][0],now[i][1]+2)==0)
		{
			return 0;
		}
	}
	return 1;
}

int testleft(){//模拟并检验是否可以向左移动一整格
	int i;
	for(i=0;i<=3;i++)
	{
		if(crash(now[i][0],now[i][1]-2)==0)
		{
			return 0;
		}
	}
	return 1;
}

void lighten(int k){//点亮某种块并且记录其初始信息，这里直接用dot函数点亮，所以有点冗杂
	switch(k){
	case 1:dot(0,36,1);dot(0,37,1);dot(0,38,1);dot(0,39,1);dot(0,40,1);dot(0,41,1);dot(0,42,1);dot(0,43,1);dot(1,36,1);dot(1,37,1);dot(1,38,1);dot(1,39,1);dot(1,40,1);dot(1,41,1);dot(1,42,1);dot(1,43,1);now[0][0]=1;now[0][1]=36;now[1][0]=1;now[1][1]=38;now[2][0]=1;now[2][1]=40;now[3][0]=1;now[3][1]=42;all=1;pos=1;break;//一字型
	case 2:dot(0,36,1);dot(0,37,1);dot(1,36,1);dot(1,37,1);dot(2,36,1);dot(2,37,1);dot(3,36,1);dot(3,37,1);dot(2,38,1);dot(2,39,1);dot(3,38,1);dot(3,39,1);dot(2,40,1);dot(2,41,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=36;now[1][0]=3;now[1][1]=36;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=40;all=2;pos=1;break;//L型
	case 3:dot(0,40,1);dot(0,41,1);dot(1,40,1);dot(1,41,1);dot(2,36,1);dot(2,37,1);dot(3,36,1);dot(3,37,1);dot(2,38,1);dot(2,39,1);dot(3,38,1);dot(3,39,1);dot(2,40,1);dot(2,41,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=40;now[1][0]=3;now[1][1]=40;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=36;all=3;pos=1;break;//7型
	case 4:dot(0,38,1);dot(0,39,1);dot(0,40,1);dot(0,41,1);dot(1,38,1);dot(1,39,1);dot(1,40,1);dot(1,41,1);dot(2,38,1);dot(2,39,1);dot(2,40,1);dot(2,41,1);dot(3,38,1);dot(3,39,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=38;now[1][0]=1;now[1][1]=40;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=40;all=4;pos=1;break;//方块
	case 5:dot(0,38,1);dot(0,39,1);dot(0,40,1);dot(0,41,1);dot(1,38,1);dot(1,39,1);dot(1,40,1);dot(1,41,1);dot(2,38,1);dot(2,39,1);dot(2,37,1);dot(2,36,1);dot(3,38,1);dot(3,39,1);dot(3,37,1);dot(3,36,1);now[0][0]=1;now[0][1]=40;now[1][0]=1;now[1][1]=38;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=36;all=5;pos=1;break;//右看鸭子
	case 6:dot(0,38,1);dot(0,39,1);dot(1,38,1);dot(1,39,1);dot(2,36,1);dot(2,37,1);dot(2,38,1);dot(2,39,1);dot(2,40,1);dot(2,41,1);dot(3,36,1);dot(3,37,1);dot(3,38,1);dot(3,39,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=38;now[1][0]=3;now[1][1]=38;now[2][0]=3;now[2][1]=40;now[3][0]=3;now[3][1]=36;all=6;pos=1;break;//中凸
	case 7:dot(2,38,1);dot(2,39,1);dot(2,40,1);dot(2,41,1);dot(3,38,1);dot(3,39,1);dot(3,40,1);dot(3,41,1);dot(0,38,1);dot(0,39,1);dot(0,37,1);dot(0,36,1);dot(1,38,1);dot(1,39,1);dot(1,37,1);dot(1,36,1);now[0][0]=1;now[0][1]=36;now[1][0]=1;now[1][1]=38;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=40;all=7;pos=1;break;//左看鸭子
	}
}

void getnext(){//刷新下一个块，显示在特定位置
	dd(55,100);dd(55,102);dd(55,104);dd(55,106);dd(53,98);dd(53,100);dd(53,102);dd(53,104);
	switch(next){
	case 1:ll(55,100);ll(55,102);ll(55,104);ll(55,106);break;//一字型
	case 2:ll(55,100);ll(55,102);ll(55,104);ll(53,100);break;//L型
	case 3:ll(55,100);ll(55,102);ll(55,104);ll(53,104);break;//7型
	case 4:ll(55,100);ll(55,102);ll(53,100);ll(53,102);break;//方块
	case 5:ll(55,100);ll(55,102);ll(53,102);ll(53,104);break;//右看鸭子
	case 6:ll(55,100);ll(55,102);ll(55,104);ll(53,102);break;//中凸
	case 7:ll(55,100);ll(55,102);ll(53,100);ll(53,98);break;//左看鸭子
	}
}

void rrotate(){//顺时针旋转处于pos状态的块all
	switch(all)
	{
	case 1:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0]+4,now[1][1]);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0]+2;now[2][1]=now[1][1];now[3][0]=now[1][0]+4;now[3][1]=now[1][1];pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]-4);ll(now[1][0],now[1][1]+2);now[0][0]=now[1][0];now[0][1]=now[1][1]-4;now[1][0]=now[0][0];now[1][1]=now[0][1]+2;now[2][0]=now[0][0];now[2][1]=now[1][1]+2;now[3][0]=now[0][0];now[3][1]=now[2][1]+2;pos=1;break;
	}
	break;
	}
	case 2:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0]+4,now[1][1]);ll(now[1][0],now[1][1]+2);now[0][0]=now[1][0];now[0][1]=now[1][1]+2;now[2][0]=now[1][0]+2;now[2][1]=now[1][1];now[3][0]=now[1][0]+4;now[3][1]=now[1][1];pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]-4);now[0][0]=now[1][0]+2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]-4;pos=3;break;
	case 3:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0]-2,now[1][1]);ll(now[1][0]-4,now[1][1]);now[0][0]=now[1][0];now[0][1]=now[1][1]-2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]-4;now[3][1]=now[1][1];pos=4;break;
	case 4:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0],now[1][1]+2);ll(now[1][0],now[1][1]+4);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]+2;now[3][0]=now[1][0];now[3][1]=now[1][1]+4;pos=1;break;
	}
	break;
	}
	case 3:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]+2);ll(now[1][0]-2,now[1][1]);ll(now[1][0]-4,now[1][1]);now[0][0]=now[1][0];now[0][1]=now[1][1]+2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]-4;now[3][1]=now[1][1];pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0],now[1][1]+2);ll(now[1][0],now[1][1]+4);now[0][0]=now[1][0]+2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]+2;now[3][0]=now[1][0];now[3][1]=now[1][1]+4;pos=3;break;
	case 3:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0]+2,now[1][1]);ll(now[1][0]+4,now[1][1]);now[0][0]=now[1][0];now[0][1]=now[1][1]-2;now[2][0]=now[1][0]+2;now[2][1]=now[1][1];now[3][0]=now[1][0]+4;now[3][1]=now[1][1];pos=4;break;
	case 4:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]-4);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]-4;pos=1;break;
	}
	break;
	}
	case 4:break;
	case 5:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0]+2,now[1][1]);ll(now[1][0]-2,now[1][1]-2);now[0][0]=now[1][0]+2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0]-2;now[3][1]=now[1][1]-2;pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[1][0],now[1][1]);dd(now[3][0],now[3][1]);ll(now[2][0],now[2][1]+2);ll(now[2][0]+2,now[2][1]);ll(now[2][0]+2,now[2][1]-2);now[0][0]=now[2][0];now[0][1]=now[2][1]+2;now[1][0]=now[2][0];now[1][1]=now[2][1];now[2][0]=now[1][0]+2;now[2][1]=now[1][1];now[3][0]=now[2][0];now[3][1]=now[2][1]-2;pos=1;break;
	}
	break;
	}
	case 6:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0],now[1][1]+2);now[0][0]=now[1][0];now[0][1]=now[1][1]+2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]+2;now[3][1]=now[1][1];pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]+2);ll(now[1][0]+2,now[1][1]);now[0][0]=now[1][0]+2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]+2;pos=3;break;
	case 3:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0],now[1][1]-2);now[0][0]=now[1][0];now[0][1]=now[1][1]-2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]+2;now[3][1]=now[1][1];pos=4;break;
	case 4:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]+2);ll(now[1][0]-2,now[1][1]);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]+2;pos=1;break;
	}
	break;
	}
	case 7:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0]+2,now[1][1]-2);ll(now[1][0]-2,now[1][1]);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0]+2;now[3][1]=now[1][1]-2;pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[1][0],now[1][1]);dd(now[3][0],now[3][1]);ll(now[2][0],now[2][1]-2);ll(now[2][0]+2,now[2][1]);ll(now[2][0]+2,now[2][1]+2);now[0][0]=now[2][0];now[0][1]=now[2][1]-2;now[1][0]=now[2][0];now[1][1]=now[2][1];now[2][0]=now[1][0]+2;now[3][0]=now[2][0];now[3][1]=now[2][1]+2;pos=1;break;
	}
	break;
	}
}
}


void lrotate(){//逆时针旋转处于pos状态的块all
	switch(all)
	{
	case 1:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[1][0],now[1][1]);dd(now[3][0],now[3][1]);ll(now[2][0]-2,now[2][1]);ll(now[2][0]+2,now[2][1]);ll(now[2][0]+4,now[2][1]);now[0][0]=now[2][0]-2;now[0][1]=now[2][1];now[1][0]=now[2][0];now[1][1]=now[2][1];now[2][0]=now[1][0]+2;now[3][0]=now[1][0]+4;now[3][1]=now[1][1];pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[1][0],now[1][1]);dd(now[3][0],now[3][1]);ll(now[2][0],now[2][1]-2);ll(now[2][0],now[2][1]-4);ll(now[2][0],now[2][1]+2);now[0][0]=now[2][0];now[0][1]=now[2][1]-4;now[1][0]=now[2][0];now[1][1]=now[2][1]-2;now[3][0]=now[2][0];now[3][1]=now[2][1]+2;pos=1;break;
	}
	break;
	}
	case 2:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0]-2,now[1][1]);ll(now[1][0]-4,now[1][1]);now[0][0]=now[1][0];now[0][1]=now[1][1]-2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]-4;now[3][1]=now[1][1];pos=4;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]+2);ll(now[1][0],now[1][1]+4);ll(now[1][0]-2,now[1][1]);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]+2;now[3][0]=now[1][0];now[3][1]=now[1][1]+4;pos=1;break;
	case 3:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]+2);ll(now[1][0]+2,now[1][1]);ll(now[1][0]+4,now[1][1]);now[0][0]=now[1][0];now[0][1]=now[1][1]+2;now[2][0]=now[1][0]+2;now[2][1]=now[1][1];now[3][0]=now[1][0]+4;now[3][1]=now[1][1];pos=2;break;
	case 4:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]-4);ll(now[1][0]+2,now[1][1]);now[0][0]=now[1][0]+2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]-4;pos=3;break;
	}
	break;
	}
	case 3:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0]+4,now[1][1]);ll(now[1][0],now[1][1]-2);now[0][0]=now[1][0];now[0][1]=now[1][1]-2;now[2][0]=now[1][0]+2;now[2][1]=now[1][1];now[3][0]=now[1][0]+4;now[3][1]=now[1][1];pos=4;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]-4);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]-4;pos=1;break;
	case 3:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0]-4,now[1][1]);ll(now[1][0],now[1][1]+2);now[0][0]=now[1][0];now[0][1]=now[1][1]+2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]-4;now[3][1]=now[1][1];pos=2;break;
	case 4:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0],now[1][1]+2);ll(now[1][0],now[1][1]+4);now[0][0]=now[1][0]+2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]+2;now[3][0]=now[1][0];now[3][1]=now[1][1]+4;pos=3;break;
	}
	break;
	}
	case 4:break;
	case 5:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[1][0],now[1][1]);dd(now[3][0],now[3][1]);ll(now[2][0]+2,now[2][1]);ll(now[2][0],now[2][1]-2);ll(now[2][0]-2,now[2][1]-2);now[0][0]=now[2][0]+2;now[0][1]=now[2][1];now[1][0]=now[2][0];now[1][1]=now[2][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[2][0]-2;now[3][1]=now[1][1]-2;pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]+2);ll(now[1][0]+2,now[1][1]);ll(now[1][0]+2,now[1][1]-2);now[0][0]=now[1][0];now[0][1]=now[1][1]+2;now[2][0]=now[1][0]+2;now[2][1]=now[1][1];now[3][0]=now[2][0];now[3][1]=now[2][1]-2;pos=1;break;
	}
	break;
	}
	case 6:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0],now[1][1]-2);now[0][0]=now[1][0];now[0][1]=now[1][1]-2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]+2;now[3][1]=now[1][1];pos=4;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]+2);ll(now[1][0]-2,now[1][1]);now[0][0]=now[1][0]-2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]+2;pos=1;break;
	case 3:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0]-2,now[1][1]);ll(now[1][0]+2,now[1][1]);ll(now[1][0],now[1][1]+2);now[0][0]=now[1][0];now[0][1]=now[1][1]+2;now[2][0]=now[1][0]-2;now[2][1]=now[1][1];now[3][0]=now[1][0]+2;now[3][1]=now[1][1];pos=2;break;
	case 4:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0],now[1][1]+2);ll(now[1][0]+2,now[1][1]);now[0][0]=now[1][0]+2;now[0][1]=now[1][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0];now[3][1]=now[1][1]+2;pos=3;break;
	}
	break;
	}
	case 7:{switch(pos){
	case 1:dd(now[0][0],now[0][1]);dd(now[1][0],now[1][1]);dd(now[3][0],now[3][1]);ll(now[2][0]-2,now[2][1]);ll(now[2][0],now[2][1]-2);ll(now[2][0]+2,now[2][1]-2);now[0][0]=now[2][0]-2;now[0][1]=now[2][1];now[1][0]=now[2][0];now[1][1]=now[2][1];now[2][0]=now[1][0];now[2][1]=now[1][1]-2;now[3][0]=now[1][0]+2;now[3][1]=now[1][1]-2;pos=2;break;
	case 2:dd(now[0][0],now[0][1]);dd(now[2][0],now[2][1]);dd(now[3][0],now[3][1]);ll(now[1][0],now[1][1]-2);ll(now[1][0]+2,now[1][1]);ll(now[1][0]+2,now[1][1]+2);now[0][0]=now[1][0];now[0][1]=now[1][1]-2;now[2][1]=now[1][1];now[2][0]=now[1][0]+2;now[3][0]=now[2][0];now[3][1]=now[2][1]+2;pos=1;break;
	}
	break;
	}
}
}

void right(){//右移一整格，也就是右移两个像素点
	int i;
	for(i=0;i<=3;i++)
	{
		dd(now[i][0],now[i][1]);
	}
	for(i=0;i<=3;i++)
	{
		ll(now[i][0],now[i][1]+2);
		now[i][1]+=2;
	}
}

void left(){//左移一整格，也就是左移两个像素点
	int i;
	for(i=0;i<=3;i++)
	{
		dd(now[i][0],now[i][1]);
	}
	for(i=0;i<=3;i++)
	{
		ll(now[i][0],now[i][1]-2);
		now[i][1]-=2;
	}
}

void move(){//将现在正在操作的块向下移动一格
	int i;
	for(i=0;i<=3;i++)
	{
		dot(now[i][0]-1,now[i][1]+1,0);
		dot(now[i][0]-1,now[i][1],0);
	}
	for(i=0;i<=3;i++)
		{
			dot(now[i][0]+1,now[i][1],1);
			dot(now[i][0]+1,now[i][1]+1,1);
			now[i][0]++;
		}
}


void above(unsigned char x){//将第x层的上面的块整体移动下来一层
	unsigned char i,j;
	for(i=x;i>=min;i-=2)
	{
		for(j=0;j<=78;j+=2)
		{
			lightened[i][j]=lightened[i-2][j];
			lightened[i-1][j]=lightened[i-3][j];
			lightened[i][j+1]=lightened[i-2][j+1];
			lightened[i-1][j+1]=lightened[i-3][j+1];
			if(lightened[i][j]==1)
			{
				ll(i,j);
			}
			else if(lightened[i][j]==0)
			{
				dd(i,j);
			}
		}
	}
}

void addscore(){//在特定位置显示分数
	str[2]=dtoa(sc%10);
	str[1]=dtoa((sc/10)%10);
	str[0]=dtoa((sc/100)%10);
	OLED_W_Str(2,90,str);
}

void score(){//记录分数并且刷新分数
	unsigned char i,j;
	unsigned char sum=0;
	for(i=high;i>=low;i-=2)
	{
		for(j=0;j<=78;j+=2)
		{
			sum+=lightened[i][j];
		}
		if(sum==40)
		{
			above(i);
			i+=2;
			sc++;
			min++;
		}
		sum=0;
		
	}
	addscore();
}

void clr(){//清空游戏区域
	unsigned char i,j;
	for(i=min-2;i<=63;i+=2)
	{
		for(j=0;j<=78;j+=2)
		{
			dd(i,j);
		}
	}
}

void lose(){//判断是否结束并准备重新开始
	if(min<=5)//5是结束的界限
	{
		clr();
		OLED_W_Str(3,0,"Game Over");//输出失败信息
		delay();
		delay();
		delay();
		delay();
		delay();
		delay();
		delay();
		clr();
		Initlight();//重置lightened数组的信息
		sc=0;
		high=0;
		low=100;
		min=100;
	}
}

int mmax(unsigned char a,unsigned char b,unsigned char c,unsigned char d){//辅助函数，找到四个数中的最大者
	int x;
	if(a>b)
	{
		x=a;
	}
	else
	{
		x=b;
	}
	if(x<c)
	{
		x=c;
	}
	if(x<d)
	{
		x=d;
	}
	return x;
}

int mmin(unsigned char a,unsigned char b,unsigned char c,unsigned char d){//辅助函数，找到四个数中的最低者
	int x;
		if(a<b)
		{
			x=a;
		}
		else
		{
			x=b;
		}
		if(x>c)
		{
			x=c;
		}
		if(x>d)
		{
			x=d;
		}
		return x;
}
