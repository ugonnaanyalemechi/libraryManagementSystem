#include <iostream>
#include <pqxx/pqxx>
#include <windows.h> // used for the Sleep() function
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
	string memberEmail, memberFirstName, memberLastName;
	bool memberExists = false;
	bool promotionConfirmed = false;
	
	while (!promotionConfirmed) {
		memberEmail = identifyMemberToPromote();

		if (memberEmail == "c") { // if the user wants to cancel the operation
			system("cls");
			break;
		}
		else {
			memberExists = checkMemberExists(memberEmail, memberFirstName, memberLastName);
			if (memberExists)
				promotionConfirmed = confirmPromotion(memberFirstName, memberLastName, memberExists);
		}
	}

	if (promotionConfirmed)
		promoteMemberToStaff(memberEmail);
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

bool Staff::confirmPromotion(string memberFirstName, string memberLastName, bool& memberExists) {
	bool inputIsInvalid = false;
	char decision;

	system("cls");
	while (!inputIsInvalid) {
		cout << "Are you sure you would like to promote " << memberFirstName << " " << memberLastName << " to a library staff member?\n";
		cout << "Enter 'y' or 'n': "; cin >> decision;
		cout << endl;
		cin.clear(); cin.ignore(1);

		if (decision == 'y')
			return true;
		else if (decision == 'n') {
			system("cls");
			memberExists = false;
			return false;
		}
		else {
			system("cls");
			cout << "Invalid input! Please try again!\n\n";
		}
	}
}

void Staff::promoteMemberToStaff(string memberEmail) {
	try {
		conn->prepare(
			"promote_member",
			"UPDATE users SET is_admin = TRUE WHERE email = $1"
		);
	}
	catch (const pqxx::sql_error& e) {
		// error handling is neccessary because prepared statement might still exist within current session
		if (string(e.what()).find("Failure during \'[PREPARE promote_member]\': ERROR:  prepared statement \"promote_member\" already exists"))
			throw;
	}

	pqxx::work promoteMemberProcess(*conn);
	promoteMemberProcess.exec_prepared("promote_member", memberEmail);
	promoteMemberProcess.commit();

	cout << "Promotion was successful!\n";
	cout << "Redirecting you back to the main menu...";
	Sleep(3000);
	system("cls");
}