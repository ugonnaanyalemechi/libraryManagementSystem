#pragma once
#include <iostream>
#include "User.h";

using std::string;

class Staff :
	public User
{
public:
	Staff(string, string);
};