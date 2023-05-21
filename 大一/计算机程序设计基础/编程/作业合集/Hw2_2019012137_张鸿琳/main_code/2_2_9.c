#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int i;
    i=1;
    printf("Calendar 2015-05\n");
    printf("--------------------------\n");
    printf("Su  Mo  Tu  We  Th  Fr  Sa\n");
    printf("--------------------------\n");
    printf("                    ");
    while(i<=31)
    {
        if(i==2||i==9||i==16||i==23||i==30||i==31)
            printf("%2d\n",i);
        else
            printf("%2d  ",i);
        i++;
    }
    printf("--------------------------");
    return 0;
}
