#include "Soort.h"

#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include "../library_code/dynarray.h"
#include <stdlib.h>

int Login()/*登录函数，用于判定是否成功登录，即用户名是否存在和其对应密码是否正确*/
{
    int a,b,k,sex;
    char* pp;
    FILE* fp;
    printf("学号：");
    a=GetIntegerFromKeyboard();
    printf("密码：");
    b=GetIntegerFromKeyboard();
    fp=fopen("student_information.csv","r");/*打开学生信息文件*/
    fseek(fp,23L,0);
    fscanf(fp,"%d",&k);
    while(k!=0)/*查找用户名*/
    {
        if(a==k)
        {
            fseek(fp,1L,1);
            fscanf(fp,"%d",&k);
            if(b==k)/*检查密码是否正确*/
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

int Menu()/*在成功登录后，显示主菜单函数*/
{
    int i;
    printf("-------------------\n");
    printf("1.选课操作\n");
    printf("2.查询个人选课信息\n");
    printf("3.查询总体选课信息\n");
    printf("-------------------\n");
    printf("请选择你的操作：");
    i=GetIntegerFromKeyboard();
    return i;
}

int Menu1()/*在成功登录后，选择查询选课整体情况时，显示菜单的函数*/
{
    int i;
    printf("---------------------------------------------\n");
    printf("1.查询选课量排序\n");
    printf("2.查询总学分数学生排序（只显示当前已选课学生）\n");
    printf("3.查询最受男女生欢迎课程\n");
    printf("---------------------------------------------\n");
    printf("请选择你的操作：");
    i=GetIntegerFromKeyboard();
    return i;
}

void BacktoMenu(int h)/*完成一次操作后，判定是否返回主菜单*/
{
    int t;
    printf("是否要返回主菜单？（若返回则输入1）：");
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

void Select(int t)/*选课操作函数，用于判定选课是否合理，以及将选课信息输入选课信息文件*/
{
    STRING s;
    STRING* a=NewObject(STRING*);
    int i;
    while(i!=0){
    printf("请输入你要选的课程（依次输入各个课程，中间用逗号相隔）：");
    s=GetStringFromKeyboard();
    i=Whether(a,s,t);
    if(i==1)
    {
        printf("选课数量不得超过6门！");
    }
    if(i==-1)
    {
        printf("学分总数不得低于12！");
    }
    if(i==-2)
    {
        printf("输入的课程名称有误！");
    }
    if(i==2)
    {
        printf("输入的课程重复！");
    }
    }
}

void SearchI(int t)/*查询个人信息*/
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
            printf("你所选课程为：%s\n",s);
            printf("总课程数为：%d\n",m);
            printf("总学分为：%d\n",n);
            BacktoMenu(t);
        }
    }
    fclose(dp);
    printf("你还没有进行选课操作，无法查询！\n");
    BacktoMenu(t);
}

void SearchAll(int id)/*查询整体信息*/
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

void Sort1()/*查询选课量排序*/
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
        p[n]=DuplicateString(TransformCharIntoString('A'+n));/*这里为了方便直接使用了代号，没有扫描文件*/
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
    printf("课程  选课量\n");
    for(t=0;t<all;t++)
    {
        printf("%s    %-d\n",p[t],i[t]);
    }
}

void Sort2()/*查询总学分数学生排序（只显示当前已选课学生）*/
{
    FILE* fp;
    int* a;
    int h[1000];/*在这里本来使用动态数组，但是出现了某种很难调和的bug，所以最后使用了1000作为上限（哭）*/
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
    printf("学号  总学分\n");
    for(k=0;k<i-1;k++)
    {
        printf("%-3d     %-d\n",a[k],h[k]);
    }
}

void Sort3()/*查询最受男女生欢迎课程*/
{
    int w;
    printf("查询男生请输入“1”，查询女生请输入“2”：");
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
        p[n]=DuplicateString(TransformCharIntoString('A'+n));/*这里为了方便直接使用了代号，没有扫描文件*/
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
    printf("课程  男生选课量\n");
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
        p[n]=DuplicateString(TransformCharIntoString('A'+n));/*这里为了方便直接使用了代号，没有扫描文件*/
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
    printf("课程  女生选课量\n");
    for(t=0;t<all;t++)
    {
        printf("%s    %-d\n",p[t],i[t]);
    }
}

int Whether(STRING* q,STRING s,int o)/*选课操作函数的辅助函数，处理用户输入的数据，转化为有用信息,也是主体的控制部分*/
{
    int k,i=0,p,h=1,r[64],sum=0,sex,id,b,z,m,l,w,j;
    FILE* fp;
    char* t;
    char* f;
    t=NewObject(char*);
    f=NewObject(char*);
    fp=fopen("lesson_information.txt","r");/*打开课程信息文件，文件包含课程名称与学分*/
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
        printf("注意：你已经进行过选课操作，本次操作将覆盖上一次操作。\n");
        SortI(q,sum,id,z);
        SortAll(q,sex,z);
        ChangeSortAll(id,sex,z);
        j=CopyOut(w);
        CopyIn(j);
    }
    if(w==-1)
    {
        printf("这是你第一次进行选课操作。");
        SortI(q,sum,id,z);
        SortAll(q,sex,z);
    }
    printf("选课操作成功！\n");
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
    hp=fopen("pass.txt","w+");/*由于“w”模式会擦除原数据，“a”模式只可在结尾追加数据，所以设置了一个过渡文件，修改中间部分的信息*/
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

void ChangeSortAll(int id,int sex,int z)/*改变原来记录的数据*/
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

int Detect(int id)/*检测是否曾经进行过选课操作*/
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

void SortI(STRING* a,int sum,int t,int i)/*将信息输入到学生选课信息文件里*/
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

void SortAll(STRING* q,int sex,int i)/*将信息输入到选课信息汇总文件里*/
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
            ha=(int)(GetIthChar(q[n],0)-'A');/*此处因为课程代号存在顺序，所以直接利用了这种顺序，如果代号不存在顺序，则要在信息文件里加入顺序相关的信息*/
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
