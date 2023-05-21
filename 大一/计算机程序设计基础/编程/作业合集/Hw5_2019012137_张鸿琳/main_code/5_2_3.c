#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <time.h>
#include <stdlib.h>

int haha();

int main()
{
    int z,a,b,i,p;
    double t;
    STRING s,g,m;
    g="g";
    m="o";
    i=1;
    printf("本游戏第一回合由你坐庄，电脑充当闲家。庄家先掷骰子，如果闲家掷的点数不大于庄家，则判庄家赢。输者将在下一回合充当庄家先掷骰子。游戏不断重复，只有在你输入了“q”或“Q”之后才退出游戏。游戏结束时你将看到游戏回合数与胜率。\n");
    z=1;
    p=0;
    while(CompareString(m,"Q")!=0&&CompareString(m,"q")!=0)
    {
        a=haha();
        printf("本回合（第%d回合）庄家掷出的骰子点数为：%d\n",i,a);
        printf("请输入字符“g”来让闲家掷骰子：");
        s=GetStringFromKeyboard();
        if(CompareString(s,g)==0)
        {
            b=haha();
            printf("本回合（第%d回合）闲家掷出的骰子点数为：%d\n",i,b);
            if(a>=b)
            {
                if(z==0)
                {
                    printf("本回合你输了，下一回合你是庄家，电脑为闲家。\n");
                    z=1;
                }
                else
                {
                    printf("本回合你赢了，下一回合你是闲家，电脑为庄家。\n");
                    z=0;
                    p++;
                }
            }
            else
            {
                if(z==0)
                {
                    printf("本回合你赢了，下一回合你是闲家，电脑为庄家。\n");
                    z=0;
                    p++;
                }
                else
                {
                    printf("本回合你输了，下一回合你是庄家，电脑为闲家。\n");
                    z=1;
                }
            }
            i++;
            printf("请你决定是否退出（输入“q”或“Q”则退出）：");
            m=GetStringFromKeyboard();
        }
        else
        {
            printf("你没有输入“g”，想要退出吗？若要退出，请输入“q”或“Q”，否则将重新开始本轮游戏：");
            m=GetStringFromKeyboard();
        }

    }
    t=(double)p/(double)i;
    printf("你总共玩了%d回合，胜率为%lf。\n",i-1,t);
    if(t>=0.5)
    {
        printf("运气不错！");
    }
    else
    {
        printf("运气不太好哦！");
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
