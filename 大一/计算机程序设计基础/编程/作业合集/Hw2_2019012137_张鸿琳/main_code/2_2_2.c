#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int n,m,a,i;
    a=1;
    printf("�������ӡ������");
    n=GetIntegerFromKeyboard();
    printf("������ո�����");
    m=GetIntegerFromKeyboard();
    while(TRUE)
    {
        printf("%*s",2*n-1-a,"");
        for(i=0;i<a;i++)
        {
            printf("*");
        }
        printf("%*s",m,"");
        for(i=0;i<2*n-a;i++)
        {
            printf("*");
        }
        printf("\n");
        a+=2;
        if(a>2*n-1)
            break;
    }
    return 0;
}
