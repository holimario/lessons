#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int k,n,i,j,a,b,c;
    a=1,b=1;
    printf("������ɼ������ʽϵ��C_n^k��\n");
    printf("������k:");
    k=GetIntegerFromKeyboard();
    if(k<0)
    {
        printf("����������k��");
        k=GetIntegerFromKeyboard();
    }
    printf("������n:");
    n=GetIntegerFromKeyboard();
    if(n<=0||n<k)
    {
        printf("����������n��");
        n=GetIntegerFromKeyboard();
    }
    if(k==0)
    {
        printf("���Ϊ1��");
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
        printf("���Ϊ%d��",c);
    }
    return 0;
}
