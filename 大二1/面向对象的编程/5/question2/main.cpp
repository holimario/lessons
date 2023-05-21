#include"sort.h"
#include<iostream>
#include<string>

using namespace std;

int main(){
    sort h(1000);
    int j;
    int r;
    string s;
    cin>>j;
    for(int i=1;i<=j;i++)
    {
        cin>>r>>s;
        h.insert(r,s);
    }
    cin>>j;
    for(int i=1;i<=j;i++)
    {
        cin>>r>>s;
        h.insert(r,s);
    }
    h.out();
}