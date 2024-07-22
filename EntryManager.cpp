#include <iostream>
#include <string>
#include <cctype> // used for the isalpha() & isspace() functions
#include <windows.h> // used for the Sleep() function
#include <conio.h>
#include <pqxx/pqxx>
#include "EntryManager.h"
#include "sha256.h"
#include "extern.h"

using namespace std;

void EntryManager::registerLibraryMember() {
	string firstName, lastName, email, passHash;

	cout << "--------------------- Registration ---------------------\n\n";
	cout << "We're so glad you want to join us! We just need a few details from you to create an account!\n\n";
	
	firstName = obtainPII("first name");
	lastName = obtainPII("last name");
	email = obtainPII("email address");
	passHash = createPassword();
	
	addNewLibraryMemberToDB(firstName, lastName, email, passHash);
	completeLibraryMemberRegistration();
}

string EntryManager::obtainPII(string infoType) { // PII = personally identifiable information
	string userInput;
	cout << "Enter your " << infoType << ": "; getline(cin, userInput);
	cout << endl;
	checkPII(userInput, infoType);
	return userInput;
}

void EntryManager::checkPII(string &userInput, string infoType) {
	if (userInput == "") {
		cout << "Invald input! Please try again!\n\n";
		obtainPII(infoType);
	}
	
	if (infoType == "first name" || infoType == "last name") {
		for (int i = 0; i < userInput.length(); i++) {
			if (userInput[0]) // ensures first and last names are capitalized
				userInput[0] = toupper(userInput[0]);
			
			if (isalpha(userInput[i]) || userInput[i]) // used to prevent special chars and nums from being entered in names
				continue;
			else {
				cout << "Invald input! Please try again!\n\n";
				obtainPII(infoType);
			}
		}
	}
}

string EntryManager::hideCharacterInput() {
	char cString[1000];
	int i = 0;
	char ch;
	while ((ch = _getch()) != '\r') { // Read characters until Enter (Enter key has ASCII value '\r')
		if (ch == '\b') { // Handle backspace
			if (i > 0) {
				std::cout << "\b \b"; // Move cursor back, overwrite character, move cursor back again
				i--;
			}
		}
		else {
			cString[i++] = ch;
			std::cout << '*'; // Print asterisk for each character
		}
	}
	cString[i] = '\0';
	cout << endl;
	string enteredString = cString;
	return enteredString;
}

string EntryManager::createPassword() {
	string inputtedPassword;

	std::cout << "Enter password: ";
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

void EntryManager::addNewLibraryMemberToDB(string firstName, string lastName, string email, string passHash) {
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
	newUserData.exec_prepared("addNewUser", email, firstName, lastName, passHash);
	newUserData.commit();
}

void EntryManager::completeLibraryMemberRegistration() {
	cout << "You have been successfully registered!\n";
	cout << "Redirecting you back to the start...\n\n";
	Sleep(1000);
	system("cls");
}