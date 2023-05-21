#pragma once
#include<iostream>
using namespace std;

class Vehicle
{
private:
    int wheel;
    int wing;
public:
    Vehicle();
    void set_max_wheel_num(int x);
    void set_max_wing_num(int x);
    void add_wing();
    void add_wheel();
    bool finished();
    void run();
    ~Vehicle();
};

Vehicle::Vehicle()
{
    wheel=0;
    wing=0;
}

Vehicle::~Vehicle()
{
}

void Vehicle::set_max_wheel_num(int x){
    wheel=x;
}

void Vehicle::set_max_wing_num(int x){
    wing=x;
}

void Vehicle::add_wing(){
    wing=wing-1;
}

void Vehicle::add_wheel(){
    wheel=wheel-1;
}

bool Vehicle::finished(){
    if((wheel==0)&&(wing==0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Vehicle::run(){
    cout << "I am running" << endl;
}