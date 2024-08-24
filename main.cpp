#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>
#include "MenuManager.h"
#include "AccountManager.h"
#include "User.h"
#include "Staff.h"
#include "BookSearch.h"
#include "extern.h"

using namespace std;

string connInfo;
MenuManager menuManager;
pqxx::connection* conn;
User* user = nullptr;
Staff* admin = nullptr;

void retrieveConnInfo(fstream& inputFile) {
	inputFile.open("../../../../connInfo.txt");
	if (inputFile.fail()) {
		cout << "Error has occurred in retrieving the file." << endl;
		exit(EXIT_FAILURE);
	}
	getline(inputFile, connInfo);
}

int setDatabaseConnection() {
	try {
		conn = new pqxx::connection(connInfo);
	}
	catch (exception const& e) {
		cout << "Could not successfully connect to the database...\n";
		cout << "Exception: " << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

int main() {
	fstream inputFile;

	retrieveConnInfo(inputFile);
	setDatabaseConnection();

	menuManager.beginMenuProcess();

	return 0;
}
