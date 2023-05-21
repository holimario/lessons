#include <iostream>
#include "Example.h"

using namespace std;

void create_example(int n) {
	
	cout << "--------create_example is ready--------\n";
	
	Example* e[10];
	
	for (int i = 0; i < n; i++)
		e[i] = new Example(i);
			
	static Example g(2333);
	for (int q = 0; q < n; q++)
		e[q]->getData();
	for (int q = 0; q < n; q++)
		e[q]->~Example();
	g.getData();
	cout << "--------create_example is over--------\n";
}

Example h(23);

int main() {

	cout << "--------main_function is ready--------\n";

	Example p(233);
		
	create_example(3);
	
	Example y(23333);
	h.getData();
	p.getData();
	y.getData();


	cout << "--------main_function is over---------\n";

	return 0;
}
