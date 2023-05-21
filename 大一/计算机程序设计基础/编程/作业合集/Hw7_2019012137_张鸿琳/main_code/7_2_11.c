#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int strcmp2(char *a,char *b)/*a[]比b[]靠前则返回-1，反之，返回1，相等则返回0*/
{
    int i;
    for(i=1;i<=strlen(a)&&i<=strlen(b);i++)
    {
        if(a[i-1]>b[i-1])
        {
            return 1;
        }
        else if(a[i-1]<b[i-1])
        {
            return -1;
        }
    }
    return 0;
}

int main()
{
    char *a="A",*b="A";
    int p;
    p=strcmp2(a,b);
    printf("%d",p);
    return 0;

}

