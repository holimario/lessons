#ifndef FARM_H
#define FARM_H
#include"Cow.h"
#include<string>
using namespace std;

class Cow;

class Farm
{
public:
    int number; 
    int i=0;
    int day=0;
    Farm(int x);
    Cow* pig=new Cow[100];
    void addCow(Cow cow);
    void supply(string a,int b);
    void startMeal();
    void produceMilk();
    float getMilkProduction();
    ~Farm(){};
};

#endif
