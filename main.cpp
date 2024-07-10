#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>
<<<<<<< HEAD
#include "MenuManager.h"
#include "extern.h"

using namespace std;

string connInfo;
MenuManager menuManager;
pqxx::connection* conn;

void retrieveConnInfo(fstream& inputFile) {
	inputFile.open("../../../../connInfo.txt");
	if (inputFile.fail())
		cout << "Error has occurred in retrieving the file." << endl;
	getline(inputFile, connInfo);
}
int setDatabaseConnection() {
	conn = new pqxx::connection(connInfo);
	if (conn->is_open())
		return 0;
	else {
		cerr << "Cannot connect and access database...\n";
		return 1;
	}
}

int main() {
	fstream inputFile;

	retrieveConnInfo(inputFile);
	setDatabaseConnection();

	menuManager.showWelcomeMenu();
=======

using namespace std;

int main() {
	try {
		fstream inputFile;
		string password;

		inputFile.open("../../../../passwordDB.txt");

		if (inputFile.fail())
			cout << "Error has occurred in retrieving the file." << endl;

		getline(inputFile, password);

		// Connect to the database
		pqxx::connection c("host=aws-0-us-west-1.pooler.supabase.com port=6543 dbname=postgres user=postgres.pwdgipuzwbjtpswldglm password=" + password);
		if (c.is_open()) {
			cout << "Opened database successfully: " << c.dbname() << endl;
		}
		else {
			cout << "Can't open database" << endl;
			return 1;
		}

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
>>>>>>> 4b213f8a424dd0b436def0d7ed4b83f9f8282516

	return 0;
}