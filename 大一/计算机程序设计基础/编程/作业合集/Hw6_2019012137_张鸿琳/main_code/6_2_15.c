#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <stdlib.h>

int main()
{
    int m,n,i,a,b,p,q,sum;
    STRING s;
    sum=0;
    typedef enum{_=0,X=-1,O=1}TICK_TACK_TOE;
    TICK_TACK_TOE tick_tack_toe_phase[3][3];
    printf("请依次连续输入棋局的九个位置信息（分别用“X”，“O”，“_”表示），本程序将会判定胜负：");
    s=GetStringFromKeyboard();
    m=0;
    i=0;
    while(m<=2)
    {
        n=0;
        while(n<=2)
        {
            if(GetIthChar(s,i)=='O')
            {
                tick_tack_toe_phase[m][n]=O;
            }
            else if(GetIthChar(s,i)=='X')
            {
                tick_tack_toe_phase[m][n]=X;
            }
            else
            {
                tick_tack_toe_phase[m][n]=_;
            }
            if(i<8)
            {
                i++;
            }
            n++;
        }
        m++;
    }
    a=0;
    printf("棋局为：\n");
    while(a<=2)
    {
        b=0;
        while(b<=2)
        {
            if(tick_tack_toe_phase[a][b]==O)
            {
                printf("O ");
            }
            else if(tick_tack_toe_phase[a][b]==X)
            {
                printf("X ");
            }
            else
            {
                printf("- ");
            }
            b++;
        }
        printf("\n");
        a++;
    }
    p=0,q=0;
    while(p<=2)
    {
        while(q<=2)
        {
            sum+=tick_tack_toe_phase[p][q];
            q++;
        }
        if(sum==3)
        {
            printf("执“O”的获胜。");
        }
        else if(sum==-3)
        {
            printf("执“X”的获胜。");
        }
        sum=0;
        p++;
    }
    p=0,q=0;
    while(p<=2)
    {
        while(q<=2)
        {
            sum+=tick_tack_toe_phase[q][p];
            q++;
        }
        if(sum==3)
        {
            printf("执“O”的获胜。");
        }
        else if(sum==-3)
        {
            printf("执“X”的获胜。");
        }
        sum=0;
        p++;
    }
    p=2,q=0;
    while(q<=2)
    {
        sum+=tick_tack_toe_phase[q][p];
        q++,p--;
    }
    if(sum==3)
        {
            printf("执“O”的获胜。");
        }
        else if(sum==-3)
        {
            printf("执“X”的获胜。");
        }
        sum=0;
    p=0,q=0;
    while(p<=2)
    {
        sum+=tick_tack_toe_phase[q][p];
        p++,q++;
    }
    if(sum==3)
        {
            printf("执“O”的获胜。");
        }
        else if(sum==-3)
        {
            printf("执“X”的获胜。");
        }
    return 0;
}
