#include <iostream>
#include <pqxx/pqxx>
#include "Staff.h"
#include "extern.h"

using namespace std;
MenuManager menuManager3;

Staff::Staff(string email, string firstName) {
	this->email = email;
	this->firstName = firstName;
}

void Staff::staffSignOut() {
	delete this;
	admin = nullptr;
	menuManager3.showWelcomeMenu();
}