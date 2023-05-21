#include "rational.h"


#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>




RationalNumber GetRationalNumber()/*获得输入的分数信息，输入格式为"a/b"*/
{
    STRING s;
    int i,l;
    RationalNumber q;
    s=GetStringFromKeyboard();
    l=GetStringLength(s);
    i=FindCharFirst('/',s);
    q.son=TransformStringIntoInteger(GetSubString(s,0,i));
    q.mon=TransformStringIntoInteger(GetSubString(s,i+1,l-1));
    return q;
}

RationalNumber Simplify(RationalNumber p)/*分数的化简*/
{
    RationalNumber q;
    q.son=p.son/FindMaxCommonDivisor(p.son,p.mon);
    q.mon=p.mon/FindMaxCommonDivisor(p.son,p.mon);
    return q;
}

RationalNumber SumRationalNumbers(RationalNumber a,RationalNumber b)/*有理数加和*/
{
    RationalNumber q;
    q.mon=FindMinCommonMultiple(a.mon,b.mon);
    q.son=(a.mon*b.son+a.son*b.mon)/FindMaxCommonDivisor(a.mon,b.mon);
    q=Simplify(q);
    return q;
}

RationalNumber MinusRationalNumbers(RationalNumber a,RationalNumber b)/*有理数相减,a-b*/
{
    RationalNumber q;
    q.mon=FindMinCommonMultiple(a.mon,b.mon);
    q.son=(a.son*b.mon-b.son*a.mon)/FindMaxCommonDivisor(a.mon,b.mon);
    q=Simplify(q);
    return q;
}

RationalNumber MutiplyRationalNumbers(RationalNumber a,RationalNumber b)/*有理数相乘*/
{
    RationalNumber q;
    q.son=a.son*b.son;
    q.mon=a.mon*b.mon;
    q=Simplify(q);
    return q;
}

RationalNumber DivideRationalNumbers(RationalNumber a,RationalNumber b)/*有理数相除，a/b*/
{
    RationalNumber q;
    q.son=a.son*b.mon;
    q.mon=a.mon*b.son;
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
