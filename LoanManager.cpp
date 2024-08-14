#include "LoanManager.h"
#include "extern.h"
#include "BookInfo.h"
#include "User.h"
#include <stdio.h>
#include "EntryManager.h"

using namespace std;

void LoanManaager::checkoutProcess(BookInfo* book) {
	
	if (EntryManager::checkUserIsLibraryAdmin(user->getEmail)) {
		cout << "User must be an administrator" << endl;
		return;
	}

	if (book->retrieveAvailableCopies <= 0) {
		cout << book->retrieveBookTitle << " is not currently available." << endl;
		//redirect back to book info page
	}
	//else if(book has already been checked out by user)
	else {
		cout << "There are " << book->retrieveAvailableCopies << " available." << endl;
		cout << "Woould you like to check out \"" << book->retrieveBookTitle << "\"? (Y/N)" << endl;
		
		if (processYesNo) {
			checkoutBook(book);
		}
		else {
			//redirect back to book info
		}

	}

}

bool LoanManager::processYesNo() {
	string userInput;
	cin >> userInput;
	if (tolower(userInput) == 'y') {
		return true;
	}
	else if (tolower(userInput) == 'n') {
		return false;
	}
	else {
		cout << "Invalid input, answer 'y' or'n'" << endl;
		processYesNo();
	}
}

void LoanManager::checkoutBook(BookInfo* book) {
	try {
		conn->prepare("addLoanToUser", "INSERT into loaned_books $1 from Users where email = $2");
	}
	catch (const pqxx::sql_error& e) {
		if (string(e.what()).find("Failure during \'[PREPARE addLoanToUser]\': ERROR:  prepared statement \"addLoanToUser\" already exists"))
			throw;
	}

	pqxx::work addLoan(conn*);
	addLoan.exec_prepared("addLoanToUser", book->retrieveBookID, user->getEmail);
	addLoan.commit();

	try {
		conn->prepare("decrementAvailiableCopies", "INSERT into loaned_books $1 from books where book_ID = $2");
	}
	catch (const pqxx::sql_error& e) {
		if (string(e.what()).find("Failure during \'[PREPARE decrementAvailableCopies]\': ERROR:  prepared statement \"decrementAvailableCopies\" already exists"))
			throw;
	}

	pqxx::work updateCopies(conn*);
	updateCopies.exec_prepared("decrementAvailableCopies", (book->retrieveAvailableCopies - 1), book->retrieveBookID);
	updateCopies.commit();


}