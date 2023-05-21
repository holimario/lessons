#ifndef RATIONAL_H
#define RATIONAL_H


#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

typedef struct A_{int son;int mon;} RationalNumber;/*����������������˵����*/

RationalNumber GetRationalNumber();/*�������ķ�����Ϣ�������ʽΪ"a/b"*/


RationalNumber Simplify(RationalNumber p);/*�����Ļ���*/


RationalNumber SumRationalNumbers(RationalNumber a,RationalNumber b);/*�������Ӻ�*/


RationalNumber MinusRationalNumbers(RationalNumber a,RationalNumber b);/*���������,a-b*/


RationalNumber MutiplyRationalNumbers(RationalNumber a,RationalNumber b);/*���������*/


RationalNumber DivideRationalNumbers(RationalNumber a,RationalNumber b);/*�����������a/b*/


int FindMinCommonMultiple(int a,int b);/*��������������С������*/


int FindMaxCommonDivisor(int a,int b);/*���������������Լ��*/

#endif // RATIONAL_H
