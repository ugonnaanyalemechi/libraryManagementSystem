#pragma once
#include <iostream>

using std::string;

class User
{
protected:
	string email;
public:
	User();
	User(string);
	string getEmail();
};