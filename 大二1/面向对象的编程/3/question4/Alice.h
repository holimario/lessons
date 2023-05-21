#pragma once
#include "Part.h"
#include<iostream>
using namespace std;

class Alice : public Robot
{
public:
    using Robot::Robot;
    friend ostream& operator<< (ostream& out,Alice& r);
    int run();
    ~Alice();
};


