#pragma once
#include"what.h"

class Alien:public WhatCanMotion, public WhatCanSpeak
{
private:
    string name;
public:
    Alien(string s);
    void speak(){cout<<name<<" is"<<" speaking"<<endl;}
    void stop(){cout<<name<<" stops"<<endl;}
    void motion(){cout<<name<<" is"<<" moving"<<endl;}
    void doSpeak(Alien& a){a.speak();a.stop();}
    void doMotion(Alien& a){a.motion();a.stop();}
    ~Alien();
};

Alien::Alien(string s)
{
    name=s;
}

Alien::~Alien()
{
}
