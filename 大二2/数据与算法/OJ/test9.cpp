#include <string.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>

//划分成一个个小区块，记录其总和，然后利用动态规划的思想求解
//可以利用动态规划的思想，找最小的三个区域

using namespace std;

const int INF=0x3f3f3f3f;//规定正无穷
int N;//总数
int Pm=0;//记录目前的正数数量，如果小于3，则是特殊情况
int Neg=0;//记录目前负数区域数量，如果小于3.则能直接输出结果
int type=-2;//记录当前的区块状态
std::priority_queue<int,vector<int>,greater<int>> maxx;//记录相对最大的三个数，防止出现特殊情况
long long block[1000100];//存储区块和
int num=0;//当前区块的总数
long long res=0;//记录总和
long long info[5][1000100];

long long calculate(){//一般情况下，利用block计算最佳方案
    for(int i=1;i<=4;i++)//先进行一遍循环，得到结果，这是不考虑循环数组的结构
    {
        long long maxx=-INF;//记录当前最大结果，每次循环都清空一下
        for(int j=i;j<=num-1;j++)
        {
            if(j==i)//此时是特殊情况，打头的那个
            {
                info[j][j]=info[j-1][j-1]+block[j];
            }
            else
            {
                maxx=max(maxx,info[i-1][j-1]);//更新分j-1组时的最佳情况
                info[i][j]=max(maxx,info[i][j-1])+block[j];
            }
        }
    }
    long long maxx=info[3][3];
    for(int i=4;i<=num-1;i++)//再循环一遍，只考虑用到循环结构的情况
    {
        maxx=max(maxx,info[3][i]);
    }

    for(int i=1;i<=4;i++)//考虑存在循环结构，实际上相当于求解剩下的三个，保证其总和最小
    {
        long long minn=INF;//记录当前最小结果，每次循环都清空一下
        for(int j=i;j<=num-1;j++)
        {
            if(j==i)//此时是特殊情况，打头的那个
            {
                info[j][j]=info[j-1][j-1]+block[j];
            }
            else
            {
                minn=min(minn,info[i-1][j-1]);//更新分j-1组时的最佳情况
                info[i][j]=min(minn,info[i][j-1])+block[j];
            }
        }
    }
    long long minn=info[3][3];
    for(int i=4;i<=num-1;i++)//再循环一遍，只考虑用到循环结构的情况
    {
        minn=min(minn,info[3][i]);
    }
    maxx=max(maxx,res-minn);//取最大值
    return maxx;
}

int main(){
    maxx.push(-666666666);
    maxx.push(-666666667);
    maxx.push(-666666668);
    scanf("%d",&N);
    long long t;
    for(int i=0;i<=N-1;i++)//记录并初步处理信息
    {
        scanf("%lld",&t);
        res+=t;
        info[0][i]=0;//初始化
        info[1][i]=0;
        if(t>=0)
        {
            Pm++;
            if(type==1)
            {
                block[num-1]+=t;
            }
            else
            {
                block[num]=t;
                num++;
            }
            type=1;
        }
        else
        {
            if(type==-1)
            {
                block[num-1]+=t;
            }
            else
            {
                block[num]=t;
                num++;
                Neg++;
            }
            type=-1;
        }
        if(t>maxx.top())
        {
            maxx.pop();
            maxx.push(t);
        }
    }
    if(block[0]*block[num-1]>0)//构成循环数组
    {
        block[0]+=block[num-1];
        num--;
    }
    if(Pm<=3)//大于等于零的工匠小于3个
    {
        int q=0;
        q+=maxx.top();
        maxx.pop();
        q+=maxx.top();
        maxx.pop();
        q+=maxx.top();
        maxx.pop();
        printf("%d",q);
    }
    else if(Neg<=3)
    {
        int q=0;
        for(int i=0;i<=num-1;i++)
        {
            if(block[i]>0)
            {
                q+=block[i];
            }
        }
        printf("%d",q);
    }
    else//最一般情况
    {
        int q=calculate();//计算最佳方案
        printf("%d",q);
    }
    return 0;
}