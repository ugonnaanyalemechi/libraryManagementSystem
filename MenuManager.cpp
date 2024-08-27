#include <iostream>
#include <iomanip>
#include "MenuManager.h"
#include "extern.h"

using namespace std;
BookSearch bookSearch;
AccountManager accountManager;

int MenuManager::getUserInput() {
	int input;
	cout << "Please enter the numerical digit of the option you would like to select...\n";
	cout << "Enter here: "; cin >> input;
	cout << endl;
	cin.clear(); cin.ignore(1);
	return input;
}

void MenuManager::beginMenuProcess() {
	while (!quit) {
		showWelcomeMenu();
	}
}

void MenuManager::showWelcomeMenu() {
	cout << "--------------------------------------------------------------------------\n\n";
	cout << "Welcome to the Library Management System!\n\n";
	cout << setw(5) << "" << "1 - Search Books\n";
	cout << setw(5) << "" << "2 - Sign In\n";
	cout << setw(5) << "" << "3 - Register\n";
	cout << setw(5) << "" << "4 - Exit\n\n";
	processWelcomeMenuInput(getUserInput());
}

void MenuManager::processWelcomeMenuInput(int userInput) {
	system("cls");
	switch (userInput) {
		case 1:
			bookSearch.searchBookProcess();
			break;
		case 2:
			accountManager.signInUser();
			break;
		case 3:
			accountManager.registerLibraryMember();
			break;
		case 4:
			cout << "Exiting..." << endl;
			quit = true;
			exit(EXIT_SUCCESS);
			break;
		default:
			cout << "Invalid option selected...\n\n";
			break;
	}
}

void MenuManager::showMemberMainMenu() {
	cout << "--------------------- Main Menu ---------------------\n\n";
	cout << "Hello, " << user->getFirstName() << "\n\n";
	cout << setw(5) << "" << "1 - Search Books\n";
	cout << setw(5) << "" << "2 - View My Loans\n";
	cout << setw(5) << "" << "3 - Edit My Account Info\n";
	cout << setw(5) << "" << "4 - Sign Out\n";
	cout << setw(5) << "" << "5 - Exit\n\n";
	processMemberMainMenu(getUserInput());
}

void MenuManager::processMemberMainMenu(int userInput) {
	system("cls");
	switch (userInput)
	{
	case 1:
		bookSearch.searchBookProcess();
		break;
	case 2:
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 3:
		accountManager.selfEditUserProcess(user->getEmail());
		break;
	case 4:
		user->signOut();
		break;
	case 5:
		cout << "Exiting...";
		exit(EXIT_SUCCESS);
		break;
	default:
		cout << "Invalid option selected...\n\n";
		break;
	}
	while (user != nullptr) {
		showMemberMainMenu();
	}
}

void MenuManager::showAdminMainMenu() {
	cout << "--------------------- Main Menu - Library Staff ---------------------\n\n";
	cout << "Hello, " << admin->getFirstName() << "\n\n";
	cout << setw(5) << "" << "1 - Search Books\n";
	cout << setw(5) << "" << "2 - Add Books\n";
	cout << setw(5) << "" << "3 - Edit Books\n";
	cout << setw(5) << "" << "4 - Search and Manage Library Members\n";
	cout << setw(5) << "" << "5 - Edit My Account Info\n";
	cout << setw(5) << "" << "6 - Promote Library Member to Library Staff\n";
	cout << setw(5) << "" << "7 - Sign Out\n";
	cout << setw(5) << "" << "8 - Exit\n\n";
	processAdminMainMenu(getUserInput());
}

void MenuManager::processAdminMainMenu(int userInput) {
	BookManager* bookManager = new BookManager();
	system("cls");
	switch (userInput)
	{
	case 1:
		bookSearch.searchBookProcess();
		break;
	case 2:
		bookManager->addBookProcess();
		break;
	case 3:
		bookManager->editBookProcess();
		break;
	case 4:
		accountManager.adminEditUserProcess();
		break;
	case 5:
		accountManager.selfEditUserProcess(admin->getEmail());
		break;
	case 6:
		admin->promoteMemberToStaffProcess();
		break;
	case 7:
		admin->staffSignOut();
		break;
	case 8:
		cout << "Exiting...";
		exit(EXIT_SUCCESS);
		break;
	default:
		cout << "Invalid option selected...\n\n";
		break;
	}

	while (admin != nullptr) {
		showAdminMainMenu();
	}
}