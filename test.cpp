#include <iostream>
#inlucde "extern.h"

using namespace std;

void printNum() {
	cout << "This was called in test.cpp: " + to_string(num) << endl;
}