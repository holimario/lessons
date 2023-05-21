/*
 * handle.h
 *
 *  Created on: Jul 7, 2021
 *      Author: 惠普
 */

#ifndef HANDLE_H_
#define HANDLE_H_

unsigned char dtoa(unsigned char c1);//转化函数
void Initlight();//对lightened数组进行初始化
void ll(unsigned char x,unsigned char y);//light，点亮某处(lx,ly)处的2*2的单位格，方便移动块
void dd(unsigned char x,unsigned char y);//destroy，熄灭某处(lx,ly)处的2*2的单位格，方便移动块
int crash0(unsigned char x,unsigned char y);//辅助函数，判断某个像素点是否可以达到
int crash(unsigned char x,unsigned char y);//辅助函数，判定一个组块是否会发生冲撞
int testmove();//模拟并判定是否可以向下移动一个像素点
int testrrotate();//模拟向右旋转，判定是否可以旋转
int testlrotate();//模拟向左旋转，判定是否可以旋转
int testright();//模拟并检验是否可以向右移动一整格
int testleft();//模拟并检验是否可以向左移动一整格
void lighten(int k);//点亮某种块并且记录其初始信息，这里直接用dot函数点亮，所以有点冗杂
void getnext();//刷新下一个块，显示在特定位置
void rrotate();//顺时针旋转处于pos状态的块all
void lrotate();//逆时针旋转处于pos状态的块all
void right();//右移一整格，也就是右移两个像素点
void left();//左移一整格，也就是左移两个像素点
void move();//将现在正在操作的块向下移动一格
void above(unsigned char x);//将第x层的上面的块整体移动下来一层
void addscore();//在特定位置显示分数
void score();//记录分数并且刷新分数
void clr();//清空游戏区域
void lose();//判断是否结束并准备重新开始
int mmax(unsigned char a,unsigned char b,unsigned char c,unsigned char d);//辅助函数，找到四个数中的最大者
int mmin(unsigned char a,unsigned char b,unsigned char c,unsigned char d);//辅助函数，找到四个数中的最低者

#endif /* HANDLE_H_ */
