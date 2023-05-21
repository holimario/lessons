#include <stdio.h>
#include "../library_code/zylib.h"
int cal(int k,int n);

int main()
{
    int k,n,c;
    printf("本程序可计算二项式系数C_n^k。\n");
    printf("请输入k:");
    k=GetIntegerFromKeyboard();
    if(k<0)
    {
        printf("请重新输入k：");
        k=GetIntegerFromKeyboard();
    }
    printf("请输入n:");
    n=GetIntegerFromKeyboard();
    if(n<=0||n<k)
    {
        printf("请重新输入n：");
        n=GetIntegerFromKeyboard();
    }
    c=cal(k,n);
    printf("结果为%d。",c);
    return 0;
}
int cal(int k,int n)
{
    if(k==0||k==n)
    {
        return 1;
    }
    else
    {
        return cal(k,n-1)+cal(k-1,n-1);
    }
}
