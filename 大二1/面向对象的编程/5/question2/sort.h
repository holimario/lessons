#pragma once
#include "fri.h"

class sort
{
private:
    fri* all;
    int numb=0;
public:
    sort(int n);
    void insert(int n,string s);
    void change(int i);
    void out();
    void manage(fri* f,string s);
    ~sort();
};


