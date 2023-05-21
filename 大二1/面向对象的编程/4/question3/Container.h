#pragma once
#include <iostream>
#include <string>

template <typename A> class Container
{
private:
    int data_x[1000];
    int data_y[1000];
    A name[1000];
    int k;
public:
    Container():k(0){};
    void insert(int x,int y,A sb);
    A* find(int x,int y);
    ~Container(){};
};

template <typename A>
void Container<A>::insert(int x,int y,A sb){
    this->data_x[k]=x;
    this->data_y[k]=y;
    this->name[k]=sb;
    k++;
}

template <typename A>
A* Container<A>::find(int x,int y){
    for(int i=0;i<k;i++){
        if((this->data_x[i]==x)&&(this->data_y[i]==y))
        {
            A* p=&name[i];
            return p;
        }
    }
    return nullptr;
}
