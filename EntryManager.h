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

	std::string obtainCredentials(std::string);
	void authenticateUser(std::string, std::string);
	bool searchUserInDB(std::string, std::string);
	void handleInvalidCredentials();
	void authorizeUser(std::string);
	bool checkUserIsLibraryAdmin(std::string);

public:
	void registerLibraryMember();
	void signInUser();
};
