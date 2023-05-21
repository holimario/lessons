#include "other.h"
#include<iostream>

using namespace std;


void Other::UpdateValue(){
    if(this->type==1)
    {
        this->value_=this->input1->value()+this->input2->value();
    }
    else
    {
        this->value_=this->input1->value()-this->input2->value();
    }
    return;
}

void Other::calc() {
	// 递归计算
    input1->calc();		
    input2->calc();		
	// 更新当前节点值 (根据input1和input2的value进行加法/减法)
    UpdateValue();		
}