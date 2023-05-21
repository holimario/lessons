#pragma once
#include<vector>
#include<list>
#include<functional>
#include<iostream>
using namespace std;

template <class T>
class Myqueriable
{
private:
    
public:
    Myqueriable(int n);
    T* num;
    int siz;
    int size();
    T operator[](int k);
    template<class funcc>
    Myqueriable& where(funcc func);
    template<class funcc>
    Myqueriable& apply(funcc func);
    T sum();
    ~Myqueriable();
};

template <class T>
Myqueriable<T>::Myqueriable(int n){
    siz=n;
    num=new T[n];
}

template<class T>
int Myqueriable<T>::size(){
    return siz;
}

template<class T>
T Myqueriable<T>::operator[](int k){
    return num[k];
}

Myqueriable<int>& from(std::list<int> p){
    Myqueriable<int>* my=new Myqueriable<int>(p.size());
    int k=0;
    for(auto i=p.begin();i!=p.end();++i)
    {
        my->num[k]=*i;
        k++;
    }
    return *my;
}

Myqueriable<float>& from(std::vector<float> p){
    Myqueriable<float>* my=new Myqueriable<float>(p.size());
    int k=0;
    for(auto i=p.begin();i!=p.end();++i)
    {
        my->num[k]=*i;
        k++;
    }
    return *my;
}

Myqueriable<float>& from(std::list<float> p){
    Myqueriable<float>* my=new Myqueriable<float>(p.size());
    int k=0;
    for(auto i=p.begin();i!=p.end();++i)
    {
        my->num[k]=*i;
        k++;
    }
    return *my;
}


Myqueriable<int>& from(std::vector<int> p){
    Myqueriable<int>* my=new Myqueriable<int>(p.size());
    int k=0;
    for(auto i=p.begin();i!=p.end();++i)
    {
        my->num[k]=*i;
        k++;
    }
    return *my;
}

template<class T> template<class funcc>
Myqueriable<T>& Myqueriable<T>::where(funcc func){
    Myqueriable<T>* my=new Myqueriable<T>(siz);
    int k=0;
    for(int i=0;i<siz;i++)
    {
        if(func(num[i])==1)
        {
            my->num[k]=num[i];
            k++;
        }
    }
    my->siz=k;
    return *my;
}

template<class T> template<class funcc>
Myqueriable<T>& Myqueriable<T>::apply(funcc func){
    Myqueriable<T>* my=new Myqueriable<T>(siz);
    for(int i=0;i<siz;i++)
    {
        my->num[i]=func(num[i]);
    }
    return *my;
}

template<class T>
T Myqueriable<T>::sum(){
    T p=0;
    for(int i=0;i<siz;i++)
    {
        p+=num[i];
    }
    return p;
}

template<class T>
Myqueriable<T>::~Myqueriable(){
    delete []num;
}