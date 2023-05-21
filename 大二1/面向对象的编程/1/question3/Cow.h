#ifndef COW_H
#define COW_H

#include<string>
using namespace std;


class Cow
{
public:
    Cow(){};
    Cow(string a,int b,int c,int d);
    string name;
    int low;
    int high;
    int milk;
    int eat=0;
    int get=0;
    int fan=0;
    int left=0;
    float sum=0;
};

#endif