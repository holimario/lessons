#include<iostream>
#include<string>
#include"EncryptStrategy.h"
#include"VerificationStrategy.h"
#include"User.h"
using namespace std;

class InsertStrategy:public EncryptStrategy
{
private:
    /* data */
public:
    InsertStrategy(){};
    std::string encode(std::string mes);
    ~InsertStrategy();
};

std::string InsertStrategy::encode(std::string mes){
    string s=mes;
    int i=1;
    for(i;i<s.size();i+=2){
        s.insert(i, "#"); 
    }
    if(i==s.size())
    {
        s.push_back('#');
    }
    return s;
}

class InvertStrategy:public EncryptStrategy
{
private:
    /* data */
public:
    InvertStrategy(){};
    std::string encode(std::string mes);
    ~InvertStrategy();
};

std::string InvertStrategy::encode(std::string mes){
    string s;
    for(int i=mes.size()-1;i>=0;i--){
        s.push_back(mes[i]);
    }
    return s;
}

class PrefixStrategy:public VerificationStrategy
{
private:
    /* data */
public:
    PrefixStrategy(){};
    std::string verify(std::string mes);
    ~PrefixStrategy();
};

std::string PrefixStrategy::verify(std::string mes){
    string s;
    s=mes.substr(0,3);
    return s;
}

class IntervalStrategy:public VerificationStrategy
{
private:
    /* data */
public:
    IntervalStrategy(){};
    std::string verify(std::string mes);
    ~IntervalStrategy();
};

std::string IntervalStrategy::verify(std::string mes){
    string s;
    for(int i=0;i<mes.size();i+=2)
    {
        s.push_back(mes[i]);
    }
    return s;
}

class UserProxy
{
private:
    EncryptStrategy* e;
    VerificationStrategy* v;
    RealUser* u;
public:
    UserProxy(RealUser* uu,EncryptStrategy* ee,VerificationStrategy* vv);
    void sendMessage(std::string mes);
    ~UserProxy();
};

UserProxy::UserProxy(RealUser* uu,EncryptStrategy* ee,VerificationStrategy* vv){
    e=ee;
    v=vv;
    u=uu;
}

void UserProxy::sendMessage(std::string mes){
    string m;
    string c;
    m=e->encode(mes);
    c=v->verify(mes);
    u->sendMessage(m);
    cout<<c<<endl;
}

