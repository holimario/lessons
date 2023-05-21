#include"Student.h"
#include<iostream>
#include<string.h>
using namespace std;

Student::Student()
{
}

istream& operator >>(istream& in,Student& s)
{
    char g[100];
    string l;
    in>>g;
    l=g;
    int k;
    k=strcspn(g,"-");
    s.name=l.substr(0,k);
    s.province=l[k+1];
    s.grade=l[k+3]-'0';
    s.time=l.substr(k+5,4);
    s.sid=stoi(l.substr(k+10,l.length()-k-10));
    return in;
}

bool operator >(Student a,Student b)
{
    if(stoi(a.time)>stoi(b.time))
    {
        return 1;
    }
    else if(a.time==b.time)
    {
        if(a.sid>b.sid)
        {
            return 1;
        }
    }
    return 0;
}

Student::~Student()
{
}