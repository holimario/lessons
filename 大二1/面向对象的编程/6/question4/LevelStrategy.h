#pragma once

class LevelStrategy
{
protected:
    int salary;
public:
    LevelStrategy(){};
    virtual int getsala()=0;
    ~LevelStrategy();
};

class P1LStrategy:public LevelStrategy
{
private:
    int salary;
public:
    P1LStrategy():salary(2000){};
    int getsala(){return salary;};
    ~P1LStrategy(){};
};

class P2LStrategy:public LevelStrategy
{
private:
    int salary;
public:
    P2LStrategy():salary(5000){};
    int getsala(){return salary;};
    ~P2LStrategy(){};
};

class P3LStrategy:public LevelStrategy
{
private:
    int salary;
public:
    P3LStrategy():salary(10000){};
    int getsala(){return salary;};
    ~P3LStrategy(){};
};