#include"fri.h"
#include<iostream>
using namespace std;

void fri::input(string s)
{
    talknum++;
    string * p=new string[talknum];
    for(int i=0;i<talknum-1;i++)
    {
        p[i]=talk[i];
    }
    delete[] talk;
    p[talknum-1]=s;
    talk=p;
    return;
}

void fri::gettalk()
{
    for(int i=talknum-1;i>=0;i--)
    {
        cout<<talk[i]<<endl;
    }
    return;
}

fri::fri(int x)
{
    id=x;
    talknum=0;
}

fri::~fri()
{
    delete []talk;
}