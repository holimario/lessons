#include "LinearDataStruct.h"

void LinearDataStruct::push(int k){
    if(this->idx_end==max_n)
    {
        change();
    }
    data[idx_end]=k;
    idx_end++;
    n++;
}

int LinearDataStruct::max_size(){
    return this->max_n;
}

int LinearDataStruct::size(){
    return this->n;
}

void LinearDataStruct::change(){
    for(int i=0;i<=this->n-1;i++)
    {
        this->data[i]=this->data[i+this->idx_begin];
    }
    this->idx_begin=0;
    this->idx_end=this->n;
}