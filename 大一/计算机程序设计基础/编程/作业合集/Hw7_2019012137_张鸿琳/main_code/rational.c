#include "rational.h"


#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>




RationalNumber GetRationalNumber()/*�������ķ�����Ϣ�������ʽΪ"a/b"*/
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

RationalNumber Simplify(RationalNumber p)/*�����Ļ���*/
{
    RationalNumber q;
    q.son=p.son/FindMaxCommonDivisor(p.son,p.mon);
    q.mon=p.mon/FindMaxCommonDivisor(p.son,p.mon);
    return q;
}

RationalNumber SumRationalNumbers(RationalNumber a,RationalNumber b)/*�������Ӻ�*/
{
    RationalNumber q;
    q.mon=FindMinCommonMultiple(a.mon,b.mon);
    q.son=(a.mon*b.son+a.son*b.mon)/FindMaxCommonDivisor(a.mon,b.mon);
    q=Simplify(q);
    return q;
}

RationalNumber MinusRationalNumbers(RationalNumber a,RationalNumber b)/*���������,a-b*/
{
    RationalNumber q;
    q.mon=FindMinCommonMultiple(a.mon,b.mon);
    q.son=(a.son*b.mon-b.son*a.mon)/FindMaxCommonDivisor(a.mon,b.mon);
    q=Simplify(q);
    return q;
}

RationalNumber MutiplyRationalNumbers(RationalNumber a,RationalNumber b)/*���������*/
{
    RationalNumber q;
    q.son=a.son*b.son;
    q.mon=a.mon*b.mon;
    q=Simplify(q);
    return q;
}

RationalNumber DivideRationalNumbers(RationalNumber a,RationalNumber b)/*�����������a/b*/
{
    RationalNumber q;
    q.son=a.son*b.mon;
    q.mon=a.mon*b.son;
    q=Simplify(q);
    return q;
}

int FindMinCommonMultiple(int a,int b)/*��������������С������*/
{
    return a*b/FindMaxCommonDivisor(a,b);
}

int FindMaxCommonDivisor(int a,int b)/*���������������Լ��*/
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
