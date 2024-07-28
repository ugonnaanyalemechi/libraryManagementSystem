#include <iostream>
#include <pqxx/pqxx>
#include "User.h"
#include "extern.h"

using namespace std;

User::User() {}

User::User(string email, string firstName) {
	this->email = email;
	this->firstName = firstName;
}

void User::signOut() {
	delete this;
	user = nullptr;
	menuManager.showWelcomeMenu();
}

string User::getEmail() {
	return email;
}

string User::getFirstName() {
	return firstName;
}