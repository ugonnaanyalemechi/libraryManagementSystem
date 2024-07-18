#include <iostream>
#include <string>
#include <cctype>
#include <pqxx/pqxx>
#include "EntryManager.h"
#include "sha256.h"
#include "extern.h"

using namespace std;

void EntryManager::registerLibraryMember() {
	string firstName, lastName, email, hashedPassword;

	cout << "--------------------- Registration ---------------------\n";
	cout << "We're so glad you want to join us! We just need a few details from you to create an account!\n\n";
	
	firstName = obtainPII("first name");
	lastName = obtainPII("last name");
	email = obtainPII("email address");
	hashedPassword = createPassword();


	addNewUserToDatabase("test", "test", "test", "test");
}

string EntryManager::obtainPII(string infoType) {
	string userInput;
	if (infoType == "first name" || infoType == "last name") {
		cout << "What is your " << infoType << "?\n";
		cout << "Enter your " << infoType << " here: "; getline(cin, userInput);
		cout << endl;
		checkPII(userInput, infoType);
	}
	else {
		cout << "What is your " << infoType << "?\n";
		cout << "(If you do not have an email, enter the word 'none' below)\n";
		cout << "Enter here: "; getline(cin, userInput);
		cout << endl;
		checkPII(userInput, infoType);
		cout << "email address: " << userInput << endl;

	}
	return userInput;
}

void EntryManager::checkPII(string &userInput, string infoType) {
	if (userInput == "") {
		cout << "Invald input!\n\n";
		obtainPII(infoType);
	}
	
	for (char c : userInput) {
		if (isalpha(c) || isspace(c))
			continue;
		else {
			cout << "Invald input!\n\n";
			obtainPII(infoType);
		}
	}

	if (userInput == "none" && infoType == "email address")
		userInput = "NULL";
}

string EntryManager::createPassword() {
	string inputtedPassword;
	cout << "Please provide a suitable password...\n";
	cout << "Enter your password here: "; getline(cin, inputtedPassword);
	cout << endl;
	return sha256(inputtedPassword);
}

void EntryManager::addNewUserToDatabase(string firstName, string lastName, string email, string hashPassword) {
	pqxx::work w(*conn);

	pqxx::result row = w.exec(
		"SELECT MAX(user_count) FROM users"
	);

	string thing = row[0][0].c_str();

	cout << thing << endl;

	/*
	in order to make a uesr_id generator, 
	*/


	/*conn->prepare(
		"add_new_user",
		"INSER"
		);*/
}