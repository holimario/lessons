#include "Soort.h"

#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include "../library_code/dynarray.h"
#include <stdlib.h>

int Login()/*��¼�����������ж��Ƿ�ɹ���¼�����û����Ƿ���ں����Ӧ�����Ƿ���ȷ*/
{
    int a,b,k,sex;
    char* pp;
    FILE* fp;
    printf("ѧ�ţ�");
    a=GetIntegerFromKeyboard();
    printf("���룺");
    b=GetIntegerFromKeyboard();
    fp=fopen("student_information.csv","r");/*��ѧ����Ϣ�ļ�*/
    fseek(fp,23L,0);
    fscanf(fp,"%d",&k);
    while(k!=0)/*�����û���*/
    {
        if(a==k)
        {
            fseek(fp,1L,1);
            fscanf(fp,"%d",&k);
            if(b==k)/*��������Ƿ���ȷ*/
            {
                fseek(fp,1L,1);
                fscanf(fp,"%d",&sex);
                system("cls");
                fclose(fp);
                return a*sex;
            }
            else
            {
                system("cls");
                return 0;
            }
        }
        fscanf(fp,"%s",&pp);
        fseek(fp,4L,1);
        fscanf(fp,"%d",&k);
    }
    system("cls");
    fclose(fp);
    return 0;
}

int Menu()/*�ڳɹ���¼����ʾ���˵�����*/
{
    int i;
    printf("-------------------\n");
    printf("1.ѡ�β���\n");
    printf("2.��ѯ����ѡ����Ϣ\n");
    printf("3.��ѯ����ѡ����Ϣ\n");
    printf("-------------------\n");
    printf("��ѡ����Ĳ�����");
    i=GetIntegerFromKeyboard();
    return i;
}

int Menu1()/*�ڳɹ���¼��ѡ���ѯѡ���������ʱ����ʾ�˵��ĺ���*/
{
    int i;
    printf("---------------------------------------------\n");
    printf("1.��ѯѡ��������\n");
    printf("2.��ѯ��ѧ����ѧ������ֻ��ʾ��ǰ��ѡ��ѧ����\n");
    printf("3.��ѯ������Ů����ӭ�γ�\n");
    printf("---------------------------------------------\n");
    printf("��ѡ����Ĳ�����");
    i=GetIntegerFromKeyboard();
    return i;
}

void BacktoMenu(int h)/*���һ�β������ж��Ƿ񷵻����˵�*/
{
    int t;
    printf("�Ƿ�Ҫ�������˵�����������������1����");
    t=GetIntegerFromKeyboard();
    if(t==1)
    {
        system("cls");
        IF(h);
    }
    else
    {
        exit(0);
    }
}

void Select(int t)/*ѡ�β��������������ж�ѡ���Ƿ�����Լ���ѡ����Ϣ����ѡ����Ϣ�ļ�*/
{
    STRING s;
    STRING* a=NewObject(STRING*);
    int i;
    while(i!=0){
    printf("��������Ҫѡ�Ŀγ̣�������������γ̣��м��ö����������");
    s=GetStringFromKeyboard();
    i=Whether(a,s,t);
    if(i==1)
    {
        printf("ѡ���������ó���6�ţ�");
    }
    if(i==-1)
    {
        printf("ѧ���������õ���12��");
    }
    if(i==-2)
    {
        printf("����Ŀγ���������");
    }
    if(i==2)
    {
        printf("����Ŀγ��ظ���");
    }
    }
}

void SearchI(int t)/*��ѯ������Ϣ*/
{
    FILE* dp;
    int k,m,n,tt;
    STRING s;
    s=NewObject(STRING);
    dp=fopen("Ichoice.txt","r");
    if(t<0)
    {
        tt=-t;
    }
    else
    {
        tt=t;
    }
    while(feof(dp)==0)
    {
        fscanf(dp,"%d,%d,%d,",&k,&m,&n);
        fscanf(dp,"%s",s);
        if(k==tt)
        {
            printf("����ѡ�γ�Ϊ��%s\n",s);
            printf("�ܿγ���Ϊ��%d\n",m);
            printf("��ѧ��Ϊ��%d\n",n);
            BacktoMenu(t);
        }
    }
    fclose(dp);
    printf("�㻹û�н���ѡ�β������޷���ѯ��\n");
    BacktoMenu(t);
}

void SearchAll(int id)/*��ѯ������Ϣ*/
{
    int i;
    system("cls");
    i=Menu1();
    switch(i)
    {
        case 1:Sort1();break;
        case 2:Sort2();break;
        case 3:Sort3();break;
    }
    BacktoMenu(id);
}

void Sort1()/*��ѯѡ��������*/
{
    FILE* kp;
    STRING* p[100];
    int k=0,t,mi,c,all,a,b,n=1,h;
    int* i;
    STRING z;
    z=NewObject(STRING);
    i=NewObject(int*);
    p[0]=DuplicateString("A");
    while(TRUE)
    {
        p[n]=DuplicateString(TransformCharIntoString('A'+n));/*����Ϊ�˷���ֱ��ʹ���˴��ţ�û��ɨ���ļ�*/
        if(CompareString(p[n],"Z")==0)
        {
            break;
        }
        n++;
    }
    kp=fopen("Allchoice.csv","r");
    while(feof(kp)==0)
    {
        fscanf(kp,"%d,%d,",&a,&b);
        i[k]=a+b;
        k++;
    }
    fclose(kp);
    k=k-1;
    all=k;
    for(k=k-1;k>0;k--)
    {
        mi=i[0];
        z=DuplicateString(p[0]);
        c=0;
        for(t=0;t<=k;t++)
        {
            if(mi>=i[t])
            {
                mi=i[t];
                z=DuplicateString(p[t]);
                c=t;
            }
        }
        i[c]=i[k];
        p[c]=DuplicateString(p[k]);
        i[k]=mi;
        p[k]=DuplicateString(z);
    }
    printf("�γ�  ѡ����\n");
    for(t=0;t<all;t++)
    {
        printf("%s    %-d\n",p[t],i[t]);
    }
}

void Sort2()/*��ѯ��ѧ����ѧ������ֻ��ʾ��ǰ��ѡ��ѧ����*/
{
    FILE* fp;
    int* a;
    int h[1000];/*�����ﱾ��ʹ�ö�̬���飬���ǳ�����ĳ�ֺ��ѵ��͵�bug���������ʹ����1000��Ϊ���ޣ��ޣ�*/
    int c,i=0,ma,z,t,k;
    STRING s;
    s=NewObject(STRING);
    a=NewObject(int*);
    fp=fopen("Ichoice.txt","r");
    while(feof(fp)==0)
    {
        fscanf(fp,"%d,%d,%d,",&a[i],&c,&h[i]);
        fscanf(fp,"%s",s);
        i++;
    }
    for(k=i-2;k>0;k--)
    {
        ma=h[0];
        z=a[0];
        c=0;
        for(t=0;t<=k;t++)
        {
            if(ma<=h[t])
            {
                ma=h[t];
                z=a[t];
                c=t;
            }
        }
        h[c]=h[k];
        a[c]=a[k];
        h[k]=ma;
        a[k]=z;
    }
    printf("ѧ��  ��ѧ��\n");
    for(k=0;k<i-1;k++)
    {
        printf("%-3d     %-d\n",a[k],h[k]);
    }
}

void Sort3()/*��ѯ������Ů����ӭ�γ�*/
{
    int w;
    printf("��ѯ���������롰1������ѯŮ�������롰2����");
    w=GetIntegerFromKeyboard();
    if(w==1)
    {
        Sort31();
    }
    if(w==2)
    {
        Sort32();
    }
}

void Sort31()
{
    FILE* kp;
    STRING* p[100];
    int k=0,t,mi,c,all,a,b,n=1,h;
    int* i;
    STRING z;
    z=NewObject(STRING);
    i=NewObject(int*);
    p[0]=DuplicateString("A");
    while(TRUE)
    {
        p[n]=DuplicateString(TransformCharIntoString('A'+n));/*����Ϊ�˷���ֱ��ʹ���˴��ţ�û��ɨ���ļ�*/
        if(CompareString(p[n],"Z")==0)
        {
            break;
        }
        n++;
    }
    kp=fopen("Allchoice.csv","r");
    while(feof(kp)==0)
    {
        fscanf(kp,"%d,%d,",&a,&b);
        i[k]=a;
        k++;
    }
    fclose(kp);
    k=k-1;
    all=k;
    for(k=k-1;k>0;k--)
    {
        mi=i[0];
        z=DuplicateString(p[0]);
        c=0;
        for(t=0;t<=k;t++)
        {
            if(mi>=i[t])
            {
                mi=i[t];
                z=DuplicateString(p[t]);
                c=t;
            }
        }
        i[c]=i[k];
        p[c]=DuplicateString(p[k]);
        i[k]=mi;
        p[k]=DuplicateString(z);
    }
    printf("�γ�  ����ѡ����\n");
    for(t=0;t<all;t++)
    {
        printf("%s    %-d\n",p[t],i[t]);
    }
}

void Sort32()
{
    FILE* kp;
    STRING* p[100];
    int k=0,t,mi,c,all,a,b,n=1,h;
    int* i;
    STRING z;
    z=NewObject(STRING);
    i=NewObject(int*);
    p[0]=DuplicateString("A");
    while(TRUE)
    {
        p[n]=DuplicateString(TransformCharIntoString('A'+n));/*����Ϊ�˷���ֱ��ʹ���˴��ţ�û��ɨ���ļ�*/
        if(CompareString(p[n],"Z")==0)
        {
            break;
        }
        n++;
    }
    kp=fopen("Allchoice.csv","r");
    while(feof(kp)==0)
    {
        fscanf(kp,"%d,%d,",&a,&b);
        i[k]=b;
        k++;
    }
    fclose(kp);
    k=k-1;
    all=k;
    for(k=k-1;k>0;k--)
    {
        mi=i[0];
        z=DuplicateString(p[0]);
        c=0;
        for(t=0;t<=k;t++)
        {
            if(mi>=i[t])
            {
                mi=i[t];
                z=DuplicateString(p[t]);
                c=t;
            }
        }
        i[c]=i[k];
        p[c]=DuplicateString(p[k]);
        i[k]=mi;
        p[k]=DuplicateString(z);
    }
    printf("�γ�  Ů��ѡ����\n");
    for(t=0;t<all;t++)
    {
        printf("%s    %-d\n",p[t],i[t]);
    }
}

int Whether(STRING* q,STRING s,int o)/*ѡ�β��������ĸ��������������û���������ݣ�ת��Ϊ������Ϣ,Ҳ������Ŀ��Ʋ���*/
{
    int k,i=0,p,h=1,r[64],sum=0,sex,id,b,z,m,l,w,j;
    FILE* fp;
    char* t;
    char* f;
    t=NewObject(char*);
    f=NewObject(char*);
    fp=fopen("lesson_information.txt","r");/*�򿪿γ���Ϣ�ļ����ļ������γ�������ѧ��*/
    k=FindCharFirst(',',s);
    q[0]=GetSubString(s,0,k);
    i=1;
    if(o>0)
    {
        sex=1;
        id=o;
    }
    if(o<0)
    {
        sex=-1;
        id=-o;
    }
    w=Detect(id);
    while(TRUE)
    {
        p=k;
        k=FindCharNext(',',s,k+1);
        q[i]=GetSubString(s,p+1,k-p-1);
        if(k==-1)
        {
            q[i]=GetSubString(s,p+1,GetStringLength(s)-p);
            i++;
            break;
        }
        i++;
    }
    for(m=0;m<i;m++)
    {
        for(l=m+1;l<i;l++)
            {
                if(CompareString(q[m],q[l])==0)
                {
                    return 2;
                }
            }
    }
    if(i>6)
    {
        fclose(fp);
        return 1;
    }
    z=i;
    for(i=i;i>0;i--)
    {
        fscanf(fp,"%s",f);
        while(TRUE)
        {
            fseek(fp,1L,1);
            fscanf(fp,"%d,%s",&r[i-1],t);
            if(CompareString(q[i-1],t)==0)
            {
                break;
            }
            if(r[i-1]==0)
            {
                fclose(fp);
                return -2;
            }
        }
        rewind(fp);
        sum+=r[i-1];
    }
    if(sum<12)
    {
        fclose(fp);
        return -1;
    }
    if(w!=-1)
    {
        printf("ע�⣺���Ѿ����й�ѡ�β��������β�����������һ�β�����\n");
        SortI(q,sum,id,z);
        SortAll(q,sex,z);
        ChangeSortAll(id,sex,z);
        j=CopyOut(w);
        CopyIn(j);
    }
    if(w==-1)
    {
        printf("�������һ�ν���ѡ�β�����");
        SortI(q,sum,id,z);
        SortAll(q,sex,z);
    }
    printf("ѡ�β����ɹ���\n");
    BacktoMenu(o);
    return 0;
}

int CopyOut(int i,STRING q)
{
    FILE* fp;
    FILE* hp;
    char*s,p;
    int t=0;
    s=NewObject(char*);
    p=NewObject(char*);
    int m=0;
    fp=fopen("Ichoice.txt","r");
    hp=fopen("pass.txt","w+");/*���ڡ�w��ģʽ�����ԭ���ݣ���a��ģʽֻ���ڽ�β׷�����ݣ�����������һ�������ļ����޸��м䲿�ֵ���Ϣ*/
    while(TRUE)
    {
        fscanf(fp,"%s",s);
        if(m==i)
        {
            fscanf(fp,"%s",s);
        }
        fprintf(hp,"%s\n",s);
        t++;
        m++;
        if(feof(fp)!=0)
        {
            break;
        }
    }
    fclose(fp);
    fclose(hp);
    return t;
}

void CopyIn(int j)
{
    FILE* fp;
    FILE* hp;
    char* s;
    int k=0;
    s=NewObject(char*);
    fp=fopen("pass.txt","r");
    hp=fopen("Ichoice.txt","w");
    while(k<j-1)
    {
        fscanf(fp,"%s",s);
        fprintf(hp,"%s\n",s);
        k++;
    }
    fclose(hp);
}

void ChangeSortAll(int id,int sex,int z)/*�ı�ԭ����¼������*/
{
    STRING* a=NewObject(STRING*);
    STRING s;
    char* t;
    int m,n,h=0,p,k,i=1,l;
    FILE* pp;
    s=NewObject(STRING);
    t=NewObject(char*);
    pp=fopen("Ichoice.txt","r");
    while(h!=id)
    {
        fscanf(pp,"%d,%d,%d,",&h,&m,&n);
        fscanf(pp,"%s",s);
    }
    fclose(pp);
    k=FindCharFirst(',',s);
    a[0]=GetSubString(s,0,k);
    l=GetStringLength(s);
    s=ConcatenateString(s,",");
    while(TRUE)
    {
        p=k;
        k=FindCharNext(',',s,k+1);
        a[i]=GetSubString(s,p+1,k-p-1);
        if(k==l)
        {
            break;
        }
        i++;
    }
    SortAll2(a,sex,z);
}

int Detect(int id)/*����Ƿ��������й�ѡ�β���*/
{
    int h,i=0;
    FILE* fp;
    char* s;
    s=NewObject(char*);
    fp=fopen("Ichoice.txt","r");
    while(feof(fp)==0)
    {
        fscanf(fp,"%d",&h);
        if(h==id)
        {
            fclose(fp);
            return i;
        }
        fscanf(fp,"%s",s);
        i++;
    }
    return -1;
}

void SortI(STRING* a,int sum,int t,int i)/*����Ϣ���뵽ѧ��ѡ����Ϣ�ļ���*/
{
    int m;
    char* s;
    FILE* hp;
    s=NewObject(char*);
    hp=fopen("Ichoice.txt","a+");
    fprintf(hp,"%d",t);
    fprintf(hp,",%d",i);
    fprintf(hp,",%d",sum);
    for(m=0;m<i;m++)
    {
        fprintf(hp,",%s",a[m]);
    }
    fprintf(hp,"\n");
    fclose(hp);
}

void SortAll(STRING* q,int sex,int i)/*����Ϣ���뵽ѡ����Ϣ�����ļ���*/
{
    FILE* fp;
    int p[16],m=0,n=0,ha;
    fp=fopen("Allchoice.csv","r");
    while(m<=15)
    {
        fscanf(fp,"%d,",&p[m]);
        m++;
    }
    fclose(fp);
    fp=fopen("Allchoice.csv","w+");
        for(n=0;n<i;n++)
        {
            ha=(int)(GetIthChar(q[n],0)-'A');/*�˴���Ϊ�γ̴��Ŵ���˳������ֱ������������˳��������Ų�����˳����Ҫ����Ϣ�ļ������˳����ص���Ϣ*/
            if(sex==1)
            {
                p[2*ha]=p[2*ha]+1;
            }
            if(sex==-1)
            {
                p[2*ha+1]=p[2*ha+1]+1;
            }
        }
        for(n=0;n<=15;n++)
        {
            fprintf(fp,"%d,",p[n]);
        }
        fclose(fp);
}

void SortAll2(STRING* a,int sex,int i)
{
    FILE* fp;
    int p[16],m=0,n=0,ha;
    fp=fopen("Allchoice.csv","r");
    while(m<=15)
    {
        fscanf(fp,"%d,",&p[m]);
        m++;
    }
    fclose(fp);
    fp=fopen("Allchoice.csv","w+");
        for(n=0;n<i;n++)
        {
            ha=(int)(GetIthChar(a[n],0)-'A');
            if(sex==1)
            {
                p[2*ha]=p[2*ha]-1;
            }
            if(sex==-1)
            {
                p[2*ha+1]=p[2*ha+1]-1;
            }
        }
        for(n=0;n<=15;n++)
        {
            fprintf(fp,"%d,",p[n]);
        }
        fclose(fp);
}

void IF(int t)
{
    int i;
    i=Menu();
    switch(i)
    {
        case 1:Select(t);break;
        case 2:SearchI(t);break;
        case 3:SearchAll(t);break;
    }
}
