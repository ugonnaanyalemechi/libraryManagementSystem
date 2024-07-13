#include <iostream>
#include <iomanip>
#include "MenuManager.h"

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
}

void MenuManager::processWelcomeMenuInput() {
	switch (userInput) {
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
			cout << "Feature unavailable. Please try again later." << endl;
			break;
		case 5:
			cout << "Feature unavailable. Please try again later." << endl;
			break;
	}
}