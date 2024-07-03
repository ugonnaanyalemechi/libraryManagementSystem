#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

int main() {
	try {
		// Connect to the database
		pqxx::connection c("host=aws-0-us-west-1.pooler.supabase.com port=6543 dbname=postgres user=postgres.pwdgipuzwbjtpswldglm password=y6czEdx7lda6U6rU");
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