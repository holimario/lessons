#pragma once
#include "Part.h"
#include<iostream>
using namespace std;

class Bob :public Robot
{
public:
    using Robot::Robot;
    int run();
    friend ostream& operator<< (ostream& out,Bob& r);
    ~Bob();
};


