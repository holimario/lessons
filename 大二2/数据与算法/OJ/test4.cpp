#include<queue>
#include<algorithm>
#include<stdio.h>

#define int long long//全部替换为long long

#define re register

//总时间复杂度是O(NlogN+Mklogk)

using namespace std;
int num;//记录树结点树
int type=0;//当前维度，通过设置为全局变量，方便node在利用nth_element函数进行自动排序
int root;//根结点位置
int X,Y,k;//存储要寻找的点的信息

struct node //结点信息，存储坐标信息和序号
{
	int x[2];
	int id;
	friend bool operator < (const node& a,const node& b)
	{
		return a.x[type]<b.x[type];
	}
}Node[110000];

struct tree {//树结点信息，存储该树结点对应哪个结点以及其作为根节点的树的最大范围，还有其左右子树的序号(位置)
	node Node;
	int Max[2]; 
	int Min[2];
	int lf;
	int rt;
}Tree[110000];

struct info //记录距离信息，用于优先队列
{ 
	int dis;
	int pos;
	bool operator < (const info& b)const {//比较算符，定义默认排序方法
		return dis>b.dis||(dis==b.dis&&pos<b.pos);
	}
};

inline int cal(tree a)//计算两个结点之间的距离
{
	re int x=a.Node.x[0]-X;
	re int y=a.Node.x[1]-Y;
	return x*x+y*y;
}

inline int call(tree a)//计算某个结点对应的树的边界与目标结点的可能最大距离
{
	re int x=(a.Max[0]-X)*(a.Max[0]-X);
	re int y=(a.Min[0]-X)*(a.Min[0]-X);
	re int w=(a.Max[1]-Y)*(a.Max[1]-Y);
	re int z=(a.Min[1]-Y)*(a.Min[1]-Y);
	return max(x,y)+max(w,z);
}

inline void limit(re int x)//找到边界
{
	if (!x)return;
	re int l=Tree[x].lf,r=Tree[x].rt;
	if (l)//左子树非空，找边界
	{
		Tree[x].Max[0]=max(Tree[x].Max[0],Tree[l].Max[0]);
		Tree[x].Max[1]=max(Tree[x].Max[1],Tree[l].Max[1]);
		Tree[x].Min[0]=min(Tree[x].Min[0],Tree[l].Min[0]);
		Tree[x].Min[1]=min(Tree[x].Min[1],Tree[l].Min[1]);
	}
	if (r)//右子树非空，找边界
	{
		Tree[x].Max[0]=max(Tree[x].Max[0],Tree[r].Max[0]);
		Tree[x].Max[1]=max(Tree[x].Max[1],Tree[r].Max[1]);
		Tree[x].Min[0]=min(Tree[x].Min[0],Tree[r].Min[0]);
		Tree[x].Min[1]=min(Tree[x].Min[1],Tree[r].Min[1]);
	}
}

inline void CreatKDtree(re int& x,re int l,re int r) {//创建树，x用于传递结点序号信息
	if (l > r) return;//迭代中止条件
	x=++num;//结点数增加，空出一个0用于call计算
	type=type^1;//标记维度
	re int mid=(l+r)>>1;//通过移位进行除以2的操作
	nth_element(Node+l,Node+mid,Node+r+1);//对整体进行排序，筛选出中间结点
	Tree[x].Node=Node[mid];//添加结点
	Tree[x].Min[0]=Tree[x].Max[0]=Tree[x].Node.x[0];//输入默认边界
	Tree[x].Min[1]=Tree[x].Max[1]=Tree[x].Node.x[1];//输入默认边界
	CreatKDtree(Tree[x].lf,l,mid-1);//进行迭代，得到左子树
	CreatKDtree(Tree[x].rt,mid+1,r);//进行迭代，得到右子树
	limit(x);//计算该结点对应的下面的子树的整体的边界值
}

inline void fp(re int root,priority_queue<info>& diss) {//找到解
	if (!root) return;//在迭代过程中，如果输入的root是0，也就意味着某个结点的某个方位的子节点为空
	re int res=cal(Tree[root]);//计算目标点与当前根节点的距离
	if (res > diss.top().dis || (res == diss.top().dis && Tree[root].Node.id < diss.top().pos))//如果该距离比存储的第k大的距离还大，或者比其id更小，那么将其放入优先队列
	{
		diss.pop();
		diss.push((info) { res,Tree[root].Node.id });
	}
	re int lf=Tree[root].lf,rt=Tree[root].rt;
	re int dl,dr;
	if (lf) dl=call(Tree[lf]);//左子树非空，计算其可能最大距离
	if (rt) dr=call(Tree[rt]);//右子树非空，计算其可能最大距离
	if (dl > dr) {//如果左子树的可能最大距离比右子树大，那先搜索左子树，这样按顺序更新可以一定程度减小对比次数
		if (dl>=diss.top().dis) fp(lf,diss);//最大距离不超过当前第k远距离，则无需搜索
		if (dr>=diss.top().dis) fp(rt,diss);//最大距离不超过当前第k远距离，则无需搜索
	}
	else {
		if (dr>=diss.top().dis) fp(rt,diss);//最大距离不超过当前第k远距离，则无需搜索
		if (dl>=diss.top().dis) fp(lf,diss);//最大距离不超过当前第k远距离，则无需搜索
	}
}

signed main() {
	int N,M;
	scanf("%lld%lld",&N,&M);
	for (re int i=1; i <= N; i++)
	{
		scanf("%lld%lld",&Node[i].x[0],&Node[i].x[1]);
		Node[i].id=i;
	}
	CreatKDtree(root,1,N);
	while(M--) 
	{
		scanf("%lld%lld%lld",&X,&Y,&k);
		priority_queue<info> diss;//重新定义新的优先队列，减少清除消耗的时间
		for (re int j=1; j <= k; j++) 
		{ 
			diss.push((info) { -1,0 }); //先放入一系列的距离为0的结点，这样在进行fp操作时，开始k个结点都会被放入，就达到了优先队列的目的
		}
		fp(root,diss);
		printf("%lld\n",diss.top().pos-1);
	}
	return 0;
}