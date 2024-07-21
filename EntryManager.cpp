#include <iostream>
#include <string>
#include <cctype> // used for the isalpha() & isspace() functions
#include <windows.h> // used for the Sleep() function
#include <pqxx/pqxx>
#include "EntryManager.h"
#include "sha256.h"
#include "extern.h"

using namespace std;

void EntryManager::registerLibraryMember() {
	string firstName, lastName, email, passHash;

	cout << "--------------------- Registration ---------------------\n";
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
	cout << "What is your " << infoType << "?\n";
	cout << "Enter your " << infoType << " here: "; getline(cin, userInput);
	cout << endl;
	checkPII(userInput, infoType);
	return userInput;
}

void EntryManager::checkPII(string &userInput, string infoType) {
	if (userInput == "") {
		cout << "Invald input! Please try again!\n\n";
		obtainPII(infoType);
	}
	
	if (infoType == "first name" || infoType == "last name") { // used to prevent special chars and nums from being entered in names
		for (char c : userInput) {
			if (isalpha(c) || isspace(c))
				continue;
			else {
				cout << "Invald input! Please try again!\n\n";
				obtainPII(infoType);
			}
		}
	}
}

string EntryManager::createPassword() {
	string inputtedPassword;
	cout << "Please provide a suitable password...\n";
	cout << "Enter your password here: "; getline(cin, inputtedPassword);
	cout << endl;
	return sha256(inputtedPassword);
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
	menuManager.showWelcomeMenu();
	menuManager.getUserInput();
	menuManager.processWelcomeMenuInput();
}