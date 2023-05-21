#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int l;
    int r;
} Node;

Node beg={0,0};

int sum=0;//记录总数
int state=1;//确定输出方向


int main(){
    int a,b,c,d;
    int process;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    process=a+b+c+d;
    Node* node=(Node*)(malloc(a*sizeof(Node)));
    for(int k=1;k<=process;k++)
    {
        scanf("%d",&a);
        if(a==1)
        {
            scanf("%d %d %d",&b,&c,&d);
            if(sum==0)
            {
                node[b].l=0;
                node[b].r=0;
                node[0].l=b;
                node[0].r=b;
            }
            else
            {
                if((state==1&&d==1)||(state==-1&&d==0))
                {
                    node[b].r=node[c].r;
                    node[b].l=c;
                    node[c].r=b;
                    node[node[b].r].l=b;
                }
                else
                {
                    node[b].l=node[c].l;
                    node[b].r=c;
                    node[c].l=b;
                    node[node[b].l].r=b;
                }
            }
            sum++;
        }
        else if(a==0)
        {
            scanf("%d",&b);
            node[node[b].l].r=node[b].r;
            node[node[b].r].l=node[b].l;
            sum--;
        }
        else if(a==-1)
        {
            scanf("%d %d",&b,&c);
            int temp;
            if(node[b].l==c)//如果两个交换的结点相邻，是特殊情况
            {
                node[node[b].r].l=c;
                node[node[c].l].r=b;
                node[b].l=node[c].l;
                node[c].r=node[b].r;
                node[b].r=c;
                node[c].l=b;
            }
            else if(node[b].r==c)
            {
                node[node[b].l].r=c;
                node[node[c].r].l=b;
                node[b].r=node[c].r;
                node[c].l=node[b].l;
                node[b].l=c;
                node[c].r=b;
            }
            else
            {
                node[node[b].l].r=c;
                node[node[b].r].l=c;
                node[node[c].l].r=b;
                node[node[c].r].l=b;
                temp=node[b].l;
                node[b].l=node[c].l;
                node[c].l=temp;
                temp=node[b].r;
                node[b].r=node[c].r;
                node[c].r=temp;
            }
        }
        else if(a==-2)
        {
            state=state*(-1);
        }
    }
    int temp=0;
    if(state==1)
    {
        for(int k=1;k<=sum;k++)
        {
            temp=node[temp].r;
            printf("%d ",temp);
        }
    }
    else if(state==-1)
    {
        for(int k=1;k<=sum;k++)
        {
            temp=node[temp].l;
            printf("%d ",temp);
        }
    }
    printf("-1");
}
