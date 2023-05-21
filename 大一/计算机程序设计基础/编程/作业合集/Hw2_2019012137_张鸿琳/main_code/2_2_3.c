#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int a,i;
    a=1;
    printf(" Nine-by-nine Multiplication Table\n");
    printf(" --------------------------------------\n");
    printf("      1   2   3   4   5   6   7   8   9\n");
    printf(" --------------------------------------\n");
    while(a<=9)
    {
        for(i=0;i<=a;i++)
        {
            if(i==0)
                printf("%3d",a);
            else
                printf("%4d",i*a);
        }
        printf("\n");
        a+=1;
    }
    return 0;
}
