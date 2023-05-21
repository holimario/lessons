#include "Stack.h"

int Stack::Iterator::operator* (){
    return this->data[idx];
}

bool Stack::Iterator::operator!= (const Stack::Iterator& b){
    if((this->data==b.data)&&(this->idx==b.idx))
    {
        return 0;
    }
    return 1;
}

bool Stack::Iterator::operator!= (Stack::Iterator&& b){
    if((this->data==b.data)&&(this->idx==b.idx))
    {
        return 0;
    }
    return 1;
}

Stack::Iterator& Stack::Iterator::operator++ (int){
    this->idx++;
    return *this;
}


Stack::Iterator Stack::begin(){
    return Stack::Iterator(this->data,this->idx_begin);
}

Stack::Iterator Stack::end(){
    return Stack::Iterator(this->data,this->idx_end);
}

int Stack::pop(){
    this->idx_end--;
    this->n--;
    return this->data[idx_end];
}