#include <stdio.h>
#include "../library_code/zylib.h"
int haha(int x);

int main()
{
    int x,k;
    k=0;
    printf("请输入一个正整数，本程序会计算其各位数字之和：");
    x=GetIntegerFromKeyboard();
    while(x<=0)
    {
        printf("请重新输入：");
        x=GetIntegerFromKeyboard();
    }
    k=haha(x);
    printf("结果为%d",k);
    return 0;
}
int haha(int x)
{
    int i;
    i=0;
    if(x<10)
    {
        return x;
    }
    while(i<10)
    {
        if((x-i)%10==0)
        {
            return i+haha((x-i)/10);
        }
        else
        {
            i++;
        }
    }
}
