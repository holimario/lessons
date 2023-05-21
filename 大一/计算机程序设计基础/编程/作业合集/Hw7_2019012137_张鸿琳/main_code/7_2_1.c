#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include "../library_code/dynarray.h"
#include <stdlib.h>

int average(int* q,int n)
{
    int i=1,sum=0;
    while(i<=n)
    {
        sum+=*q++;
        i++;
    }
    sum/=n;
    return sum;
}

int main()
{
    int n,i;
    printf("请输入数组元素个数：");
    n=GetIntegerFromKeyboard();
    int* a=malloc(n);
    for(i=1;i<=n;i++)
    {
        printf("第%d个数为:",i);
        a[i-1]=GetIntegerFromKeyboard();
    }
    printf("平均值为：%d",average(a,n));
    return 0;
}
