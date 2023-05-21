#pragma once
#include<iostream>
using namespace std;

class Part
{
private:
    int i;
public:
    Part(int k);
    Part();
    Part(const Part& k);
    int getinfo();
    ~Part();
};


class Robot
{
private:
    int num;
public:
    Part* p;
    int need;
    Robot(int k);
    bool is_full();
    void add_part(const Part& k);
    ~Robot();
};

