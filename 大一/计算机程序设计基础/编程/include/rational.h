#ifndef RATIONAL_H
#define RATIONAL_H


#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

typedef struct _A{int numerator;int denominator;} rat;/*�������Ϊ������������Ԫ�صĽṹ��*/

rat GetRationalNumberFromKeyborad()/*�����ʽΪ��n/m"*/


rat Simplify(rat a)/*�����Ļ���*/


rat SumRationalNumbers(rat a,rat b)/*�������Ӻ�*/


rat MinusRationalNumbers(rat a,rat b)/*�����������a-b��*/


rat MutiplyRationalNumbers(rat a,rat b)/*���������*/


rat MutiRationalNumbers(rat a,rat b)/*�����������a/b��*/


int FindMinCommonMultiple(int a,int b)/*��������������С������*/


int FindMaxCommonDivisor(int a,int b)/*���������������Լ��*/



#endif // RATIONAL_H
