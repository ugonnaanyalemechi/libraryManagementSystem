#pragma once
#include <string>
#include <pqxx/pqxx>

using std::string;

class EntryManager
{
private:
	string obtainPII(string);
	void checkPII(string&, string);
	string createPassword();
	void confirmNewPassword(string);
	void addNewLibraryMemberToDB(string, string, string, string);
	void completeLibraryMemberRegistration();
	string hideCharacterInput();
	string obtainCredentials(string);
	void authenticateUser(string, string, string&);
	bool searchUserInDB(string, string, string&);
	void setupSQLPrepStatementForFindingUser();
	void handleInvalidCredentials();
	void authorizeUser(string, string);
	bool checkUserIsLibraryAdmin(string);
public:
	void registerLibraryMember();
	void signInUser();
};
