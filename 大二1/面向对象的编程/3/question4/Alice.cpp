#include "Part.h"
#include "Alice.h"
#include<iostream>
using namespace std;

int Alice::run(){
    int sum=0;
    for(int i=0;i<=this->need-1;i++)
    {
        sum+=this->p[i].getinfo();
    }
    return sum;
}

ostream& operator<<(ostream& out,Alice& r){
    out<<"Build robot Alice";
    return out;
}

Alice::~Alice(){}