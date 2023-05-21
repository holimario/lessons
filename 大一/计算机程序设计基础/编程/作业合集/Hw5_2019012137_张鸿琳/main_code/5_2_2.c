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
    printf("此游戏首先由电脑掷骰子，再由用户输入字符“g”掷骰子，比较大小，大者获胜。\n");
    a=haha();
    printf("电脑掷出的骰子点数为：%d",a);
    printf("\n");
    printf("请输入字符“g”以掷骰子：");
    s=GetStringFromKeyboard();
    if(CompareString(s,g)==0)
    {
        b=haha();
        printf("你掷出的骰子点数为：%d",b);
        printf("\n");
        if(a>b)
        {
            printf("你输了。");
        }
        else if(a<b)
        {
            printf("你赢了。");
        }
        else
        {
            printf("平局！");
        }
    }
    else
    {
        printf("游戏结束。");
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
