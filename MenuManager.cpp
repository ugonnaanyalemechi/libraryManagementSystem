#include <iostream>
#include <iomanip>
#include "MenuManager.h"
#include "extern.h"

using namespace std;

void MenuManager::getUserInput() {
	cout << "Please enter the numerical digit of the option you would like to select...\n";
	cout << "Enter here: "; cin >> userInput;
	cout << endl;
}

void MenuManager::showWelcomeMenu() {
	cout << "--------------------------------------------------------------------------\n";
	cout << "Welcome to the Library Management System!\n\n";
	cout << setw(5) << "" << "1 - Search Books\n";
	cout << setw(5) << "" << "2 - Sign In\n";
	cout << setw(5) << "" << "3 - Register\n";
	cout << setw(5) << "" << "4 - Staff Sign In\n";
	cout << setw(5) << "" << "5 - Exit\n\n";
	getUserInput();
	processWelcomeMenuInput();
}

void MenuManager::processWelcomeMenuInput() {
	system("cls");
	switch (userInput) {
		case 1:
			cout << "Feature unavailable. Please try again later." << endl;
			break;
		case 2:
			showMemberMainMenu();
			break;
		case 3:
			cout << "Feature unavailable. Please try again later." << endl;
			break;
		case 4:
			cout << "Feature unavailable. Please try again later." << endl;
			break;
		case 5:
			cout << "Exiting..." << endl;
			exit(EXIT_SUCCESS);
			break;
		default:
			cout << "Invalid option selected...\n";
			break;

	}
}

void MenuManager::showMemberMainMenu() {
	cout << "--------------------------------------------------------------------------\n";
	cout << "Welcome \"Username\"\n\n";
	cout << setw(5) << "" << "1 - Search Books\n";
	cout << setw(5) << "" << "2 - View My Loans\n";
	cout << setw(5) << "" << "3 - Edit My Account Info\n";
	cout << setw(5) << "" << "4 - Sign Out\n";
	cout << setw(5) << "" << "5 - Exit\n\n";
	getUserInput();
	processMemberMainMenu();
}

void MenuManager::processMemberMainMenu() {
	system("cls");
	switch (userInput)
	{
	case 1:
		cout << "Feature unavailable. Please try again later." << endl;
		break;
	case 2:
		cout << "Feature unavailable. Please try again later." << endl;
		break;
	case 3:
		cout << "Feature unavailable. Please try again later." << endl;
		break;
	case 4:
		showWelcomeMenu();
		break;
	case 5:
		cout << "Exiting...";
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}