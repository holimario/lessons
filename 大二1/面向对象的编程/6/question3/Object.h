#pragma once
#include <list>
#include <iostream>
#include<memory>
#include "CustomClass.h"
using namespace std;

class Object;
class Content
{
	public:
	virtual void output(std::ostream& out){ //virtual function for output
		std::cout << "the operator is not supported for this type." << std::endl;
	}
	virtual Content& operator+=(int x){};
	virtual Content& operator+=(string x){};
	virtual Object& get(int i){};
};

class IntContent: public Content
{
private:
	int x;
public:
	IntContent(int _x): x(_x) {}
	void output(std::ostream& out){ //???
		out << x;
	}
	IntContent& operator+=(int y){
		x=x+y;
		return *(this);
	}
};

class StringContent: public Content
{
private:
	std::string x;
public:
	StringContent(std::string _x): x(_x) {}
	void output(std::ostream& out){  //???
		out << x;
	}
	StringContent& operator+=(string y){
		x=x+y;
		return *(this);
	}
};

// The following codes are not working

class VectorContent: public Content
{
private:
	std::vector<Object> x; //Object is not defined???
public:
	VectorContent(const std::vector<Object>& _x): x(_x) {}
	Object& get(int i){return x[i];}
};

class CustomContent: public Content
{
private:
	CustomClass x;
public:
	CustomContent(const CustomClass& _x): x(_x) {}

};

class Object
{
private:
	shared_ptr<Content> pt;

public:
	Object() {}
	Object(int x) {
		shared_ptr<Content> p(new IntContent(x)); // where to delete? maybe use std::shared_ptr?
		pt=p;
	}
	Object(const std::string &x){
		shared_ptr<Content> p(new StringContent(x));
		pt=p;
	}
	// The following codes are not working
	Object(const std::vector<Object> &x){
		shared_ptr<Content> p(new VectorContent(x));
		pt=p;
	}
	Object(const CustomClass &x){
		shared_ptr<Content> p(new CustomContent(x));
		pt=p;
	}

	friend std::ostream& operator<<(std::ostream& out, const Object& obj) {
		obj.pt->output(out);
		return out;
	}

	Object& operator+=(int y){
		pt->operator+=(y);
		return *this;
	}
	Object& operator+=(const std::string &y){
		pt->operator+=(y);
		return *this;
	}

	Object& operator[](int i){
		return pt->get(i);
	}

};
