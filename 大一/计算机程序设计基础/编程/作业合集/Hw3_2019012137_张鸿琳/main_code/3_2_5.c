#include <stdio.h>
#include "../library_code/zylib.h"

void gcd(int x,int y);

int main()
{
    int x,y;
    printf("�����������������������ֵ����Լ����\n");
    printf("�������һ������:");
    x=GetIntegerFromKeyboard();
    printf("������ڶ�������:");
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
            printf("�������Լ��Ϊ��%d",i);
            break;
        }
        else
        {
            i--;
        }
    }

}
