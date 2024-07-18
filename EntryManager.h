#pragma once
#include <string>

class EntryManager
{
public:
	void registerLibraryMember();
	std::string obtainPII(std::string);
	void checkFirstLastName(std::string, std::string);
	std::string createPassword();
	void addNewUserToDatabase(std::string, std::string, std::string, std::string);
};
