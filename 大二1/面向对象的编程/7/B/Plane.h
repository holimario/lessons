#pragma once
#include"Vehicle.h"
#include<iostream>
using namespace std;

class Plane:public Vehicle
{
private:
    /* data */
public:
    Plane(){
        set_max_wheel_num(3);
        set_max_wing_num(2);
    };
    void run(){
        cout << "I am running and flying" << endl;
    }
};


