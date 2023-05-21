#ifndef RATIONAL_H
#define RATIONAL_H


#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

typedef struct _A{int numerator;int denominator;} rat;/*定义分数为含有两个整数元素的结构体*/

rat GetRationalNumberFromKeyborad()/*输入格式为“n/m"*/


rat Simplify(rat a)/*分数的化简*/


rat SumRationalNumbers(rat a,rat b)/*有理数加和*/


rat MinusRationalNumbers(rat a,rat b)/*有理数相减“a-b”*/


rat MutiplyRationalNumbers(rat a,rat b)/*有理数相乘*/


rat MutiRationalNumbers(rat a,rat b)/*有理数相除“a/b”*/


int FindMinCommonMultiple(int a,int b)/*辅助函数，求最小公倍数*/


int FindMaxCommonDivisor(int a,int b)/*辅助函数，求最大公约数*/



#endif // RATIONAL_H
