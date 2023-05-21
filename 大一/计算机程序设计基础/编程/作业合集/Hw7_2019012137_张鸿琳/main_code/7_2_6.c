#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include "../library_code/dynarray.h"
#include <stdlib.h>

void transpose(int* q,int n)
{
    int a[n][n];
    int w,u;
    int* t=q;
    for(w=0;w<n;w++)
    {
        for(u=0;u<n;u++)
        {
            a[w][u]=*t;
            t++;
        }
    }
    t=q;
    for(w=0;w<n;w++)
    {
        for(u=0;u<n;u++)
        {
            *t=a[u][w];
            t++;
        }
    }
}

int main()
{
    int n,i,max,min,w,u;
    int* q;
    printf("请输入矩阵的行数（列数）：");
    n=GetIntegerFromKeyboard();
    printf("请输入矩阵元素的最大值：");
    max=GetIntegerFromKeyboard();
    printf("请输入矩阵元素的最小值：");
    min=GetIntegerFromKeyboard();
    q=malloc(n*n);
    srand(time(NULL));
    for(i=0;i<n*n;i++)
    {
        *q=GenerateRandomNumber(min,max);
        q++;
    }
    printf("随机产生的矩阵为：\n");
    q=q-n*n;
    for(w=0;w<n;w++)
    {
        for(u=0;u<n;u++)
        {
            printf("%d ",*q);
            q++;
        }
        printf("\n");
    }
    printf("转置矩阵为：\n");
    q=q-n*n;
    transpose(q,n);
    for(w=0;w<n;w++)
    {
        for(u=0;u<n;u++)
        {
            printf("%d ",*q);
            q++;
        }
        printf("\n");
    }
    return 0;
}
