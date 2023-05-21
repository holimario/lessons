#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    double a,b,c;
    printf("此程序计算一年期满后本金与利息总额。\n");
    printf("请输入您一年期定期存款金额(单位为人民币）；");
    scanf("%lf",&a);
    printf("请输入按照百分比格式表示的一年期定期存款利率（无需输入百分号）：");
    scanf("%lf",&b);
    c=a*(1+b/100);
    printf("您一年期满后本金与利息总额为：%lf",c);
    return 0;
}
