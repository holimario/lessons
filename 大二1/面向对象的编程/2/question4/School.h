#ifndef __SCHOOL__
#define __SCHOOL__
#include"Student.h"
#include<iostream>
using namespace std;

class School
{
private:
    int num=0;
    Student* data;
public:
    School(int n);
    void add_member(Student s);
    string operator[] (int sid);
    string operator[] (string name);
    string operator[] (char province);
    ~School();
};



#endif