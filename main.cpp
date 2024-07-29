#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>
#include "MenuManager.h"
#include "EntryManager.h"
#include "User.h"
#include "Staff.h"
#include "extern.h"

using namespace std;

string connInfo;
MenuManager menuManager;
BookManager bookManager;
EntryManager entryManager;
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
	conn = new pqxx::connection(connInfo);
	if (conn->is_open()) {
		cout << "Connected successfully to the database!\n" << endl;
		return 0;
	}
	else {
		cerr << "Cannot connect and access database...\n";
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
