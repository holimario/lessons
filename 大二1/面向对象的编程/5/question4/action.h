#include"animal.h"
#include<iostream>
#include <string>
#include <vector>
using namespace std;

void action(Animal* animal, std::vector<Dog> & dogzone, std::vector<Bird> & birdzone){
    if(dynamic_cast<Dog*>(animal)==nullptr)
    {
        birdzone.push_back(move(*(dynamic_cast<Bird*>(animal))));
        return;
    }
    else
    {
        dogzone.push_back(move(*(dynamic_cast<Dog*>(animal))));
        return;
    }
}