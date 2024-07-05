#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

int main() {
	fstream inputFile;
	string password;

	inputFile.open("../../../../passwordDB.txt");

	if (inputFile.fail())
		cout << "Error has occurred in retrieving the file." << endl;

	getline(inputFile, password);

	try {
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

	return 0;
}