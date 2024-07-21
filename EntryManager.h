#pragma once
#include <string>

class EntryManager
{
private:
	std::string obtainPII(std::string);
	void checkPII(std::string&, std::string);
	std::string createPassword();
	void addNewLibraryMemberToDB(std::string, std::string, std::string, std::string);
	void completeLibraryMemberRegistration();
	void obtainLoginCredentials(std::string&, std::string&);
	void authenticateUser(std::string, std::string);
public:
	void registerLibraryMember();
	void signInUser();
};
