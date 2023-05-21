#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    STRING a,b,c,d,e;
    double ar1,ar2,ar3,ar4,ar5;
    double po1,po2,po3,po4,po5;
    double gd1,gd2,gd3,gd4,gd5;
    a="China",b="Iceland",c="India",d="Madagascar",e="Maldive";
    ar1=960.00,ar2=10.30,ar3=297.47,ar4=62.70,ar5=0.03;
    po1=135700.00,po2=32.30,po3=125200.00,po4=2292.00,po5=34.50;
    gd1=9240.00,gd2=15.33,gd3=1877.00,gd4=10.61,gd5=2.30;
    printf("---------------------------------------------------\n");
    printf("COUNTRY     AREA(10K km2)  POP.(10K)  GDP(Billion$)\n");
    printf("---------------------------------------------------\n");
    printf("%-12.12s %12.2lf %10.2lf  %-12.2lf\n",a,ar1,po1,gd1);
    printf("%-12.12s %12.2lf %10.2lf  %-12.2lf\n",b,ar2,po2,gd2);
    printf("%-12.12s %12.2lf %10.2lf  %-12.2lf\n",c,ar3,po3,gd3);
    printf("%-12.12s %12.2lf %10.2lf  %-12.2lf\n",d,ar4,po4,gd4);
    printf("%-12.12s %12.2lf %10.2lf  %-12.2lf\n",e,ar5,po5,gd5);
    return 0;
}
