#pragma once

using std::string;

class EntryManager
{
private:
	string obtainPII(string);
	bool checkPII(string&, string);
	string createPassword();
	void confirmNewPassword(string);
	bool addNewLibraryMemberToDB(string, string, string, string);
	void completeLibraryMemberRegistration();
	string hideCharacterInput();
	string obtainCredentials(string);
	bool authenticateUser(string, string, string&);
	bool searchUserInDB(string, string, string&);
	void setupSQLPrepStatementForFindingUser();
	void handleInvalidCredentials();
	void authorizeUser(string, string);
	bool checkUserIsLibraryAdmin(string);
	void displayUserAccountEdit();
	void processAccountChanges(int userInput, string email);
	void allocatePreparedAccountEditStatement();
	void applyAccountChanges(string userChange, string changeType);
	bool retrieveUserAccountInfo(string email);
	void displayUserAccountInfo();
public:
	void registerLibraryMember();
	void signInUser();
	void adminEditUserProcess();
	void selfEditUserProcess(string email);
};
