#ifndef __STUDENT__
#define __STUDENT__
#include<iostream>
using namespace std;

class Student
{
private:

public:
    Student();
    string name;
    char province;
    int grade;
    string time;
    int sid;
    ~Student();
};

bool operator >(Student a,Student b);
istream& operator >>(istream& in,Student& s);

#endif