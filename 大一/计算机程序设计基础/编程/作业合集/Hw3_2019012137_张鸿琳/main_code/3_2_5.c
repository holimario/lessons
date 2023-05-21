#include <stdio.h>
#include "../library_code/zylib.h"

void gcd(int x,int y);

int main()
{
    int x,y;
    printf("本程序可求出您输入两个数字的最大公约数。\n");
    printf("请输入第一个数字:");
    x=GetIntegerFromKeyboard();
    printf("请输入第二个数字:");
    y=GetIntegerFromKeyboard();
    gcd(x,y);
    return 0;
}

void gcd(int x,int y)
{
    int i;
    if(x>y)
    {
        i=y;
    }
    else
    {
        i=x;
    }
    while(i>0)
    {
        if(x%i==0&&y%i==0)
        {
            printf("二者最大公约数为：%d",i);
            break;
        }
        else
        {
            i--;
        }
    }

}
