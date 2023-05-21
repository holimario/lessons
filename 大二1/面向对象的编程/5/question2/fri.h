#pragma once
#include <string>
using namespace std;

class fri
{
private:
public:
    string* talk=new string[10];
    int id;
    int talknum;
    fri(int x=-1);
    void input(string s);
    void gettalk();
    ~fri();
};



