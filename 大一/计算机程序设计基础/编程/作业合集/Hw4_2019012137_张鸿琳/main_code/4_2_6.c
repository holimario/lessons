#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int n,i,S;
    S=0;
    printf("请输入一个非零自然数：");
    n=GetIntegerFromKeyboard();
    while(n<=0)
    {
        printf("请重新输入：");
        n=GetIntegerFromKeyboard();
    }
    for(i=1;i<n-1;i++)
    {
        if(n%i==0)
        {
            S+=i;
        }
    }
    if(S==n)
    {
        printf("%d是完数。\n",n);
    }
    else
    {
        printf("%d不是完数。\n",n);
    }
    return 0;
}
