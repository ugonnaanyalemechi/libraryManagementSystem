#include <iostream>
#include <pqxx/pqxx>
#include "Staff.h"
#include "extern.h"

using namespace std;

Staff::Staff(string email, string firstName) {
	this->email = email;
	this->firstName = firstName;
}