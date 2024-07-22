#include <iostream>
#include <iomanip>
#include "MenuManager.h"
#include "extern.h"

using namespace std;

int MenuManager::getUserInput() {
	cin.clear();
	int input;
	cout << "Please enter the numerical digit of the option you would like to select...\n";
	cout << "Enter here: "; cin >> input;
	cout << endl;
	return input;
}

void MenuManager::startMenu() {
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
			cout << "Feature unavailable. Please try again later.\n\n";
			break;
		case 2:
			showMemberMainMenu();
			break;
		case 3:
			cout << "Feature unavailable. Please try again later.\n\n";
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
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 2:
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 3:
		cout << "Feature unavailable. Please try again later.\n\n";
		break;
	case 4:
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
	cout << setw(5) << "" << "2 - Add/Edit Books\n";
	cout << setw(5) << "" << "3 - Search and Manage Library Members\n";
	cout << setw(5) << "" << "4 - Edit My Account Info\n";
	cout << setw(5) << "" << "5 - Sign Out\n";
	cout << setw(5) << "" << "6 - Exit\n\n";
	processAdminMainMenu(getUserInput());
}

void MenuManager::processAdminMainMenu(int userInput) {
	system("cls");
	switch (userInput)
	{
	case 1:
		cout << "Feature unavailable. Please try again later.\n\n";
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
		break;
	case 6:
		cout << "Exiting...";
		quit = true;
		break;
	default:
		cout << "Invalid option selected...\n\n";
		break;
	}
}