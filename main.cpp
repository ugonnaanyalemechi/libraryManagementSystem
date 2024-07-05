#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>

#include "extern.h"

using namespace std;
using namespace pqxx;

void printNum();

int main() {

	num = 5;

	fstream inputFile;
	string password;

	inputFile.open("../../../../passwordDB.txt");

	if (inputFile.fail())
		cout << "Error has occurred in retrieving the file." << endl;

	getline(inputFile, password);

	try {
		// Connect to the database
		connection c("host=aws-0-us-west-1.pooler.supabase.com port=6543 dbname=postgres user=postgres.pwdgipuzwbjtpswldglm password=" + password);
		if (c.is_open()) {
			cout << "Opened database successfully: " << c.dbname() << endl;
		}
		else {
			cout << "Can't open database" << endl;
			return 1;
		}

		work w(c);

		result row = w.exec(
			"SELECT title FROM books WHERE book_id=3"
		);

		w.commit();

		cout << row[0][0] << endl;

	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return 1;
	}

	cout << "This was printed in main.cpp: " + to_string(num) << endl;
	printNum();


	return 0;
}