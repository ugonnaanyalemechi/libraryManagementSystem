#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>
#include "MenuManager.h"
#include "EntryManager.h"
#include "extern.h"

using namespace std;

string connInfo;
MenuManager menuManager;
EntryManager entryManager;
pqxx::connection* conn;

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
<<<<<<< Updated upstream
	if (conn->is_open()) {
		cout << "Connected successfully to the database!" << endl;
		return 0;
	}
	else {
=======

	if (conn->is_open()) {
		cout << "Successfully connected to: " << conn->dbname() << endl;

		pqxx::work w(*conn);

		/*pqxx::result row = w.exec(
			"SELECT title FROM books WHERE book_id=6"
		);

		cout << row[0][0] << endl;*/

		return 0;
	} else {
>>>>>>> Stashed changes
		cerr << "Cannot connect and access database...\n";
		exit(EXIT_FAILURE);
	}
}

int main() {
	fstream inputFile;

	retrieveConnInfo(inputFile);
	setDatabaseConnection();

<<<<<<< Updated upstream
	menuManager.showWelcomeMenu();
	menuManager.getUserInput();
	menuManager.processWelcomeMenuInput();
=======
	//menuManager.showWelcomeMenu();

	entryManager.registerLibraryMember();
>>>>>>> Stashed changes

	return 0;
}