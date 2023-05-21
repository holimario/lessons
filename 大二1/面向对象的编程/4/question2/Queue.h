#ifndef __QUEUE
#define __QUEUE

#include "LinearDataStruct.h"
#include "IteratorBase.h"

class Queue: public LinearDataStruct {

public:

    class Iterator: public IteratorBase {
    public:
        int operator* ();
        bool operator!= (const Iterator& b);
        bool operator!= (Iterator&& b);
        Iterator& operator++ (int);
        using IteratorBase::IteratorBase;
    };

    Iterator begin();
    Iterator end();
    int pop();
    using LinearDataStruct::LinearDataStruct;
};


#endif