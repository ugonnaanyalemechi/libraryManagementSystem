#pragma once
#include <iostream>

using namespace std;

class EntryManager
{
public:
	void registerLibraryMember();
	string obtainPII(string);
	string createHashedPassword();
	void addNewUserToDatabase(string, string, string, string);
};
