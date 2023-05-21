#ifndef PARSER_H
#define PARSER_H
#include<string>
using namespace std;


class Parser
{
private:

public:
    Parser(){};
    int i=0;
    void add_argument(string a,int b,string c);
    int get_argument(string a);
    void init(int a,char** b);
    int ifnum(char *a);
    string* target=new string[100];
    int* num=new int[100];
    string* info=new string[100];
    void usage();
    string transfer(int n);
    string change(string a);
    ~Parser(){};
};




#endif