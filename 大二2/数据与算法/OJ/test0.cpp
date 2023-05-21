#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int main()
{
    default_random_engine e(time(0));
    uniform_real_distribution<double> x(0,1);
    uniform_real_distribution<double> y(0,1);
    int sum=0;
    for(int i=1;i<=10000;i++)
    {
        double a=x(e);
        double b=y(e);
        if(cos(3.141592653*a)+sin(3.141592653*b)>=0&&cos(3.141592653*a)+sin(3.141592653*b)<=1)
        {
            sum++;
        }
    }
    double out=(double)sum/10000;
    cout<<"P="<<out<<endl;
    return 0;
}