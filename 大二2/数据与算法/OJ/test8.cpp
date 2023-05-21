#include <string.h>
#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <iomanip>

//Aberth方法

using namespace std;

int N;//维数
int all[110];//存储部分根的重数
complex<double> temp[110];//存储部分根的重数
int test[110];//存储某个结果是否还需要牛顿方法进一步迭代
bool out[110];//保存是否输出的数据
complex<double> z[110];//存储当前估计的解
complex<double> w[110];//迭代信息存储
double error1=0.01;//判定两点距离的误差
double error2=0.00000001;//Aberth方法最终误差
double error3=0.000000001;//newton方法最终误差
double poly[7][110];//存储系数
int num1=10000;//迭代次数
int num2=100000;
int sum=0;

void init(){//初始化估计z
    for(int i=0;i<=N-1;i++)
    {
        complex<double> p(-10+cos(2*3.1415/(2*N)*i)/N,0.5*sin(2*3.1415/(2*N)*i)/N);
        // complex<double> p((rand()%10)*cos(i),(rand()%10)*sin(i));
        z[i]=p;
    }
    z[N]=complex<double>(188.79769,188.79769);
}

void derive(){
    for(int i=1;(i<=6)&&(i<=N);i++)//对多项式进行求导
    {
        for(int j=0;j<=N-i;j++)
        {
            poly[i][j]=(j+1)*poly[i-1][j+1];
        }
    }
}

complex<double> pp(int k,int m){//计算代入z_k到多项式中的解
    complex<double> a=0;
    complex<double> b=1;
    for(int i=0;i<=N-m;i++)
    {
        a+=b*poly[m][i];
        b*=z[k];
    }
    return a;
}

complex<double> tpp(int k,int m){//计算代入z_k到多项式中的解
    complex<double> a=0;
    complex<double> b=1;
    for(int i=0;i<=N-m;i++)
    {
        a+=b*poly[m][i];
        b*=temp[k];
    }
    return a;
}

complex<double> minuss(int k){//计算相减倒数求和系数
    complex<double> a=0;
    for(int i=0;i<=N-1;i++)
    {
        if(i!=k)
        {
            a+=((complex<double>)1)/(z[k]-z[i]);
        }
    }
    return a;
}

void calculate(){//计算结果并输出
    for(int i=1;i<=num1;i++)
    {
        sum=0;
        for(int j=0;j<=N-1;j++)
        {
            complex<double> a=pp(j,0)/pp(j,1);
            complex<double> b=(complex<double>)1-a*minuss(j);
            w[j]=a/b;
        }
        for(int j=0;j<=N-1;j++)
        {
            z[j]=z[j]-w[j];
            if(abs(w[j])<=error2)
            {
                sum++;
                test[j]=1;//通过
            }
        }
        if(sum==N)break;
    }
}


void chong(){//对各个根的重数进行简单梳理
    for(int i=0;i<=N-1;i++)
    {
        all[i]=0;
        for(int j=0;j<=N-1;j++)
        {
            if(abs(z[i]-z[j])<=0.005)
            {
                all[i]++;
            }
        }
    }
}

// void chong(){//查询那些根的重数
//     for(int i=0;i<=N-1;i++)
//     {
//         all[i]=2;
//         for(int j=1;j<=5;j++)
//         {
//             if(abs(pp(i,j))<=0.005)all[i]++;
//             else break;
//         }
//     }
//     // chong2();
// }

void newton(){//利用牛顿方法进行更精确的求解
    chong();
    complex<double> t;
    for(int i=0;i<=N-1;i++)
    {
        // if(all[i]>bll[i])
        // {
        //     all[i]=bll[i];
        // }
        if(test[i]==0)//精度没有达到，一般是重根，需要进一步迭代
        {
            for(int j=1;j<=num2;j++)//迭代 num2 次
            {
                t=pp(i,all[i]-1)/pp(i,all[i]);
                z[i]=z[i]-t;
                if(abs(t)<=error3)//对于该根的误差达到限度，提前跳出循环
                {
                    test[i]=1;
                    sum++;
                    break;
                }
            }
        }
    }
}

// void newton(){//利用牛顿割线方法进行更精确的求解
//     complex<double> t;
//     for(int i=0;i<=N-1;i++)
//     {
//         if(test[i]==0)//精度没有达到，一般是重根，需要进一步迭代
//         {
//             temp[i]=complex<double>(0.9999*z[i].real(),0.9999*z[i].imag());
//             for(int j=1;j<=num2;j++)//迭代 num2 次
//             {
//                 t=pp(i,0)*(z[i]-temp[i])/(pp(i,0)-tpp(i,0));
//                 temp[i]=z[i];
//                 z[i]=z[i]-t;
//                 if(abs(t)<=error3)//对于该根的误差达到限度，提前跳出循环
//                 {
//                     test[i]=1;
//                     sum++;
//                     break;
//                 }
//             }
//         }
//     }
// }

// bool mysort(complex<double> a,complex<double> b){//自定义排序函数
//     if(abs(a.real()-b.real())<=error1)
//     {
//         if(a.imag()<b.imag())return 0;
//         else return 1;
//     }
//     else if(a.real()<b.real())return 0;
//     else return 1;
// }

bool mysort(complex<double> a,complex<double> b){//自定义排序函数
    if(abs(a.real()-b.real())<=error1)
    {
        if(a.imag()<b.imag())return 0;
        else return 1;
    }
    else if(a.real()<b.real())return 0;
    else return 1;
}

// void getsort(){//对得到的结果进行排序并输出
//     for(int i=0;i<=N-1;i++)//清除共轭
//     {
//         if(z[i].imag()<0)
//         {
//             z[i]=complex<double>(z[i].real(),-z[i].imag());
//         }
//     }
//     sort(&z[0],&z[N],mysort);
//     int u;
//     for(int i=0;i<=N-1;i++)
//     {
//         printf("%lf %lf\n",z[i].real(),z[i].imag());
//         if((abs(z[i+1].imag()-z[i].imag())<0.01)&&(abs(z[i+1].real()-z[i].real())<0.01))//共轭
//         {
//             z[i+1]=complex<double>(z[i].real(),-z[i].imag());
//         }
//     }
// }

void getsort(){//排序并输出结果
    sort(&z[0],&z[N],mysort);//初步排序
    for(int i=0;i<=N-1;i++)
    {
        if(out[i]==0)
        {
            printf("%lf %lf\n",z[i].real(),z[i].imag());
            out[i]=1;
            int u=0;
            for(int j=i+1;j<=N-1;j++)
            {
                if(out[j]==0)
                {
                    if(abs(complex<double>(z[i].real()-z[j].real(),z[i].imag()+z[j].imag()))<0.05)//找共轭
                    {
                        u=1;//存在共轭
                        printf("%lf %lf\n",z[j].real(),z[j].imag());
                        out[j]=1;
                        break;
                    }
                }
            }
        }
    }
}

int main(){
    cin>>N;
    for(int i=N;i>=0;i--)
    {
        cin>>poly[0][i];
        test[i]=0;
    }
    init();//初始化估计解
    derive();
    calculate();//计算结果
    newton();//进一步精确计算部分解
    getsort();//对输出结果进行排序并输出
    return 0;
}