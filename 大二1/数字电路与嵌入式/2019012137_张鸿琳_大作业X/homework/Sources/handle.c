/*
 * handle.c
 *
 *  Created on: Jul 7, 2021
 *      Author: ����
 */

#include "derivative.h"
#include "OLED.h"
#include "handle.h"

int all;//��¼�������ڲ����Ŀ������
unsigned char pos;//��¼�������ڲ����Ŀ����̬
int next;//��¼��һ��ˢ�µĿ������
char str[5];//���ڷ�������ʾ
unsigned char sc=0;//��¼����
unsigned char now[4][2];//��¼�����ƶ��Ŀ���ĸ���λ���ӵ����½�λ�ã�4����ÿ�ֿ鶼�����ĸ���λ���ӹ��ɣ�2����λ�������½ǵ�����(x,y)
unsigned char test[4][2];//��¼ģ��ĳ�ֱ仯�����ĸ���λ���ӵ����½�λ�ã�4����ÿ�ֿ鶼�����ĸ���λ���ӹ��ɣ�2����λ�������½ǵ�����(x,y)
unsigned char lightened[64][80];//��¼�����Ѿ�����λ�ã���Ӧ��Ϸ�����64*80�����ص�
unsigned char high=0;//��¼ĳһ�����䵽�ײ�����ײ�λ�ã��������Ƿ������ȥ
unsigned char low=100;//��¼ĳһ�����䵽�ײ����䶥��λ�ã��������Ƿ������ȥ
unsigned char min=100;//��¼���ڵ������ѻ�����ߵ�


unsigned char dtoa(unsigned char c1)//ת������
{
  return (c1>=10)? (c1+'A'-10):(c1+'0');
}

void delay()//��ʱ
{
   unsigned short i,j;
   for(i=0;i<3000;i++)
	{
   		for(j=0;j<100;j++)
      		asm("nop");
	}
}

void Initlight(){//��lightened������г�ʼ��
	unsigned char i,j;
	for(i=0;i<=63;i++)
	{
		for(j=0;j<=79;j++)
		{
			lightened[i][j]=0;
		}
	}
}

void ll(unsigned char x,unsigned char y)//light������ĳ��(lx,ly)����2*2�ĵ�λ�񣬷����ƶ���
{
	dot(x,y,1);
	dot(x-1,y,1);
	dot(x,y+1,1);
	dot(x-1,y+1,1);
}

void dd(unsigned char x,unsigned char y)//destroy��Ϩ��ĳ��(lx,ly)����2*2�ĵ�λ�񣬷����ƶ���
{
	dot(x,y,0);
	dot(x-1,y,0);
	dot(x,y+1,0);
	dot(x-1,y+1,0);
}


int crash0(unsigned char x,unsigned char y){//�����������ж�ĳ�����ص��Ƿ���Դﵽ
	if((lightened[x][y]==1)||(x>=64)||(y>=80)||(x<0)||(y<0))
	{
		return 0;
	}
	return 1;
}

int crash(unsigned char x,unsigned char y){//�����������ж�һ������Ƿ�ᷢ����ײ
	int i=crash0(x,y)*crash0(x,y+1)*crash0(x-1,y)*crash0(x-1,y+1);
	return i;
}

int testmove(){//ģ�Ⲣ�ж��Ƿ���������ƶ�һ�����ص�
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

int testrrotate(){//ģ��������ת���ж��Ƿ������ת
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

int testlrotate(){//ģ��������ת���ж��Ƿ������ת
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

int testright(){//ģ�Ⲣ�����Ƿ���������ƶ�һ����
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

int testleft(){//ģ�Ⲣ�����Ƿ���������ƶ�һ����
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

void lighten(int k){//����ĳ�ֿ鲢�Ҽ�¼���ʼ��Ϣ������ֱ����dot���������������е�����
	switch(k){
	case 1:dot(0,36,1);dot(0,37,1);dot(0,38,1);dot(0,39,1);dot(0,40,1);dot(0,41,1);dot(0,42,1);dot(0,43,1);dot(1,36,1);dot(1,37,1);dot(1,38,1);dot(1,39,1);dot(1,40,1);dot(1,41,1);dot(1,42,1);dot(1,43,1);now[0][0]=1;now[0][1]=36;now[1][0]=1;now[1][1]=38;now[2][0]=1;now[2][1]=40;now[3][0]=1;now[3][1]=42;all=1;pos=1;break;//һ����
	case 2:dot(0,36,1);dot(0,37,1);dot(1,36,1);dot(1,37,1);dot(2,36,1);dot(2,37,1);dot(3,36,1);dot(3,37,1);dot(2,38,1);dot(2,39,1);dot(3,38,1);dot(3,39,1);dot(2,40,1);dot(2,41,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=36;now[1][0]=3;now[1][1]=36;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=40;all=2;pos=1;break;//L��
	case 3:dot(0,40,1);dot(0,41,1);dot(1,40,1);dot(1,41,1);dot(2,36,1);dot(2,37,1);dot(3,36,1);dot(3,37,1);dot(2,38,1);dot(2,39,1);dot(3,38,1);dot(3,39,1);dot(2,40,1);dot(2,41,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=40;now[1][0]=3;now[1][1]=40;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=36;all=3;pos=1;break;//7��
	case 4:dot(0,38,1);dot(0,39,1);dot(0,40,1);dot(0,41,1);dot(1,38,1);dot(1,39,1);dot(1,40,1);dot(1,41,1);dot(2,38,1);dot(2,39,1);dot(2,40,1);dot(2,41,1);dot(3,38,1);dot(3,39,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=38;now[1][0]=1;now[1][1]=40;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=40;all=4;pos=1;break;//����
	case 5:dot(0,38,1);dot(0,39,1);dot(0,40,1);dot(0,41,1);dot(1,38,1);dot(1,39,1);dot(1,40,1);dot(1,41,1);dot(2,38,1);dot(2,39,1);dot(2,37,1);dot(2,36,1);dot(3,38,1);dot(3,39,1);dot(3,37,1);dot(3,36,1);now[0][0]=1;now[0][1]=40;now[1][0]=1;now[1][1]=38;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=36;all=5;pos=1;break;//�ҿ�Ѽ��
	case 6:dot(0,38,1);dot(0,39,1);dot(1,38,1);dot(1,39,1);dot(2,36,1);dot(2,37,1);dot(2,38,1);dot(2,39,1);dot(2,40,1);dot(2,41,1);dot(3,36,1);dot(3,37,1);dot(3,38,1);dot(3,39,1);dot(3,40,1);dot(3,41,1);now[0][0]=1;now[0][1]=38;now[1][0]=3;now[1][1]=38;now[2][0]=3;now[2][1]=40;now[3][0]=3;now[3][1]=36;all=6;pos=1;break;//��͹
	case 7:dot(2,38,1);dot(2,39,1);dot(2,40,1);dot(2,41,1);dot(3,38,1);dot(3,39,1);dot(3,40,1);dot(3,41,1);dot(0,38,1);dot(0,39,1);dot(0,37,1);dot(0,36,1);dot(1,38,1);dot(1,39,1);dot(1,37,1);dot(1,36,1);now[0][0]=1;now[0][1]=36;now[1][0]=1;now[1][1]=38;now[2][0]=3;now[2][1]=38;now[3][0]=3;now[3][1]=40;all=7;pos=1;break;//��Ѽ��
	}
}

void getnext(){//ˢ����һ���飬��ʾ���ض�λ��
	dd(55,100);dd(55,102);dd(55,104);dd(55,106);dd(53,98);dd(53,100);dd(53,102);dd(53,104);
	switch(next){
	case 1:ll(55,100);ll(55,102);ll(55,104);ll(55,106);break;//һ����
	case 2:ll(55,100);ll(55,102);ll(55,104);ll(53,100);break;//L��
	case 3:ll(55,100);ll(55,102);ll(55,104);ll(53,104);break;//7��
	case 4:ll(55,100);ll(55,102);ll(53,100);ll(53,102);break;//����
	case 5:ll(55,100);ll(55,102);ll(53,102);ll(53,104);break;//�ҿ�Ѽ��
	case 6:ll(55,100);ll(55,102);ll(55,104);ll(53,102);break;//��͹
	case 7:ll(55,100);ll(55,102);ll(53,100);ll(53,98);break;//��Ѽ��
	}
}

void rrotate(){//˳ʱ����ת����pos״̬�Ŀ�all
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


void lrotate(){//��ʱ����ת����pos״̬�Ŀ�all
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

void right(){//����һ����Ҳ���������������ص�
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

void left(){//����һ����Ҳ���������������ص�
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

void move(){//���������ڲ����Ŀ������ƶ�һ��
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


void above(unsigned char x){//����x�������Ŀ������ƶ�����һ��
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

void addscore(){//���ض�λ����ʾ����
	str[2]=dtoa(sc%10);
	str[1]=dtoa((sc/10)%10);
	str[0]=dtoa((sc/100)%10);
	OLED_W_Str(2,90,str);
}

void score(){//��¼��������ˢ�·���
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

void clr(){//�����Ϸ����
	unsigned char i,j;
	for(i=min-2;i<=63;i+=2)
	{
		for(j=0;j<=78;j+=2)
		{
			dd(i,j);
		}
	}
}

void lose(){//�ж��Ƿ������׼�����¿�ʼ
	if(min<=5)//5�ǽ����Ľ���
	{
		clr();
		OLED_W_Str(3,0,"Game Over");//���ʧ����Ϣ
		delay();
		delay();
		delay();
		delay();
		delay();
		delay();
		delay();
		clr();
		Initlight();//����lightened�������Ϣ
		sc=0;
		high=0;
		low=100;
		min=100;
	}
}

int mmax(unsigned char a,unsigned char b,unsigned char c,unsigned char d){//�����������ҵ��ĸ����е������
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

int mmin(unsigned char a,unsigned char b,unsigned char c,unsigned char d){//�����������ҵ��ĸ����е������
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
