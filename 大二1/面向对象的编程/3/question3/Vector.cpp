#include"Vector.h"
#include<iostream>

using namespace std;

Vector::Vector(int n){
    this->array=new Node[n];
    this->capacity=n;
    this->len=0;
}

Vector::~Vector(){
    delete []array;
}

Vector::Vector(const Vector & other){
    this->array=new Node[other.capacity];
    this->capacity=other.capacity;
    this->len=other.len;
    for(int i=0;i<other.len;i++)
    {
        this->array[i]=other.array[i];
    }
}

Vector::Vector(Vector && other){
    this->capacity=other.capacity;
    this->len=other.len;
    this->array=other.array;
    other.array=nullptr;
}

Vector& Vector:: operator=(const Vector & other){
    if(this->capacity<=other.len)
    {
        delete []array;
        this->array=new Node[other.len];
        this->capacity=other.len;
    }
    this->len=other.len;
    this->capacity=other.capacity;
    for(int i=0;i<other.len;i++)
    {
        this->array[i]=other.array[i];
    }
    return *this;
}

Vector& Vector:: operator=(Vector && other){
    delete []array;
    this->len=other.len;
    this->array=other.array;
    other.array=nullptr;
    other.len=0;
    other.capacity=0;
    return *this;
}

Node& Vector:: operator [] (int pos){
    return this->array[pos];
}

void Vector::append(int value){
    Node add(value);
    if(this->len!=this->capacity)
    {
        this->array[len]=std::move(add);
        this->len++;
    }
    else
    {
        Vector p(this->capacity+1);
        for(int i=0;i<=this->len;i++)
        {
            p[i]=std::move(this->array[i]);
        }
        p.len=capacity+1;
        p.array[len]=std::move(add);
        *this=std::move(p);
    }
}

void Vector::insert(int pos, int value){
    Node j(value);
    if(this->len!=this->capacity)
    {
        Vector w(std::move(*this));
        for(int i=this->len;i!=pos;i--)
        {
        w.array[i]=std::move(w.array[i-1]);
        }
        w.array[pos]=std::move(j);
        *this=std::move(w);
        this->len++;
    }
    else
    {
        Vector w(this->capacity+1);
        w.capacity=this->capacity+1;
        for(int i=this->len;i!=pos;i--)
        {
        w.array[i]=std::move(this->array[i-1]);
        }
        for(int i=0;i!=pos;i++)
        {
        w.array[i]=std::move(this->array[i]);
        }
        w.array[pos]=std::move(j);
        w.len=this->len;
        *this=std::move(w);
        this->len++;
    }
}

void Vector::swap(int pos1, int pos2){
    Node h=std::move(this->array[pos1]);
    this->array[pos1]=std::move(this->array[pos2]);
    this->array[pos2]=std::move(h);
}

void Vector::dilatation(){
    Vector q(2*this->capacity);
    q.len=this->len;
    for(int i=0;i<this->len;i++)
    {
        q.array[i]=std::move(this->array[i]);
    }
    *this=std::move(q);
}

int Vector::getlen(){
    return this->len;
}