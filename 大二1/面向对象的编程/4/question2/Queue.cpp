#include "Queue.h"

int Queue::Iterator::operator* (){
    return this->data[idx];
}

bool Queue::Iterator::operator!= (const Queue::Iterator& b){
    if((this->data==b.data)&&(this->idx==b.idx))
    {
        return 0;
    }
    return 1;
}

bool Queue::Iterator::operator!= (Queue::Iterator&& b){
    if((this->data==b.data)&&(this->idx==b.idx))
    {
        return 0;
    }
    return 1;
}

Queue::Iterator& Queue::Iterator::operator++ (int){
    this->idx++;
    return *this;
}



Queue::Iterator Queue::begin(){
    return Queue::Iterator(this->data,this->idx_begin);
}

Queue::Iterator Queue::end(){
    return Queue::Iterator(this->data,this->idx_end);
}

int Queue::pop(){
    this->idx_begin++;
    this->n--;
    return this->data[idx_begin-1];
}