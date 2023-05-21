#include<queue>
#include<algorithm>
#include<stdio.h>

//总时间复杂度是O(NlogN + Mklogk)

using namespace std;

long long type;//当前维度，通过设置为全局变量，方便node在利用nth_element函数进行自动排序
long long X,Y,k;//存储要寻找的点的信息

struct node //结点信息，存储坐标信息和序号
{
	long long x[2];
	long long id;
	friend bool operator < (const node& a, const node& b)
	{
		return a.x[type]<b.x[type];
	}
};
node Node[110000];

struct kd {//树结点信息，存储该树结点对应哪个结点以及其作为根节点的树的最大范围，还有其左右子树的序号(位置)
	node Node;
	long long max[2]; 
	long long min[2];
	long long l;
	long long r;
};
kd tree[110000];

class Dis//记录距离信息，用于优先队列
{ 
	public:
    long long dis;
	long long pos;
	bool operator < (const Dis& b)const {//比较算符，定义默认排序方法
		return dis>b.dis||(dis==b.dis&&pos<b.pos);
	}
};

inline long long cal(kd a)//计算两个结点之间的距离
{
	register long long x=a.Node.x[0]-X;
	register long long y=a.Node.x[1]-Y;
	return x*x+y*y;
}

inline long long call(kd a)//计算某个结点对应的树的边界与目标结点的可能最大距离
{
	register long long x=(a.max[0]-X)*(a.max[0]-X);
	register long long y=(a.min[0]-X)*(a.min[0]-X);
	register long long w=(a.max[1]-Y)*(a.max[1]-Y);
	register long long z=(a.min[1]-Y)*(a.min[1]-Y);
	return max(x,y)+max(w,z);
}

inline void bulidkdt(register long long& x, register long long l, register long long r, register long long k) {//创建树，x用于传递结点序号信息
	if (l > r) return;//迭代中止条件
	type=k;//标记维度，此处貌似很影响代码效率
	register long long mid = (l + r) >> 1;//通过移位进行除以2的操作
    x=mid;
	nth_element(Node + l, Node + mid, Node + r + 1);//对整体进行排序，筛选出中间结点
	tree[x].Node=Node[mid];//添加结点
	tree[x].min[0]=tree[x].max[0]=tree[x].Node.x[0];//输入默认边界
	tree[x].min[1]=tree[x].max[1]=tree[x].Node.x[1];//输入默认边界
	bulidkdt(tree[x].l,l,mid-1,k^1);//进行迭代，得到左子树
	bulidkdt(tree[x].r,mid+1,r,k^1);//进行迭代，得到右子树
    register long long lt=tree[x].l,rt=tree[x].r;
	if(x)//计算该结点对应的下面的子树的整体的边界值
    {
        if (lt)//左子树非空，找边界
	    {
		    tree[x].max[0]=max(tree[x].max[0],tree[lt].max[0]);
		    tree[x].max[1]=max(tree[x].max[1],tree[lt].max[1]);
		    tree[x].min[0]=min(tree[x].min[0],tree[lt].min[0]);
		    tree[x].min[1]=min(tree[x].min[1],tree[lt].min[1]);
	    }
	    if (rt)//右子树非空，找边界
	    {
		    tree[x].max[0]=max(tree[x].max[0],tree[rt].max[0]);
		    tree[x].max[1]=max(tree[x].max[1],tree[rt].max[1]);
		    tree[x].min[0]=min(tree[x].min[0],tree[rt].min[0]);
		    tree[x].min[1]=min(tree[x].min[1],tree[rt].min[1]);
	    }
    }
}

inline void fp(register long long root,priority_queue<Dis>& diss) {//找到解
	if (!root) return;//在迭代过程中，如果输入的root是0，也就意味着某个结点的某个方位的子节点为空
	register long long res=cal(tree[root]);//计算目标点与当前根节点的距离
	if (res > diss.top().dis||(res==diss.top().dis&&tree[root].Node.id<diss.top().pos))//如果该距离比存储的第k大的距离还大，或者比其id更小，那么将其放入优先队列
	{
		diss.pop();
		diss.push((Dis) {res,tree[root].Node.id});
	}
	register long long lf=tree[root].l,rt=tree[root].r;
	register long long dl, dr;
	if (lf) dl=call(tree[lf]);//左子树非空，计算其可能最大距离
	if (rt) dr=call(tree[rt]);//右子树非空，计算其可能最大距离
	if (dl > dr) {//如果左子树的可能最大距离比右子树大，那先搜索左子树，这样按顺序更新可以一定程度减小对比次数
		if (dl>=diss.top().dis) fp(lf,diss);//最大距离不超过当前第k远距离，则无需搜索
		if (dr>=diss.top().dis) fp(rt,diss);//最大距离不超过当前第k远距离，则无需搜索
	}
	else {
		if (dr>=diss.top().dis) fp(rt,diss);//最大距离不超过当前第k远距离，则无需搜索
		if (dl>=diss.top().dis) fp(lf,diss);//最大距离不超过当前第k远距离，则无需搜索
	}
}

int main(){
	long long N, M;
    long long root;//根结点位置
	scanf("%lld%lld",&N,&M);
	for (register long long i=1;i<=N;i++)
	{
		scanf("%lld%lld",&Node[i].x[0],&Node[i].x[1]);
		Node[i].id=i;
	}
	bulidkdt(root,1,N,0);
	while(M--)
	{
		scanf("%lld%lld%lld",&X,&Y,&k);
		priority_queue<Dis> diss;//重新定义新的优先队列，减少清除消耗的时间
		for(register long long j=1;j<=k;j++)
		{ 
			diss.push((Dis){-1,0});//先放入一系列的距离为0的结点，这样在进行fp操作时，开始k个结点都会被放入，就达到了优先队列的目的
		}
		fp(root,diss);
		printf("%lld\n", diss.top().pos-1);
	}
	return 0;
}