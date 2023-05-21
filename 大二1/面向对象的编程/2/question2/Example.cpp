#include <iostream>
#include "Example.h"

using namespace std;

int Example::n=1;

Example::Example(int data) {
	k=n;
	da=data;
	cout<<"Example #"<<k<<" is created"<<endl;
	n++;
}

void Example::getData() {
	cout<<"The data of Example #"<<k<<" is "<<da<<endl;
}

Example::~Example() {
	cout<<"Example #"<<k<<" is destroyed"<<endl;
}