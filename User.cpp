#include <iostream>
#include <pqxx/pqxx>
#include "User.h"
#include "extern.h"

using namespace std;
MenuManager menuManager2;

User::User() {
	email = "N/A";
	firstName = "N/A";
	lastName = "N/A";
}

User::User(string email, string firstName) {
	this->email = email;
	this->firstName = firstName;
	this->lastName = "N/A";
}

void User::signOut() {
	delete this;
	user = nullptr;
	menuManager2.showWelcomeMenu();
}

string User::getEmail() {
	return email;
}

string User::getFirstName() {
	return firstName;
}

string User::getlastName() {
	return lastName;
}

void User::setEmail(string newEmail) {
	email = newEmail;
}

void User::setFirstName(string newFirstName) {
	firstName = newFirstName;
}

void User::setLastName(string newLastName) {
	lastName = newLastName;
}

