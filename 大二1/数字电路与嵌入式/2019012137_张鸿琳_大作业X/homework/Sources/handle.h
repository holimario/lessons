/*
 * handle.h
 *
 *  Created on: Jul 7, 2021
 *      Author: ����
 */

#ifndef HANDLE_H_
#define HANDLE_H_

unsigned char dtoa(unsigned char c1);//ת������
void Initlight();//��lightened������г�ʼ��
void ll(unsigned char x,unsigned char y);//light������ĳ��(lx,ly)����2*2�ĵ�λ�񣬷����ƶ���
void dd(unsigned char x,unsigned char y);//destroy��Ϩ��ĳ��(lx,ly)����2*2�ĵ�λ�񣬷����ƶ���
int crash0(unsigned char x,unsigned char y);//�����������ж�ĳ�����ص��Ƿ���Դﵽ
int crash(unsigned char x,unsigned char y);//�����������ж�һ������Ƿ�ᷢ����ײ
int testmove();//ģ�Ⲣ�ж��Ƿ���������ƶ�һ�����ص�
int testrrotate();//ģ��������ת���ж��Ƿ������ת
int testlrotate();//ģ��������ת���ж��Ƿ������ת
int testright();//ģ�Ⲣ�����Ƿ���������ƶ�һ����
int testleft();//ģ�Ⲣ�����Ƿ���������ƶ�һ����
void lighten(int k);//����ĳ�ֿ鲢�Ҽ�¼���ʼ��Ϣ������ֱ����dot���������������е�����
void getnext();//ˢ����һ���飬��ʾ���ض�λ��
void rrotate();//˳ʱ����ת����pos״̬�Ŀ�all
void lrotate();//��ʱ����ת����pos״̬�Ŀ�all
void right();//����һ����Ҳ���������������ص�
void left();//����һ����Ҳ���������������ص�
void move();//���������ڲ����Ŀ������ƶ�һ��
void above(unsigned char x);//����x�������Ŀ������ƶ�����һ��
void addscore();//���ض�λ����ʾ����
void score();//��¼��������ˢ�·���
void clr();//�����Ϸ����
void lose();//�ж��Ƿ������׼�����¿�ʼ
int mmax(unsigned char a,unsigned char b,unsigned char c,unsigned char d);//�����������ҵ��ĸ����е������
int mmin(unsigned char a,unsigned char b,unsigned char c,unsigned char d);//�����������ҵ��ĸ����е������

#endif /* HANDLE_H_ */
