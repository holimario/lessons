#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <time.h>
#include <stdlib.h>

int main()
{
    int a[30],i;
    i=0;
    srand(time(NULL));
    srand(rand());
    srand(rand());
    srand(rand());
    while(i<30)
    {
        a[i]=rand()%90+10;
        printf("%d ",a[i]);
        i++;
    }
    return 0;
}
