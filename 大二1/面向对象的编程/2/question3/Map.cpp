#ifndef __MAP__
#define __MAP__
#include"Map.h"
#include<iostream>
using namespace std;

Map::Map(int n)
{
    Pair* p=new Pair[n];
    this->data=p;
    sz=0;
}

int Map::operator[](string s) const
{
    for(int i=0;i<sz;i++)
    {
        if(this->data[i].hasKey(s)==1)
        {
            return this->data[i].getVal();
        }
    }
    return 0;
}

int& Map::operator[](string s)
{
    for(int i=0;i<sz;i++)
    {
        if(this->data[i].hasKey(s)==1)
        {
            return this->data[i].getVal();
        }
    }
    this->data[sz].reset(s,0);
    sz++;
    return this->data[sz-1].getVal();
}

int Map::size()
{
    return sz;
}

Map::~Map()
{
    delete[] data;
}


#endif