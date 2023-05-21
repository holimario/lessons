#include "rational.h"


#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

typedef struct _A{int numerator;int denominator;} rat;/*定义分数为含有两个整数元素的结构体*/

rat GetRationalNumberFromKeyborad()/*输入格式为“n/m"*/
{
    STRING s;
    rat q;
    int i,l;
    s=GetStringFromKeyboard();
    l=GetStringLength(s);
    i=FindCharFirst('/',s);
    q.numerator=TransformStringIntoInteger(GetSubString(s,0,i-1));
    q.denominator=TransformStringIntoInteger(GetSubString(s,i-1,l-1));
    return q;
}

rat Simplify(rat a)/*分数的化简*/
{
    rat q;
    q.denominator=a.denominator/FindMaxCommonDivisor(a.denominator,a.numerator);
    q.numerator=a.numerator/FindMaxCommonDivisor(a.denominator,a.numerator);
    return q;
}

rat SumRationalNumbers(rat a,rat b)/*有理数加和*/
{
    rat q;
    q.denominator=FindMinCommonMultiple(a.denominator,b.denominator);
    q.numerator=(a.numerator*b.denominator+b.numerator*a.denominator)/FindMaxCommonDivisor(a.denominator,b.denominator);
    q=Simplify(q);
    return q;
}

rat MinusRationalNumbers(rat a,rat b)/*有理数相减“a-b”*/
{
    rat q;
    q.denominator=FindMinCommonMultiple(a.denominator,b.denominator);
    q.numerator=(a.numerator*b.denominator-b.numerator*a.denominator)/FindMaxCommonDivisor(a.denominator,b.denominator);
    q=Simplify(q);
    return q;
}

rat MutiplyRationalNumbers(rat a,rat b)/*有理数相乘*/
{
    rat q;
    q.denominator=a.denominator*b.denominator;
    q.numerator=a.numerator*b.numerator;
    q=Simplify(q);
    return q;
}

rat MutiRationalNumbers(rat a,rat b)/*有理数相除“a/b”*/
{
    rat q;
    q.denominator=a.denominator*b.numerator;
    q.numerator=a.numerator*b.denominator;
    q=Simplify(q);
    return q;
}

int FindMinCommonMultiple(int a,int b)/*辅助函数，求最小公倍数*/
{
    return a*b/FindMaxCommonDivisor(a,b);
}

int FindMaxCommonDivisor(int a,int b)/*辅助函数，求最大公约数*/
{
    int i;
    if(a>=b)
    {
        for(i=b;i>=1;i--)
        {
            if(a%i==0&&b%i==0)
            {
                return i;
            }
        }
    }
    else
    {
        for(i=a;i>=1;i--)
        {
            if(a%i==0&&b%i==0)
            {
                return i;
            }
        }
    }
}
