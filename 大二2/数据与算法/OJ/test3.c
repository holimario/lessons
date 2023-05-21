#include <stdio.h>
#include <stdlib.h>

int find(int n,int* a);

int main(){
    int N;
    int out;
    scanf("%d",&N);
    int* rock=malloc(N*sizeof(int));
    for(int k=0;k<=N-1;k++)
    {
        scanf("%d",&rock[k]);
    }
    out=find(N,rock);
    printf("%d",out);
    return 0;
}


int find(int n,int* rock)
{
    int N=n;
    int state=1;
    int now;
    int temp;
    int* a=malloc(N*sizeof(int));
    int* b=malloc(N*sizeof(int));
    for(int k=2;k<=N;k+=2)
    {
        if(state==1)
        {
            for(int i=0;i<=N-k;i++)
            {
                if(k==2)
                {
                    if(rock[i]>=rock[i+1])
                    {
                        a[i]=rock[i];
                    }
                    else
                    {
                        a[i]=rock[i+1];
                    }
                }
                else
                {
                    now=rock[i]+b[i+1];//第i+1个石头开头的k-2个石头集合
                    temp=rock[i]+b[i+2];
                    if(temp>now)
                    {
                        now=temp;
                    }
                    temp=rock[i+k-1]+b[i];
                    if(temp>now)
                    {
                        now=temp;
                    }
                    temp=rock[i+k-1]+b[i+1];
                    if(temp>now)
                    {
                        now=temp;
                    }
                    a[i]=now;
                }
            }
            state*=-1;
        }
        else if(state==-1)
        {
            for(int i=0;i<=N-k;i++)
            {
                now=rock[i]+a[i+1];//第i+1个石头开头的k-2个石头集合
                temp=rock[i]+a[i+2];
                if(temp>now)
                {
                    now=temp;
                }
                temp=rock[i+k-1]+a[i];
                if(temp>now)
                {
                    now=temp;
                }
                temp=rock[i+k-1]+a[i+1];
                if(temp>now)
                {
                    now=temp;
                }
                b[i]=now;
            }
            state*=-1;
        }
    }
    if(a[0]>b[0])
    {
        return a[0];
    }
    else
    {
        return b[0];
    }
}