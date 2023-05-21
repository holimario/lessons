#include<queue>
#include<string.h>
#include<iostream>
#include<algorithm>

//通过高斯消元法求出异或矩阵的基底

//两个布尔值之间的加和运算是异或运算

using namespace std;

bool S[1010];//操作集合
bool T[1010];//目标状态
bool* base[1010];//存储基底矩阵，指针数组
bool* info[1010];//存储基底对应的移位和翻转运算

int N;//记录输入的维数

void init(){//对基底矩阵进行初始化
    for(int i=0;i<=N-1;i++)
    {
        bool* p=new bool[1010];
        bool* pp=new bool[1010];//存储矩阵基底信息
        for(int k=0;k<=N-1;k++)
        {
            p[(N-i+k)%(N)]=S[k];//进行错位操作
            pp[k]=0;
        }
        base[i]=p;
        pp[i]=1;
        info[i]=pp;
    }
}

void Gauss(int a){//计算出基底矩阵，同时记录其对应的变换信息，初始默认为一系列的S的偏移作为横向量，可以利用迭代进行快速计算，a标记着迭代的维度
    if(a==N-1)return;//迭代停止条件
    if(base[a][a]!=1)//如果可能不满足上三角关系，进行交换
    {
        for(int j=a+1;j<=N-1;j++)
        {
            if(base[j][a]==1)
            {
                bool* p=base[j];
                base[j]=base[a];
                base[a]=p;
                p=info[j];
                info[j]=info[a];
                info[a]=p;
                break;
            }
        }
    }
    if(base[a][a]!=1)//没有找到可交换的两个行，直接进行下一步迭代
    {
        Gauss(a+1);
    }
    else
    {
        for(int i=a+1;i<=N-1;i++)//进行消去操作
        {
            if(base[i][a]==1)//发现需要进行消元操作，直接进行异或运算
            {
                for(int g=0;g<=N-1;g++)
                {
                    base[i][g]=base[a][g]^base[i][g];
                    info[i][g]=info[a][g]^info[i][g];
                }
            }
        }
        Gauss(a+1);//进行完消元后进入下一步迭代
    }
}

void solve(){//利用高斯消元法求解方程组的解，并且输出结果，在计算时会自动判断出不存在解的情况
    Gauss(0);//先进行高斯消元，得到基底矩阵
    bool* res=new bool[1010];//存储结果
    for(int i=0;i<=N-1;i++)//初始化
    {
        res[i]=0;
    }
    for(int i=0;i<=N-1;i++)//计算相应的系数
    {
        if(T[i]==1)
        {
            if(base[i][i]==1)
            {
                for(int k=0;k<=N-1;k++)
                {
                    res[k]=info[i][k]^res[k];//输入信息
                    T[k]=T[k]^base[i][k];//更新目标信息
                }
            }
            else//不存在解
            {
                putchar('N');
                cout<<endl;
                return;
            }
        }
    }
    int flag=0;
    for(int y=0;y<=N-1;y++)//存在解，输出结果
    {
        if(res[y]==1)
        {
            putchar('B');
            flag=1;
        }
        if(flag==1)
        {
            putchar('A');
        }
    }
    if(flag==0)
    {
        putchar('B');
        putchar('B');
    }
    delete[] res;
    cout<<endl;
}

void clean(){
    for(int i=0;i<=N-1;i++)
    {
        delete[] base[i];
        delete[] info[i];
    }
}


int main(){
    int x;
    cin>>x;
    for(int i=1;i<=x;i++)//输入题目并求解
    {
        scanf("%d",&N);//输入维数
        char c=' ';
        int k=0;
        while(c==' ')//除去空格
        {
            c=getchar();
        }
        while(c!=' ')
        {
            S[k]=(bool)(c-'0');
            k++;
            c=getchar();
        }
        k=0;
        c=' ';
        while(c==' ')//除去空格
        {
            c=getchar();
        }
        while(c!=' ')
        {
            T[k]=(bool)(c-'0');
            k++;
            c=getchar();
            if(k==N)break;
        }
        init();//初始化
        solve();//求解并输出
        clean();//清除空间
    }
    return 0;
}