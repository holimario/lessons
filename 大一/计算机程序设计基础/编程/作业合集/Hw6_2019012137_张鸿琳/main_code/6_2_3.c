#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

int main()
{
    int a;
    STRING s;
    printf("������һ��Ӣ���ַ�����ϵͳ�������һ��Ԫ����ĸ��λ�ã�");
    s=GetStringFromKeyboard();
    a=FindCharFirst('a',s);
    if(a>FindCharFirst('e',s))
    {
        a=FindCharFirst('e',s);
    }
    if(a>FindCharFirst('i',s))
    {
        a=FindCharFirst('i',s);
    }
    if(a>FindCharFirst('o',s))
    {
        a=FindCharFirst('o',s);
    }
    if(a>FindCharFirst('u',s))
    {
        a=FindCharFirst('u',s);
    }
    printf("��һ��Ԫ����ĸ�����ڵ�%d���ַ���λ���ϡ�",a+1);
    return 0;
}
