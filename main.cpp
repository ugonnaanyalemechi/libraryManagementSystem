#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>
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

	return 0;
}