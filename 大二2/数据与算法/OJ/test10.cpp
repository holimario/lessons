#include <string.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

//左上角为(0,0)
//采用广度优先的BFS算法，暴力搜索

int num=0;//存储当前所搜索的层数

struct point{//存储点的基本信息，包含父节点，最少步骤数，对于某个姿态的点，其可能操作仅有左转、右转和执行，保证了BFS的可实现
    bool flag=0;//当flag==1时即为扫描过了
    char move;//标记到达此处所对应的操作，-1是左转，-2是右转，1是前进1格，2是前进两格
};

struct forlist{
    short me[3];//包含自己的信息，用于list中
    forlist (short a,short b,int c){
        me[0]=a;
        me[1]=b;
        me[2]=c;
    }
};

point node[4][1000][1000];//最前面一维表示以某种姿态到达该点

short sA,sB,sC;//初始状态
short eA,eB,eC;//终止状态
short N,M;//列数和行数

bool info[1010][1010];//存储是否为墙的信息，以及是否已经探索过了
queue<forlist> list1;//存储查找信息
queue<forlist> list2;//存储查找信息

void search(){//寻找路线并输出，利用BFS不断扫描，直到达到最终目标状态
    list1.push(forlist(sC-1,sA,sB));//存入出发点
    node[sC-1][sA][sB].flag=1;
    short temp;
    while(1)//不断循环查找
    {
        num++;
        while(!list1.empty())
        {
            forlist t=list1.front();//取出开头元素
            list1.pop();//删去开头元素
            temp=(t.me[0]+3)%4;
            if(node[temp][t.me[1]][t.me[2]].flag==0)//没被扫描到过
            {
                node[temp][t.me[1]][t.me[2]].flag=1;
                node[temp][t.me[1]][t.me[2]].move=-2;
                list2.push(forlist(temp,t.me[1],t.me[2]));//存入扫描列表
            }
            temp=(t.me[0]+1)%4;
            if(node[temp][t.me[1]][t.me[2]].flag==0)//没被扫描到过
            {
                node[temp][t.me[1]][t.me[2]].flag=1;
                node[temp][t.me[1]][t.me[2]].move=-1;
                list2.push(forlist(temp,t.me[1],t.me[2]));//存入扫描列表
            }
            if(t.me[0]==0)
            {
                if(t.me[1]-1>=0&&node[t.me[0]][t.me[1]-1][t.me[2]].flag==0&&info[t.me[1]-1][t.me[2]]==0)//没被扫描到过且不是墙且没有出界线
                {
                    node[t.me[0]][t.me[1]-1][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]-1][t.me[2]].move=1;
                    list2.push(forlist(t.me[0],t.me[1]-1,t.me[2]));
                }
                if(t.me[1]-2>=0&&node[t.me[0]][t.me[1]-2][t.me[2]].flag==0&&info[t.me[1]-2][t.me[2]]==0&&info[t.me[1]-1][t.me[2]]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]-2][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]-2][t.me[2]].move=2;
                    list2.push(forlist(t.me[0],t.me[1]-2,t.me[2]));
                }
            }
            else if(t.me[0]==1)
            {
                if(t.me[2]-1>=0&&node[t.me[0]][t.me[1]][t.me[2]-1].flag==0&&info[t.me[1]][t.me[2]-1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]-1].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]-1].move=1;
                    list2.push(forlist(t.me[0],t.me[1],t.me[2]-1));
                }
                if(t.me[2]-2>=0&&node[t.me[0]][t.me[1]][t.me[2]-2].flag==0&&info[t.me[1]][t.me[2]-2]==0&&info[t.me[1]][t.me[2]-1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]-2].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]-2].move=2;
                    list2.push(forlist(t.me[0],t.me[1],t.me[2]-2));
                }
            }
            else if(t.me[0]==2)
            {
                if(t.me[1]+1<=M-1&&node[t.me[0]][t.me[1]+1][t.me[2]].flag==0&&info[t.me[1]+1][t.me[2]]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]+1][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]+1][t.me[2]].move=1;
                    list2.push(forlist(t.me[0],t.me[1]+1,t.me[2]));
                }
                if(t.me[1]+2<=M-1&&node[t.me[0]][t.me[1]+2][t.me[2]].flag==0&&info[t.me[1]+2][t.me[2]]==0&&info[t.me[1]+1][t.me[2]]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]+2][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]+2][t.me[2]].move=2;
                    list2.push(forlist(t.me[0],t.me[1]+2,t.me[2]));
                }
            }
            else if(t.me[0]==3)
            {
                if(t.me[2]+1<=N-1&&node[t.me[0]][t.me[1]][t.me[2]+1].flag==0&&info[t.me[1]][t.me[2]+1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]+1].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]+1].move=1;
                    list2.push(forlist(t.me[0],t.me[1],t.me[2]+1));
                }
                if(t.me[2]+2<=N-1&&node[t.me[0]][t.me[1]][t.me[2]+2].flag==0&&info[t.me[1]][t.me[2]+2]==0&&info[t.me[1]][t.me[2]+1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]+2].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]+2].move=2;
                    list2.push(forlist(t.me[0],t.me[1],t.me[2]+2));
                }
            }
        }
        if(node[eC-1][eA][eB].flag==1)break;//已经到达了目标点，跳出循环
        num++;//增加层数

        while(!list2.empty())//遍历list2
        {
            forlist t=list2.front();//取出开头元素
            list2.pop();//删去开头元素
            temp=(t.me[0]+3)%4;
            if(node[temp][t.me[1]][t.me[2]].flag==0)//没被扫描到过
            {
                node[temp][t.me[1]][t.me[2]].flag=1;
                node[temp][t.me[1]][t.me[2]].move=-2;
                list1.push(forlist(temp,t.me[1],t.me[2]));//存入扫描列表
            }
            temp=(t.me[0]+1)%4;
            if(node[temp][t.me[1]][t.me[2]].flag==0)//没被扫描到过
            {
                node[temp][t.me[1]][t.me[2]].flag=1;
                node[temp][t.me[1]][t.me[2]].move=-1;
                list1.push(forlist(temp,t.me[1],t.me[2]));//存入扫描列表
            }
            if(t.me[0]==0)
            {
                if(t.me[1]-1>=0&&node[t.me[0]][t.me[1]-1][t.me[2]].flag==0&&info[t.me[1]-1][t.me[2]]==0)//没被扫描到过且不是墙且没有出界线
                {
                    node[t.me[0]][t.me[1]-1][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]-1][t.me[2]].move=1;
                    list1.push(forlist(t.me[0],t.me[1]-1,t.me[2]));
                }
                if(t.me[1]-2>=0&&node[t.me[0]][t.me[1]-2][t.me[2]].flag==0&&info[t.me[1]-2][t.me[2]]==0&&info[t.me[1]-1][t.me[2]]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]-2][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]-2][t.me[2]].move=2;
                    list1.push(forlist(t.me[0],t.me[1]-2,t.me[2]));
                }
            }
            else if(t.me[0]==1)
            {
                if(t.me[2]-1>=0&&node[t.me[0]][t.me[1]][t.me[2]-1].flag==0&&info[t.me[1]][t.me[2]-1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]-1].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]-1].move=1;
                    list1.push(forlist(t.me[0],t.me[1],t.me[2]-1));
                }
                if(t.me[2]-2>=0&&node[t.me[0]][t.me[1]][t.me[2]-2].flag==0&&info[t.me[1]][t.me[2]-2]==0&&info[t.me[1]][t.me[2]-1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]-2].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]-2].move=2;
                    list1.push(forlist(t.me[0],t.me[1],t.me[2]-2));
                }
            }
            else if(t.me[0]==2)
            {
                if(t.me[1]+1<=M-1&&node[t.me[0]][t.me[1]+1][t.me[2]].flag==0&&info[t.me[1]+1][t.me[2]]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]+1][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]+1][t.me[2]].move=1;
                    list1.push(forlist(t.me[0],t.me[1]+1,t.me[2]));
                }
                if(t.me[1]+2<=M-1&&node[t.me[0]][t.me[1]+2][t.me[2]].flag==0&&info[t.me[1]+2][t.me[2]]==0&&info[t.me[1]+1][t.me[2]]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]+2][t.me[2]].flag=1;
                    node[t.me[0]][t.me[1]+2][t.me[2]].move=2;
                    list1.push(forlist(t.me[0],t.me[1]+2,t.me[2]));
                }
            }
            else if(t.me[0]==3)
            {
                if(t.me[2]+1<=N-1&&node[t.me[0]][t.me[1]][t.me[2]+1].flag==0&&info[t.me[1]][t.me[2]+1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]+1].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]+1].move=1;
                    list1.push(forlist(t.me[0],t.me[1],t.me[2]+1));
                }
                if(t.me[2]+2<=N-1&&node[t.me[0]][t.me[1]][t.me[2]+2].flag==0&&info[t.me[1]][t.me[2]+2]==0&&info[t.me[1]][t.me[2]+1]==0)//没被扫描到过且不是墙
                {
                    node[t.me[0]][t.me[1]][t.me[2]+2].flag=1;
                    node[t.me[0]][t.me[1]][t.me[2]+2].move=2;
                    list1.push(forlist(t.me[0],t.me[1],t.me[2]+2));
                }
            }
        }
        if(node[eC-1][eA][eB].flag==1)break;//已经到达了目标点，跳出循环
    }
    cout<<num<<endl;
    short a=eC-1,b=eA,c=eB;
    char* out=new char[num+1];
    for(int i=0;i<=num-1;i++)//对路径进行复原并输出
    {
        out[i]=node[a][b][c].move;
        if(out[i]==-1)a=(a+3)%4;
        else if(out[i]==-2)a=(a+1)%4;
        else if(out[i]==1)
        {
            if(a==0)b+=1;
            else if(a==1)c+=1;
            else if(a==2)b-=1;
            else if(a==3)c-=1;
        }
        else if(out[i]==2)
        {
            if(a==0)b+=2;
            else if(a==1)c+=2;
            else if(a==2)b-=2;
            else if(a==3)c-=2;
        }
    }
    for(int i=num-1;i>=0;i--)//反向输出
    {
        if(out[i]==-1)printf("L\n");
        else if(out[i]==-2)printf("R\n");
        else if(out[i]==1)printf("F\n");
        else if(out[i]==2)printf("F2\n");
    }
}

int main()
{
    cin>>N>>M;
    for(short i=0;i<=M-1;i++)
    {
        for(short j=0;j<=N-1;j++)
        {
            cin>>info[i][j];//i为行，j为列
        }
    }
    cin>>sB>>sA>>sC;
    cin>>eB>>eA>>eC;
    search();//寻找路线并输出
}