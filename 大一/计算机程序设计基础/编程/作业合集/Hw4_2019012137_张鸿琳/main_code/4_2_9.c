#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int k,n,i,j,a,b,c;
    a=1,b=1;
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
    if(k==0)
    {
        printf("结果为1。");
    }
    else
    {
        for(i=n-k+1;i<=n;i++)
        {
            a=a*i;
        }
        for(j=1;j<=k;j++)
        {
            b=b*j;
        }
        c=a/b;
        printf("结果为%d。",c);
    }
    return 0;
}
