#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include <time.h>
#include <stdlib.h>

int haha();

int main()
{
    int z,a,b,i,p;
    double t;
    STRING s,g,m;
    g="g";
    m="o";
    i=1;
    printf("����Ϸ��һ�غ�������ׯ�����Գ䵱�мҡ�ׯ���������ӣ�����м����ĵ���������ׯ�ң�����ׯ��Ӯ�����߽�����һ�غϳ䵱ׯ���������ӡ���Ϸ�����ظ���ֻ�����������ˡ�q����Q��֮����˳���Ϸ����Ϸ����ʱ�㽫������Ϸ�غ�����ʤ�ʡ�\n");
    z=1;
    p=0;
    while(CompareString(m,"Q")!=0&&CompareString(m,"q")!=0)
    {
        a=haha();
        printf("���غϣ���%d�غϣ�ׯ�����������ӵ���Ϊ��%d\n",i,a);
        printf("�������ַ���g�������м������ӣ�");
        s=GetStringFromKeyboard();
        if(CompareString(s,g)==0)
        {
            b=haha();
            printf("���غϣ���%d�غϣ��м����������ӵ���Ϊ��%d\n",i,b);
            if(a>=b)
            {
                if(z==0)
                {
                    printf("���غ������ˣ���һ�غ�����ׯ�ң�����Ϊ�мҡ�\n");
                    z=1;
                }
                else
                {
                    printf("���غ���Ӯ�ˣ���һ�غ������мң�����Ϊׯ�ҡ�\n");
                    z=0;
                    p++;
                }
            }
            else
            {
                if(z==0)
                {
                    printf("���غ���Ӯ�ˣ���һ�غ������мң�����Ϊׯ�ҡ�\n");
                    z=0;
                    p++;
                }
                else
                {
                    printf("���غ������ˣ���һ�غ�����ׯ�ң�����Ϊ�мҡ�\n");
                    z=1;
                }
            }
            i++;
            printf("��������Ƿ��˳������롰q����Q�����˳�����");
            m=GetStringFromKeyboard();
        }
        else
        {
            printf("��û�����롰g������Ҫ�˳�����Ҫ�˳��������롰q����Q�����������¿�ʼ������Ϸ��");
            m=GetStringFromKeyboard();
        }

    }
    t=(double)p/(double)i;
    printf("���ܹ�����%d�غϣ�ʤ��Ϊ%lf��\n",i-1,t);
    if(t>=0.5)
    {
        printf("��������");
    }
    else
    {
        printf("������̫��Ŷ��");
    }
    return 0;
}

int haha()
{
int i;
srand((int)time(NULL));
i=rand()%6;
return i+1;
}
