#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

int main()
{
    int a;
    STRING s;
    printf("请输入一串英语字符串，系统将输出第一个元音字母的位置：");
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
    printf("第一个元音字母出现在第%d个字符的位置上。",a+1);
    return 0;
}
