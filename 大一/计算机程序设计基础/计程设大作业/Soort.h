#ifndef SOORT_H
#define SOORT_H
#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include "../library_code/dynarray.h"
#include <stdlib.h>

int Login();/*��¼�����������ж��Ƿ�ɹ���¼�����û����Ƿ���ں����Ӧ�����Ƿ���ȷ*/


int Menu();/*�ڳɹ���¼����ʾ���˵�����*/

int Menu1();/*�ڳɹ���¼��ѡ���ѯѡ���������ʱ����ʾ�˵��ĺ���*/


void BacktoMenu(int h);/*���һ�β������ж��Ƿ񷵻����˵�*/


void Select(int t);/*ѡ�β��������������ж�ѡ���Ƿ�����Լ���ѡ����Ϣ����ѡ����Ϣ�ļ�*/

void SearchI(int t);/*��ѯ������Ϣ*/

void SearchAll(int id);/*��ѯ������Ϣ*/


void Sort1();/*��ѯѡ��������*/

void Sort2();/*��ѯ��ѧ����ѧ������ֻ��ʾ��ǰ��ѡ��ѧ����*/


void Sort3();/*��ѯ������Ů����ӭ�γ�*/


void Sort31();


void Sort32();


int Whether(STRING* q,STRING s,int o);/*ѡ�β��������ĸ��������������û���������ݣ�ת��Ϊ������Ϣ,Ҳ������Ŀ��Ʋ���*/


int CopyOut(int i,STRING q);


void CopyIn(int j);


void ChangeSortAll(int id,int sex,int z);/*�ı�ԭ����¼������*/


int Detect(int id);/*����Ƿ��������й�ѡ�β���*/


void SortI(STRING* a,int sum,int t,int i);/*����Ϣ���뵽ѧ��ѡ����Ϣ�ļ���*/


void SortAll(STRING* q,int sex,int i);/*����Ϣ���뵽ѡ����Ϣ�����ļ���*/


void SortAll2(STRING* a,int sex,int i);


void IF(int t);



#endif // SOORT_H
