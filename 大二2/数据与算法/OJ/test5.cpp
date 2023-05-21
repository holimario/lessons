#include<queue>
#include<string.h>
#include<iostream>
#include<algorithm>

#define MAX 30010

using namespace std;

int S,E;//起点与终点

struct edge {//to为所到的点序号，cost为边权重
    int to,cost;
    bool operator ==(const edge& A)//用于find函数
    {
        return to==A.to;
    }
};
typedef pair<int,int> Pair; //first是最短距离，second是顶点的编号
vector<edge> info[MAX];//存储每个点到另外一些点的边权重信息
int dis[MAX];//存储原点到各点的距离


int getshort(int start,int end,vector<int>* path)//start为初始点,end为终点
{
    priority_queue<Pair,vector<Pair>,greater<Pair>> que;//存储距离信息的优先队列
    int v;
    memset(dis,0x7f,sizeof(dis));//设定初始值
    dis[start] = 0;
    que.push(Pair(0,start));//把起点加入队列
    while(!que.empty())
    {
        Pair p = que.top();
        que.pop();
        v = p.second;//顶点的序号
        if(v==end)
        {
            return v;//返回最终结束时的点序号
        }
        if (dis[v] < p.first) continue;//出现重复则跳过，节约时间
        for(int i = 0; i < info[v].size(); i++)
        {
            edge e = info[v][i];
            if (dis[e.to] > dis[v] + e.cost)//如果距离更短,那么将其存入优先队列，同时刷新路径链信息
            {
                dis[e.to] = dis[v] + e.cost;
                que.push(Pair(dis[e.to],e.to));
                path[e.to].clear();
                path[e.to].push_back(v);
            }
            else if(dis[e.to] == dis[v] + e.cost)//如果距离相等，那么增加路径链信息，从而实现保存多条路径
            {
                path[e.to].push_back(v);
            }
        }
    }
    return v;//返回最终结束时的点序号
}

void reset(vector<int>* path,int end)//重置距离信息info
{
    if(S==end)return;//如果清理到了开头则结束
    int p=path[end].size();
    for(int i=0;i<p;i++)
    {
        for(auto k=info[path[end][i]].begin();k!=info[path[end][i]].end();k++)
        {
            if(k->to==end)
            {
                info[path[end][i]].erase(k);
                break;
            }
        }
        for(auto k=info[end].begin();k!=info[end].end();k++)
        {
            if(k->to==path[end][i])
            {
                info[end].erase(k);
                break;
            }
        }
        reset(path,path[end][i]);//利用迭代进一步清理
    }
}

int main(){
    int x,y,z;
    int temp[MAX];
    int sum=0;
    int t;
    vector<int> path[MAX];//存储路径链信息，通过向上回溯，找到路径链
    cin>>S>>E;
    for(int i=1;i<=E;i++)
    {
        cin>>x>>y>>z;
        info[x].push_back(edge{y,z});//无向边
        info[y].push_back(edge{x,z});
    }
    cin>>S>>E;
    getshort(S,E,path);
    std::cout<<"start"<<endl;
    t=E;
    for(int i=0;;i++)//反向查找路径并记录
    {
        temp[i]=t;
        sum++;
        if(t==S)break;
        t=path[t][0];
    }
    for(int i=sum-1;i>=0;i--)
    {
        std::cout<<temp[i]<<endl;
    }
    std::cout<<"end"<<endl;
    std::cout<<dis[E]<<endl;
    vector<int> ppath[MAX];//存储路径链信息，通过向上回溯，找到路径链
    reset(path,E);//清除掉最短路径经过的位置，再计算几乎最短路径
    if(getshort(S,E,ppath)!=E)return 0;//如果不存在路径，那么直接跳过输出
    std::cout<<"start"<<endl;
    t=E;
    sum=0;
    for(int i=0;;i++)//反向查找路径并记录
    {
        temp[i]=t;
        sum++;
        if(t==S)break;
        t=ppath[t][0];
    }
    for(int i=sum-1;i>=0;i--)
    {
        std::cout<<temp[i]<<endl;
    }
    std::cout<<"end"<<endl;
    std::cout<<dis[E]<<endl;
    return 0;
}