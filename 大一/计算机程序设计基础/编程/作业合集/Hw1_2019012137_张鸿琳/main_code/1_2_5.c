#include <stdio.h>
#include "../library_code/zylib.h"

int main()
{
    double a,b,c;
    printf("�˳������һ�������󱾽�����Ϣ�ܶ\n");
    printf("��������һ���ڶ��ڴ����(��λΪ����ң���");
    scanf("%lf",&a);
    printf("�����밴�հٷֱȸ�ʽ��ʾ��һ���ڶ��ڴ�����ʣ���������ٷֺţ���");
    scanf("%lf",&b);
    c=a*(1+b/100);
    printf("��һ�������󱾽�����Ϣ�ܶ�Ϊ��%lf",c);
    return 0;
}
