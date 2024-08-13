#include <iostream>
#include <pqxx/pqxx>
#include "Staff.h"
#include "extern.h"

using namespace std;
MenuManager menuManager3;

Staff::Staff(string email, string firstName) {
	this->email = email;
	this->firstName = firstName;
}

void Staff::staffSignOut() {
	delete this;
	admin = nullptr;
	menuManager3.showWelcomeMenu();
}

void Staff::promoteMemberToStaffProcess() {
	string memberEmaill, memberFirstName, memberLastName;
	bool memberExists = false;
	
	while (!memberExists) {
		string memberEmail = identifyMemberToPromote();

		if (memberEmail == "c") { // if the user wants to cancel the operation
			system("cls");
			break;
		}
		else
			memberExists = checkMemberExists(memberEmail, memberFirstName, memberLastName);
			;
	}

	if (memberExists)
		//promoteMemberToStaff(userEmail);
		;
}

string Staff::identifyMemberToPromote() {
	string userEmail;

	cout << "Enter the email address of the user to be promoted (or enter 'c' to quit and return to the main menu)\n";
	cout << "Enter here: "; getline(cin, userEmail);
	cout << endl;

	return userEmail;
}

bool Staff::checkMemberExists(string memberEmail, string& memberFirstName, string& memberLastName) {
	try {
		conn->prepare(
			"check_member_exists",
			"SELECT email, first_name, last_name FROM users WHERE email = $1"
		);
	}
	catch (const pqxx::sql_error& e) {
		// error handling is neccessary because prepared statement might still exist within current session
		if (string(e.what()).find("Failure during \'[PREPARE check_member_exists]\': ERROR:  prepared statement \"check_member_exists\" already exists"))
			throw;
	}

	pqxx::work checkMemberProcess(*conn);
	pqxx::result userResult = checkMemberProcess.exec_prepared("check_member_exists", memberEmail);
	checkMemberProcess.commit();

	if (userResult.size() == 0) {// no user matching with inputted email was found
		system("cls");
		cout << "Invalid input/email address could not be found, please try again...\n\n";
		return false;
	}

	for (auto row : userResult) {
		memberFirstName = row["first_name"].c_str();
		memberLastName = row["last_name"].c_str();
	}

	return true;
}