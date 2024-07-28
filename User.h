#pragma once
#include <iostream>

using std::string;

class User
{
protected:
	string email, firstName;
public:
	User();
	User(string, string);
	string getEmail();
	string getFirstName();
};