#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int a,b,c,e,f,g,h;
    printf("此程序会对您输入的两个整数进行加减乘除四则运算(其中除法为整除得余数）\n");
    printf("第一个整数在此输入：");
    scanf("%d",&a);
    printf("第二个整数在此输入：");
    scanf("%d",&b);
    c=a+b,e=a-b,f=a*b,g=a/b,h=a%b;
    printf("%d+%d=%d\n",a,b,c);
    printf("%d-%d=%d\n",a,b,e);
    printf("%d*%d=%d\n",a,b,f);
    printf("%d/%d=%d……%d\n",a,b,g,h);
    return 0;
}
