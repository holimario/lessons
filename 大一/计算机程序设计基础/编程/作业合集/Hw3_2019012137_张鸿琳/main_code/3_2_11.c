#include <stdio.h>
#include "../library_code/zylib.h"

void calender(int y,int m);
int days(int y,int m);
int bol(int t);
int dayss(int t,int y);

int main()
{
    int y,m;
    printf("输入年份：");
    y=GetIntegerFromKeyboard();
    printf("\n");
    printf("输入月份：");
    m=GetIntegerFromKeyboard();
    printf("\n");
    calender(y,m);
    return 0;;
}
void calender(int y,int m)
{
    int i,h,p;
    h=1,p=1;
    printf("Calendar %d-%d\n",y,m);
    printf("--------------------------\n");
    printf("Su  Mo  Tu  We  Th  Fr  Sa\n");
    printf("--------------------------\n");
    i=days(y,m);
    while(p<i)
    {
        printf("    ");
        p++;
    }
    while(h<=dayss(m,y))
    {
        printf("%2d  ",h);
        i++;
        h++;
        if(i==8)
        {
            printf("\n");
            i=1;
        }
    }
}
int days(int y,int m)
{
    int k,t;
    t=2015;
    while(t<y)
    {
        k+=(365+bol(t));
        t++;
    }
    t=1;
    while(t<m)
    {
        k+=dayss(t,y);
        t++;
    }
    return k%7+4;
}
int bol(int t)
{
    if((t%4==0&&t%100!=0)||t%400==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int dayss(int t,int y)
{
    switch(t)
    {
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:return 31;
        case 4:case 6:case 9:case 11:return 30;
        case 2:return 28+bol(y);
    }
}
