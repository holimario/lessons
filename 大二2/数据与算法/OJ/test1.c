#include <stdio.h>


int main(){
    int i;
    int flag=0;
    int s[100];
    int sum=0;
    scanf("%d",&i);
    if(i==0)
    {
        printf("10");
        return 0;
    }
    else if(i==1)
    {
        printf("1");
    }
    else
    {
        while(i!=1)
        {
            for(int k=9;k>=2;k--)
            {
                if(i%k==0)
                {
                    s[sum]=k;
                    sum++;
                    i=i/k;
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                printf("-1");
                return 0;
            }
            else
            {
                flag=0;
            }
        }
    }
    for(int x=sum-1;x>=0;x--)
    {
        printf("%d",s[x]);
    }
    return 0;
}