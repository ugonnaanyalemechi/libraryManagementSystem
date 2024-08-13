#pragma once
#include <iostream>

using std::string;

class User
{
protected:
	string email, firstName, lastName;
public:
	User();
	User(string, string);
	void signOut();
	string getEmail();
	string getFirstName();
	string getlastName();
	void setEmail(string newEmail);
	void setFirstName(string newFirstName);
	void setLastName(string newLastName);
};