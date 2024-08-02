#include <iostream>
#include <iomanip>
#include "MenuManager.h"
#include "extern.h"

using namespace std;
BookSearch bookSearch;
EntryManager entryManager;

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
	cout << "--------------------------------------------------------------------------\n";
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
			showAdminMainMenu();
			//cout << "Feature unavailable. Please try again later.\n\n";
			break;
		case 3:
			entryManager.registerLibraryMember();
			break;
		case 4:
			cout << "Exiting..." << endl;
			quit = true;
			break;
		default:
			cout << "Invalid option selected...\n\n";
			break;
	}
}

void MenuManager::showMemberMainMenu() {
	cout << "--------------------- Main Menu ---------------------\n\n";
	cout << "Welcome \"Username\"\n\n";
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
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 4:
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 5:
		cout << "Exiting...";
		quit = true;
		break;
	default:
		cout << "Invalid option selected...\n\n";
		break;
	}
}

void MenuManager::showAdminMainMenu() {
	cout << "Welcome \"Username\"\n\n";
	cout << "Administrator Menu" << endl;
	cout << "--------------------------------------------------------------------------\n";
	cout << setw(5) << "" << "1 - Search Books\n";
	cout << setw(5) << "" << "2 - Add Books\n";
	cout << setw(5) << "" << "3 - Edit Books\n";
	cout << setw(5) << "" << "4 - Search and Manage Library Members\n";
	cout << setw(5) << "" << "5 - Edit My Account Info\n";
	cout << setw(5) << "" << "6 - Sign Out\n";
	cout << setw(5) << "" << "7 - Exit\n\n";
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
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 5:
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 6:
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 7:
		cout << "Exiting...";
		quit = true;
		break;
	default:
		cout << "Invalid option selected...\n\n";
		break;
	}
}