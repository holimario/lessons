#include "Part.h"
#include <iostream>
using namespace std;

Part::Part(){
    i=0;
}

int Part::getinfo(){
    return this->i;
}

Part::Part(int k){
    i=k;
}

Part::Part(const Part& k){
    i=k.i;
}

Part::~Part(){}

Robot::Robot(int k){
    need=k;
    num=0;
    p=new Part[k];
}

bool Robot::is_full(){
    return (num==need);
}

void Robot::add_part(const Part& k){
    num++;
    this->p[num-1]=std::move(k);
}

Robot::~Robot(){
    delete []p;
}