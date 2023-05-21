#ifndef RATIONAL_H
#define RATIONAL_H


#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

typedef struct A_{int son;int mon;} RationalNumber;/*定义有理数，或者说分数*/

RationalNumber GetRationalNumber();/*获得输入的分数信息，输入格式为"a/b"*/


RationalNumber Simplify(RationalNumber p);/*分数的化简*/


RationalNumber SumRationalNumbers(RationalNumber a,RationalNumber b);/*有理数加和*/


RationalNumber MinusRationalNumbers(RationalNumber a,RationalNumber b);/*有理数相减,a-b*/


RationalNumber MutiplyRationalNumbers(RationalNumber a,RationalNumber b);/*有理数相乘*/


RationalNumber DivideRationalNumbers(RationalNumber a,RationalNumber b);/*有理数相除，a/b*/


int FindMinCommonMultiple(int a,int b);/*辅助函数，求最小公倍数*/


int FindMaxCommonDivisor(int a,int b);/*辅助函数，求最大公约数*/

#endif // RATIONAL_H
