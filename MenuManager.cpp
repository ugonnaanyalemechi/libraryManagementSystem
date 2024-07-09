#include <iostream>
#include <iomanip>
#include "MenuManager.h"

using namespace std;

void MenuManager::getUserInput() {
	cout << "Enter file name here: "; cin >> userInput;
	cout << userInput << endl;
}

void MenuManager::showWelcomeMenu() {
	cout << "--------------------------------------------------------------------------\n";
	cout << "Welcome to the Library Management System!\n\n";
	cout << "Please enter the numerical digit of the option you would like to select...\n\n";
	cout << setw(5) << "" << "1 - Search Books\n";
	cout << setw(5) << "" << "2 - Sign In\n";
	cout << setw(5) << "" << "3 - Register\n";
	cout << setw(5) << "" << "4 - Staff Sign In\n";
	cout << setw(5) << "" << "5 - Exit\n\n";
}