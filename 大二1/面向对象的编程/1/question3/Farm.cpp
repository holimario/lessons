#include"Farm.h"
#include"Cow.h"
#include<iostream>
#include<string>
using namespace std;

Farm::Farm(int x)
{
    number=x-1;
}

void Farm::addCow(Cow cow)
{
    pig[i].name=cow.name;
    pig[i].low=cow.low;
    pig[i].high=cow.high;
    pig[i].milk=cow.milk;
    i++;
}

void Farm::supply(string a,int b)
{
    int o;
    for(o=0;o<=number;o++)
    {
        if(pig[o].name==a)
        {
            pig[o].get=b;
        }
    }
}

void Farm::startMeal()
{
    int d;
    for(d=0;d<=number;d++)
    {
        if(pig[d].get+pig[d].left>pig[d].high)
        {
            pig[d].eat=pig[d].high;
            pig[d].left=pig[d].get+pig[d].left-pig[d].high;
            pig[d].get=0;
        }
        else
        {
            pig[d].eat=pig[d].get+pig[d].left;
            pig[d].left=0;
            pig[d].get=0;
        }
    }
}

void Farm::produceMilk()
{
    int y,x;
    for(y=0;y<=number;y++)
    {
        if(pig[y].eat>=pig[y].low)
        {
            pig[y].sum+=(float)pig[y].milk;
        }
        else if(pig[y].eat==0)
        {
            pig[y].sum+=0;
        }
        else
        {
            pig[y].sum+=(float)pig[y].milk/2;
        }
        pig[y].eat=0;
    }
}

float Farm::getMilkProduction()
{
    int y;
    float Sum=0;
    for(y=0;y<=number;y++)
    {
        Sum+=pig[y].sum;
    }
    return Sum;
}