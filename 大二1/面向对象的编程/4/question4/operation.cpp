#include "operation.h"
#include<iostream>
using namespace std;
OperationNodeTwo::~OperationNodeTwo() = default;

void OperationNodeTwo::calc() {
	// 递归计算
    cout<<"pp1"<<endl;
    input1->calc();		
    input2->calc();		
	// 更新当前节点值 (根据input1和input2的value进行加法/减法)
    UpdateValue();		
}
