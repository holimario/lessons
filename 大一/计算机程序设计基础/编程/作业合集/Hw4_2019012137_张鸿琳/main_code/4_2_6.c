#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int n,i,S;
    S=0;
    printf("������һ��������Ȼ����");
    n=GetIntegerFromKeyboard();
    while(n<=0)
    {
        printf("���������룺");
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
        printf("%d��������\n",n);
    }
    else
    {
        printf("%d����������\n",n);
    }
    return 0;
}
