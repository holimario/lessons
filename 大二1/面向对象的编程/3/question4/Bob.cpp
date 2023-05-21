#include "Part.h"
#include "Bob.h"
#include<iostream>

int Bob::run(){
    int sum=0;
    for(int i=0;i<=this->need-1;i++)
    {
        sum+=(this->p[i].getinfo())*(this->p[i].getinfo());
    }
    return sum;
}

ostream& operator<<(ostream& out,Bob& r){
    out<<"Build robot Bob";
    return out;
}

Bob::~Bob(){}