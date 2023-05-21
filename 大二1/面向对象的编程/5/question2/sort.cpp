#include"sort.h"
#include<iostream>
using namespace std;

void sort::insert(int n,string s){
    for(int i=0;i<=numb;i++)
    {
        if(all[i].id==n)
        {
            manage(&(all[i]),s);
            change(i);
            return;
        }
    }
    all[numb].id=n;
    manage(&(all[numb]),s);
    numb++;
    return;
}

void sort::change(int i){
    int p,t;
    string* l;
    p=all[i].id;
    l=all[i].talk;
    t=all[i].talknum;
    for(int q=i+1;q<numb;q++)
    {
        all[q-1].id=all[q].id;
        all[q-1].talk=all[q].talk;
        all[q-1].talknum=all[q].talknum;
    }
    all[numb-1].id=p;
    all[numb-1].talk=l;
    all[numb-1].talknum=t;
    return;
}

void sort::out(){
    for(int i=numb-1;i>=0;i--)
    {
        cout<<all[i].id<<endl;
        all[i].gettalk();
    }
}

sort::sort(int n)
{
    all=new fri[n];
}

sort::~sort()
{
    delete[] all;
}

void sort::manage(fri* f,string s)
{
    int i;
    for(;s.find("/")!=-1;)
    {
        i=s.find("/");
        f->input(s.substr(0,i));
        s.erase(0,i+1);
    }
    f->input(s);
}