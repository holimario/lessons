#include"School.h"
#include"Student.h"
#include<iostream>
using namespace std;

School::School(int n)
{
    Student* p=new Student[n];
    data=p;
}

void School::add_member(Student s)
{
    data[num].name=s.name;
    data[num].grade=s.grade;
    data[num].province=s.province;
    data[num].time=s.time;
    data[num].sid=s.sid;
    num++;
}

string School::operator[] (int sid)
{
    for(int i=0;i<num;i++)
    {
        if(data[i].sid==sid)
        {
            return data[i].name+"-"+data[i].time+"-"+to_string(data[i].grade)+"-"+to_string(data[i].sid)+"\n";
        }
    }
    return "Not Found\n";
}

string School::operator[] (string name)
{
    for(int i=0;i<num;i++)
    {
        if(data[i].name==name)
        {
            return data[i].name+"-"+data[i].time+"-"+to_string(data[i].grade)+"-"+to_string(data[i].sid)+"\n";
        }
    }
    return "Not Found\n";
}

string School::operator[] (char province)
{
    int k=-1;
    for(int i=0;i<num;i++)
    {
        if(data[i].province==province)
        {
            if(k==-1)
            {
                k=i;
            }
            if(data[i]>data[k])
            {
                k=i;
            }
        }
    }
    if(k==-1)
    {
        return "Not Found\n";
    }
    else
    {
        return data[k].name+"-"+data[k].time+"-"+to_string(data[k].grade)+"-"+to_string(data[k].sid)+"\n";
    }
}

School::~School()
{
    delete[] data;
}