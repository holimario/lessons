#include <stdio.h>
#include "../library_code/zylib.h"

void IsPrime( int n );

int main()
{
    int n;
    printf("������һ������2������:");
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
            printf("%d ��������\n",n);
            break;
        }
        else if(n%i==0)
        {
            printf("%d ����������\n",n);
            break;
        }
        else
        {
            i++;
        }
    }
}
