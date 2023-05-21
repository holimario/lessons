#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <time.h>
#include <stdlib.h>


int main()
{
int i;
srand((int)time(NULL));
i=rand()%6;
i=i+1;
printf( "%d", i );
return 0;
}

