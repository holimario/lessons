#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <time.h>
#include <stdlib.h>

int haha();

int main()
{
    int a,b;
    STRING s,g;
    g="g";
    printf("����Ϸ�����ɵ��������ӣ������û������ַ���g�������ӣ��Ƚϴ�С�����߻�ʤ��\n");
    a=haha();
    printf("�������������ӵ���Ϊ��%d",a);
    printf("\n");
    printf("�������ַ���g���������ӣ�");
    s=GetStringFromKeyboard();
    if(CompareString(s,g)==0)
    {
        b=haha();
        printf("�����������ӵ���Ϊ��%d",b);
        printf("\n");
        if(a>b)
        {
            printf("�����ˡ�");
        }
        else if(a<b)
        {
            printf("��Ӯ�ˡ�");
        }
        else
        {
            printf("ƽ�֣�");
        }
    }
    else
    {
        printf("��Ϸ������");
    }
    return 0;
}

int haha()
{
int i;
srand((int)time(NULL));
i=rand()%6;
return i+1;
}
