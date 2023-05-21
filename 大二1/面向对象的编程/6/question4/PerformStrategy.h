#pragma once

class PerformStrategy
{
private:
    double perform;
public:
    PerformStrategy(){};
    virtual int cal(int b)=0;
    ~PerformStrategy();
};


class sPerformStrategy:public PerformStrategy
{
private:
    double perform;
public:
    sPerformStrategy(double n):perform(n){};
    int cal(int b){return (b+1000);};
    ~sPerformStrategy(){};
};

class mPerformStrategy:public PerformStrategy
{
private:
    double perform;
public:
    mPerformStrategy(double n):perform(n){};
    int cal(int b){return (b+b*perform);};
    ~mPerformStrategy(){};
};

class lPerformStrategy:public PerformStrategy
{
private:
    double perform;
public:
    lPerformStrategy(double n):perform(n){};
    int cal(int b){return (b+2*b*perform);};
    ~lPerformStrategy(){};
};