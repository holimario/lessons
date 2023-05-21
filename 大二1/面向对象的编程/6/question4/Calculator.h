#pragma once
#include"PerformStrategy.h"
#include"LevelStrategy.h"

class Calculator
{
private:
    LevelStrategy* le;
    PerformStrategy* per;
public:
    Calculator(LevelStrategy* l,PerformStrategy* p);
    int get_base();
    int get_total(int b);
    ~Calculator(){};
};

Calculator::Calculator(LevelStrategy* l,PerformStrategy* p)
{
    le=l;
    per=p;
}

int Calculator::get_base(){
    return le->getsala();
}

int Calculator::get_total(int b){
    return per->cal(b);
}
