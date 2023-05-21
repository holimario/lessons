#pragma once
#include "operation.h"
#include "node.h"

class Other: public OperationNodeTwo
{
private:
    int type;
public:
    Other(string name, Node *x1, Node *x2,int i):OperationNodeTwo(name,x1,x2),type(i){};
    void UpdateValue();
    void calc();
    ~Other(){};
};

