#pragma once
#include <string>

class EntryManager
{
public:
	void registerLibraryMember();
	std::string obtainPII(std::string);
	void checkPII(std::string&, std::string);
	std::string createPassword();
	void addNewLibraryMemberToDB(std::string, std::string, std::string, std::string);
	void completeLibraryMemberRegistration();
};
