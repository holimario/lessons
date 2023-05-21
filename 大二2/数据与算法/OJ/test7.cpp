#include <string.h>
#include <iostream>
#include <cmath>

//幂法和逆幂法

using namespace std;

double* matrix[1010];
double vec1[1010];//用于运算的向量
double vec2[1010]={1,4,6};//用于运算的向量
int N;//维数
double a,b;
int num=2000;//迭代次数
double error=0.0000000001;//规定误差限
double* info[1010];
double re[1010];

void LU(int y){//将matrix进行LU分解
    if(y==N-1)return;//迭代停止条件
    if(matrix[y][y]==0)//如果可能不满足上三角关系，进行交换
    {
        for(int j=y+1;j<=N-1;j++)
        {
            if(matrix[j][y]!=0)
            {
                double* p=matrix[j];
                matrix[j]=matrix[y];
                matrix[y]=p;
                p=info[j];
                info[j]=info[y];
                info[y]=p;
                break;
            }
        }
    }
    if(matrix[y][y]==0)//没有找到可交换的两个行，直接进行下一步迭代
    {
        LU(y+1);
    }
    else
    {
        for(int i=y+1;i<=N-1;i++)//进行消去操作
        {
            if(matrix[i][y]!=0)
            {
                double h=matrix[i][y]/matrix[y][y];
                for(int g=0;g<=N-1;g++)
                {
                    matrix[i][g]=matrix[i][g]-h*matrix[y][g];
                    info[i][g]=info[i][g]-h*info[y][g];
                }
            }
            
        }
        LU(y+1);//进行完消元后进入下一步迭代
    }
}

void init(){//初始化vec
    for(int i=0;i<=N-1;i++)
    {
        vec1[i]=1;
        vec2[i]=1;
    }
}

double getmax(double* x){
    double p=0;
    for(int i=0;i<=N-1;i++)
    {
        if(fabs(x[i])>p)
        {
            p=fabs(x[i]);
        }
    }
    return p;
}

void multiply(double* x){
    double vec[1010];
    for(int i=0;i<=N-1;i++)
    {
        vec[i]=0;
        for(int j=0;j<=N-1;j++)
        {
            vec[i]+=x[j]*matrix[i][j];
        }
    }
    for(int i=0;i<=N-1;i++)
    {
        x[i]=vec[i];
    }
}

void calculate(double* x){
    for(int i=0;i<=N-1;i++)//清零
    {
        re[i]=0;
    }
    for(int i=0;i<=N-1;i++)//计算相应的系数
    {
        if(x[i]!=0)
        {
            double h=x[i]/matrix[i][i];
            for(int k=0;k<=N-1;k++)
            {
                re[k]=re[k]+h*info[i][k];//输入信息
                x[k]=x[k]-h*matrix[i][k];//更新目标信息
            }
        }
    }
    for(int i=0;i<=N-1;i++)
    {
        x[i]=re[i];
    }
}

double maxx(){//求最大特征值
    int k=0;
    double res=0;
    double temp=0;
    double m=1;
    while(k<=num)
    {
        k++;
        temp=res;
        for(int i=0;i<=N-1;i++)//规范化向量，防止分量过大
        {
            vec1[i]=vec1[i]/m;
        }
        multiply(vec1);
        res=getmax(vec1);//找到最大分量
        m=res;
        if(fabs(res-temp)<=error)break;
    }
    return res;
}

double minn(){//求最小特征值
    int k=0;
    double res=0;
    double temp=0;
    double m=1;
    LU(0);//进行分解
    while(k<=num)
    {
        k++;
        temp=res;
        for(int i=0;i<=N-1;i++)//规范化向量，防止分量过大
        {
            vec2[i]=vec2[i]/m;
        }
        calculate(vec2);
        res=getmax(vec2);//找到最大分量
        m=res;
        if(fabs(res-temp)<=error)break;
    }
    return res;
}

int main(){
    cout.precision(4);//设置有效数字
    cin>>N;
    for(int i=0;i<=N-1;i++)
    {
        double* p=new double[1010];
        double* pp=new double[1010];
        for(int k=0;k<=N-1;k++)
        {
            cin>>p[k];
            pp[k]=0;
        }
        pp[i]=1;
        info[i]=pp;
        matrix[i]=p;
    }
    init();
    a=maxx();
    b=1/minn();
    cout<<a<<' '<<b<<endl;
    return 0;
}