#pragma once
#include "Pair.h"
#include<iostream>
using namespace std;

class Map{
    Pair * data;
    int sz;
public:
    Map(int n);
    int operator[](string s) const;
    int& operator[](string s);
    int size();
    ~Map();
};