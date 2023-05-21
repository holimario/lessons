#include"Instruction.h"




class Ins:public Instruction
{
private:
    int i;
    int sum;
    double dou;
public:
    Ins();
    Ins(int u);
    void add(int k);
    void ad(int p);
    void operator+= (int q);
    void operator+= (double q);
    void apply(std::vector<int> &vec);
    void apply(std::vector<double> &vec);
    void output();
    ~Ins();
};


void Ins::operator+= (int q){
    sum=q;
}

void Ins::operator+= (double q){
    sum=q;
}

void Ins::ad(int p){
    sum=p;
}

Ins::Ins(){
    i=0;
    sum=0;
}

Ins::Ins(int u){
    i=u;
}

void Ins::add(int m){
    sum=m;
}

void Ins::apply(std::vector<int> &vec){
    vec[i]+=sum;
}

void Ins::apply(std::vector<double> &vec){
    vec[i]+=sum;
}

void Ins::output(){
    ;
}

class MagicArray
{
private:
    int length;
    Ins* p=new Ins[1000];
    int x;
public:
    MagicArray(int k):length(k),x(0){};
    void getInstructions();
    Ins& operator[](int i){
    p[x].add(i);
    x++;
    return p[x];
}; 
    void apply(std::vector<int> &vec);
    void apply(std::vector<double> &vec);
    ~MagicArray();
};

void MagicArray::getInstructions(){
    ;
}

void MagicArray::apply(std::vector<int> &vec){
    for(int i=0;i<x;i++){
        p[i].apply(vec);
    }
}

void MagicArray::apply(std::vector<double> &vec){
    for(int i=0;i<x;i++){
        p[i].apply(vec);
    }
}
