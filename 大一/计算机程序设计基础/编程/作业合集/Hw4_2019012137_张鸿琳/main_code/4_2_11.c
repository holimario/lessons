#include <stdio.h>
#include "../library_code/zylib.h"
int haha(int x);

int main()
{
    int x,k;
    k=0;
    printf("������һ�����������������������λ����֮�ͣ�");
    x=GetIntegerFromKeyboard();
    while(x<=0)
    {
        printf("���������룺");
        x=GetIntegerFromKeyboard();
    }
    k=haha(x);
    printf("���Ϊ%d",k);
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
