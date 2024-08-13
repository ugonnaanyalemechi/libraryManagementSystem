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
	string userEmail;
	bool memberExists = false;
	
	while (!memberExists) {
		string userEmail = identifyMemberToPromote();

		if (userEmail == "c") // if the user wants to cancel the operation
			break;
		else
			//memberExists = checkMemberExists();
			;
	}

	if (memberExists)
		//promoteMemberToStaff(userEmail);
		;
}

string Staff::identifyMemberToPromote() {
	string userEmail;

	cout << "Enter the email address of the user to be promoted: "; getline(cin, userEmail);
	cout << endl;

	return userEmail;
}