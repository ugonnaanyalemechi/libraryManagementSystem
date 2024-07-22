#pragma once
#include <string>

class EntryManager
{
private:
	std::string obtainPII(std::string);
	void checkPII(std::string&, std::string);
	std::string createPassword();
	void confirmNewPassword(std::string);
	void addNewLibraryMemberToDB(std::string, std::string, std::string, std::string);
	void completeLibraryMemberRegistration();
	std::string hideCharacterInput();
public:
	void registerLibraryMember();
};
