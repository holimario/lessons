#include <stdio.h>
#include "../library_code/zylib.h"
int cal(int k,int n);

int main()
{
    int k,n,c;
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
    c=cal(k,n);
    printf("���Ϊ%d��",c);
    return 0;
}
int cal(int k,int n)
{
    if(k==0||k==n)
    {
        return 1;
    }
    else
    {
        return cal(k,n-1)+cal(k-1,n-1);
    }
}
