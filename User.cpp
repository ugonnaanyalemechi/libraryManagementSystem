#include <iostream>
#include <pqxx/pqxx>
#include "User.h"
#include "extern.h"

using namespace std;

User::User() {}

User::User(string email) {
	this->email = email;
}

string User::getEmail() {
	return email;
}