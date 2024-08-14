#include <iostream>
#include <cctype> // used for the isalpha() & isspace() functions
#include <windows.h> // used for the Sleep() function
#include <conio.h> // used for the _getch() function
#include <algorithm>
#include "EntryManager.h"
#include "sha256.h"
#include "extern.h"

using namespace std;
MenuManager menuManager1;

void EntryManager::registerLibraryMember() {
	string firstName, lastName, email, passHash;
	bool libraryMemberAddedToDB = false;

	cout << "--------------------- Registration ---------------------\n\n";
	cout << "We're so glad you want to join us! We just need a few details from you to create an account!\n\n";
	
	firstName = obtainPII("first name");
	lastName = obtainPII("last name");
	email = obtainPII("email address");
	passHash = createPassword();
	
	libraryMemberAddedToDB = addNewLibraryMemberToDB(firstName, lastName, email, passHash);
	
	if (libraryMemberAddedToDB) {
		completeLibraryMemberRegistration();
	}
	else {
		registerLibraryMember();
	}
		
}

string EntryManager::obtainPII(string infoType) { // PII = personally identifiable information
	string userInput;
	bool newUserPIIValid = false;

	while (newUserPIIValid == false) {
		cout << "Enter your " << infoType << ": "; getline(cin, userInput);
		cout << endl;

		newUserPIIValid = checkPII(userInput, infoType);

		if (newUserPIIValid)
			return userInput;
	}
}

bool EntryManager::checkPII(string &userInput, string infoType) {

	int alphaCount = 0;

	for (char c : userInput) {
		if (isalpha(c))
			alphaCount++;
	}

	if (alphaCount == 0) { // prevents only-whitespace input from being entered
		cout << "Invald input! Please try again!\n\n";
		return false;
	}
	
	if (infoType == "first name" || infoType == "last name") {
		for (int i = 0; i < userInput.length(); i++) {
			if (userInput[0]) // ensures first and last names are capitalized
				userInput[0] = toupper(userInput[0]);
			
			if (isalpha(userInput[i]) || isdigit(userInput[i])) // used to prevent special chars and nums from being entered in names
				return true;
			else {
				cout << "Invald input! Please try again!\n\n";
				return false;
			}
		}
	}
}

string EntryManager::hideCharacterInput() {
	char cString[1000];
	int i = 0;
	char ch;
	while ((ch = _getch()) != '\r') { // read characters until Enter (Enter key has ASCII value '\r')
		if (ch == '\b') { // handle backspace
			if (i > 0) {
				cout << "\b \b"; // move cursor back, overwrite character, move cursor back again
				i--;
			}
		}
		else {
			cString[i++] = ch;
			cout << '*'; // print asterisk for each character
		}
	}
	cString[i] = '\0';
	cout << endl;
	string enteredString = cString;
	return enteredString;
}

string EntryManager::createPassword() {
	string inputtedPassword;

	cout << "Enter password: ";
	inputtedPassword = hideCharacterInput();
	confirmNewPassword(inputtedPassword);
	return sha256(inputtedPassword);
}

void EntryManager::confirmNewPassword(string inputtedPassword) {
	string reenteredPassword;
	cout << "Confirm password: ";
	reenteredPassword = hideCharacterInput();
	cout << endl;

	if (inputtedPassword != reenteredPassword) {
		cout << "Password inputs did not match! Please try again!\n\n";
		createPassword();
	}
}

bool EntryManager::addNewLibraryMemberToDB(string firstName, string lastName, string email, string passHash) {
	try {
		conn->prepare(
			"addNewUser",
			"INSERT INTO users (email, first_name, last_name, pass_hash) VALUES ($1, $2, $3, $4)"
		);
	}
	catch (const pqxx::sql_error& e) {
		// error handling is neccessary because prepared statement might still exist within current session
		if (string(e.what()).find("Failure during \'[PREPARE addNewUser]\': ERROR:  prepared statement \"addNewUser\" already exists"))
			throw;
	}

	pqxx::work newUserData(*conn);
	try {
		newUserData.exec_prepared("addNewUser", email, firstName, lastName, passHash);
	}
	catch (const pqxx::sql_error& e) {
		if (string(e.what()).find("Failure during 'addNewUser': ERROR:  duplicate key value violates unique constraint 'users_email_key'")) {
			cout << "User with same email address already exists!\n";
			cout << "Redirecting to new registration...";
			Sleep(7000);
			system("cls");
			return false;
		}
	}
	newUserData.commit();
	return true;
}

void EntryManager::completeLibraryMemberRegistration() {
	cout << "You have been successfully registered!\n";
	cout << "Redirecting you back to the start...\n\n";
	Sleep(1000);
	system("cls");
}

void EntryManager::signInUser() {
	string email, password, firstName;

	cout << "--------------------- Sign In ---------------------\n\n";

	email = obtainCredentials("Email");
	password = obtainCredentials("Password");

	if(authenticateUser(email, password, firstName))
		authorizeUser(email, firstName);
}

string EntryManager::obtainCredentials(string credentialType) {
	string userInput;

	if (credentialType == "Email") {
		cout << credentialType << ": "; getline(cin, userInput);
		cout << endl;
	}
	else {
		cout << credentialType << ": ";
		userInput = hideCharacterInput();
		cout << endl;
	}

	return userInput;
}

bool EntryManager::authenticateUser(string email, string password, string& firstName) {
	string passHash = sha256(password);
	bool userExists = searchUserInDB(email, passHash, firstName);

	if (!userExists)
		handleInvalidCredentials();
	return userExists;
}

bool EntryManager::searchUserInDB(string email, string passHash, string& firstName) {
	setupSQLPrepStatementForFindingUser();
	
	pqxx::work findUserProcess(*conn);
	pqxx::result userResult = findUserProcess.exec_prepared("find_user", email, passHash);
	findUserProcess.commit();

	if (userResult.size() == 0) // no user matching with inputted credentials found
		return false;

	for (auto row : userResult)
		firstName = row["first_name"].c_str();
	return true;
}

void EntryManager::setupSQLPrepStatementForFindingUser() {
	try {
		conn->prepare(
			"find_user",
			"SELECT email, pass_hash, first_name FROM users WHERE email = $1 AND pass_hash = $2"
		);
	}
	catch (const pqxx::sql_error& e) {
		// error handling is neccessary because prepared statement might still exist within current session
		if (string(e.what()).find("Failure during \'[PREPARE find_user]\': ERROR:  prepared statement \"find_user\" already exists"))
			throw;
	}
}

void EntryManager::handleInvalidCredentials() {
	cout << "---------------------------------------------------\n\n";
	cout << "Invalid email and/or password!\n\n";
	cout << "Would you like to try again or return back to the starting menu?\n\n";
	cout << setw(5) << "" << "1 - Try Again\n";
	cout << setw(5) << "" << "2 - Return to Starting Menu\n\n";
	
	int userInput = menuManager1.getUserInput();
	system("cls");

	switch (userInput) {
		case 1:
			signInUser();
			break;
		case 2:
			break;
		default:
			cout << "Invalid option selected...\n\n";
			handleInvalidCredentials();
			break;
	}
}

void EntryManager::authorizeUser(string email, string firstName) {
	bool userIsLibraryAdmin = checkUserIsLibraryAdmin(email);

	if (userIsLibraryAdmin) {
		admin = new Staff(email, firstName);
		system("cls");
		menuManager1.showAdminMainMenu();
	}
	else {
		user = new User(email, firstName);
		system("cls");
		menuManager1.showMemberMainMenu();
	}
}

bool EntryManager::checkUserIsLibraryAdmin(string email) {
	try {
		conn->prepare(
			"check_user_is_admin",
			"SELECT email, is_admin FROM users WHERE email = $1 AND is_admin = TRUE"
		);
	}
	catch (const pqxx::sql_error& e) {
		// error handling is neccessary because prepared statement might still exist within current session
		if (string(e.what()).find("Failure during \'[PREPARE check_user_is_admin]\': ERROR:  prepared statement \"check_user_is_admin\" already exists"))
			throw;
	}

	pqxx::work checkUserIsAdminProcess(*conn);
	pqxx::result userTypeResult = checkUserIsAdminProcess.exec_prepared("check_user_is_admin", email);
	checkUserIsAdminProcess.commit();

	if (userTypeResult.size() == 0)
		return false;
	return true;
}

void EntryManager::adminEditUserProcess() {
	string userInput;
	user = new User();
	do {
		cout << "Enter a member email: ";
		getline(cin, userInput);
		system("cls");
	} while (!retrieveUserAccountInfo(userInput));
	user->setEmail(userInput);
	displayUserAccountEdit();

	char userCharInput = '0';
	while (true) {
		cout << "Edit another member? (Y/N): ";
		cin >> userCharInput;
		userCharInput = toupper(userCharInput);
		if (userCharInput != 'Y' && userCharInput != 'N') {
			cout << "Invalid option selected...\n";
		}
		else if (userCharInput == 'Y') {
			system("cls");
			bool singleRun = false;
			do {
				cout << "Enter a member email: ";
				if (!singleRun) {
					cin.ignore();
					singleRun = true;
				}
				getline(cin, userInput);
				system("cls");
			} while (!retrieveUserAccountInfo(userInput));
			user->setEmail(userInput);
			displayUserAccountEdit();
		}
		else {
			system("cls");
			break;
		}
	}
	delete user;
	user = nullptr;
}

void EntryManager::selfEditUserProcess(string email) {
	bool userNullAtStart = false;
	if (user == nullptr) {
		userNullAtStart = true;
		user = new User();
	}
	retrieveUserAccountInfo(email);
	user->setEmail(email);
	displayUserAccountEdit();
	if (userNullAtStart) {
		retrieveUserAccountInfo(email);
		admin->setFirstName(user->getFirstName());
		delete user;
		user = nullptr;
	}
	else {
		retrieveUserAccountInfo(email);
	}
}

void EntryManager::displayUserAccountInfo() {
	cout << "First Name: " << user->getFirstName() << endl;
	cout << "Last Name: " << user->getlastName() << endl;
	cout << "Email: " << user->getEmail() << endl;
}

bool EntryManager::retrieveUserAccountInfo(string email) {
	try {
		conn->prepare("retrieveUserInfo", "SELECT first_name, last_name, email FROM users WHERE email = $1");
	}
	catch (const pqxx::sql_error& e) {
		if (string(e.what()).find("Failure during \'[PREPARE retrieveUserInfo]\': ERROR:  prepared statement \"retrieveUserInfo\" already exists"))
			throw;
		}

	try {
		pqxx::work retrieveData(*conn);
		pqxx::result dataResult = retrieveData.exec_prepared("retrieveUserInfo", email);
		retrieveData.commit();

		if (dataResult.size() == 0) {
			system("cls");
			cout << "Invalid email entered...\n";
			return false;
		}
		else {
			for (auto row : dataResult) {
				user->setFirstName(row["first_name"].c_str());
				user->setLastName(row["last_name"].c_str());
			}
		}

	}
	catch (const pqxx::sql_error& e) {
		cerr << "SQL error: " << e.what() << '\n';
	}
	catch (const pqxx::usage_error& e) {
		cerr << "Usage error: " << e.what() << '\n';
		throw;
	}
	return true;
}

void EntryManager::displayUserAccountEdit() {
	cout << "Current member information:\n";
	displayUserAccountInfo();
	cout << "\n\nSelect info to change:\n";
	cout << "#1. First Name\n#2. Last Name\n#3. Email\n#4. Password\n#5. Cancel Operation\n\n";
	int selectedAction = menuManager1.getUserInput();
	processAccountChanges(selectedAction, user->getEmail());
}

void EntryManager::processAccountChanges(int userInput, string email) {
	allocatePreparedAccountEditStatement();
	system("cls");
	cout << "Current member information:\n";
	displayUserAccountInfo();
	cout << endl << endl;

	string userStringInput;
	string changeType;
	bool confirmChangePrompt = false;
	switch (userInput) {
	case 1:
		cout << "Enter a new first name: ";
		getline(cin, userStringInput);
		confirmChangePrompt = true;
		changeType = "first_name";
		break;
	case 2:
		cout << "Enter a new last name: ";
		getline(cin, userStringInput);
		confirmChangePrompt = true;
		changeType = "last_name";
		break;
	case 3:
		cout << "Enter a new email: ";
		getline(cin, userStringInput);
		confirmChangePrompt = true;
		changeType = "email";
		break;
	case 4:
		cout << "--------------------- Create a new password ---------------------\n\n";
		userStringInput = createPassword();
		confirmChangePrompt = true;
		changeType = "pass_hash";
		break;
	case 5:
		system("cls");
		break;
	default:
		cout << "Invalid option selected...\n\n";
		displayUserAccountEdit();
		break;
	}

	if (confirmChangePrompt) {
		char userCharInput = '0';
		while (true) {
			cout << "Confirm Change? (Y/N): ";
			cin >> userCharInput;
			userCharInput = toupper(userCharInput);
			if (userCharInput != 'Y' && userCharInput != 'N') {
				cout << "Invalid option selected...\n";
			}
			else if (userCharInput == 'Y') {
				applyAccountChanges(userStringInput, changeType);
				system("cls");
				cout << "Change applied successfully!\n";
				break;
			}
			else {
				system("cls");
				displayUserAccountEdit();
				break;
			}
		}
	}
}

void EntryManager::allocatePreparedAccountEditStatement() {
	const int totalOptions = 4;
	string editOptions[totalOptions] = {"first_name", "last_name", "email", "pass_hash"};

	for (int i = 0; i < totalOptions; i++) {
		try {
			conn->prepare("edit_user_" + editOptions[i] + "", "UPDATE users SET " + editOptions[i] + " = $1 WHERE email = $2");
		}
		catch (const pqxx::sql_error& e) {
			//error handling is neccessary because prepared statement might still exist within current session
			if (string(e.what()).find("Failure during \'[PREPARE edit_user_" + editOptions[i] + "]\': ERROR:  prepared statement \"edit_user_" + editOptions[i] + "\" already exists"))
				throw;
		}
	}
}

void EntryManager::applyAccountChanges(string userChange, string changeType) {
	try {
		pqxx::work applyChange(*conn);
		applyChange.exec_prepared("edit_user_" + changeType, userChange, user->getEmail());
		applyChange.commit();
	}
	catch (const pqxx::sql_error& e) {
		cerr << "SQL error: " << e.what() << '\n';
	}
	catch (const pqxx::usage_error& e) {
		cerr << "Usage error: " << e.what() << '\n';
		throw;
	}
}