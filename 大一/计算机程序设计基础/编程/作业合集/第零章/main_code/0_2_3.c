#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    int a,b,c,e,f,g,h;
    printf("�˳�����������������������мӼ��˳���������(���г���Ϊ������������\n");
    printf("��һ�������ڴ����룺");
    scanf("%d",&a);
    printf("�ڶ��������ڴ����룺");
    scanf("%d",&b);
    c=a+b,e=a-b,f=a*b,g=a/b,h=a%b;
    printf("%d+%d=%d\n",a,b,c);
    printf("%d-%d=%d\n",a,b,e);
    printf("%d*%d=%d\n",a,b,f);
    printf("%d/%d=%d����%d\n",a,b,g,h);
    return 0;
}
