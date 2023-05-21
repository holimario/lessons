#include <stdio.h>
#include "../library_code/zylib.h"

void IsPrime( int n );

int main()
{
    int n;
    printf("请输入一个大于2的整数:");
    scanf("%d",&n);
    IsPrime(n);
    return 0;
}

void IsPrime( int n )
{
    int i;
    i=2;
    while(i<=n)
    {
        if(i==n)
        {
            printf("%d 是素数。\n",n);
            break;
        }
        else if(n%i==0)
        {
            printf("%d 不是素数。\n",n);
            break;
        }
        else
        {
            i++;
        }
    }
}
