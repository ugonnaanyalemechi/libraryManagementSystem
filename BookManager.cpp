#include "BookManager.h"
#include "extern.h"
//Remove false positive warning for invalid index
#pragma warning(disable:6385)
using namespace std;

bool checkDate(string dateInput) {
    if (dateInput.length() != 10) {
        return false;
    }
    else if ((dateInput[4] != '-') && (dateInput[7] != '-')) {
        return false;
    }

    int year = (dateInput[0] - 48) * 1000 + (dateInput[1] - 48) * 100 
             + (dateInput[2] - 48) * 10 + (dateInput[3] - 48);

    int month = (dateInput[5] - 48) * 10 + (dateInput[6] - 48);

    if (month > 12 || month < 1) {
        return false;
    }
    int day = (dateInput[8] - 48) * 10 + (dateInput[9] - 48);

    //handle leap year cases
    if (!((year % 100 == 0) && (year % 400 != 0))) {
        if (year % 4 == 0 && month == 2 && day <= 29) {
            return true;
        }
    }

    int daysPerMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (day = 0 || day > daysPerMonth[month - 1]) {
        return false;
    }

    return true;
}

void BookManager::appendBookToDatabase(string title, string author, string publisher, string publicationDate, int availableCopies) {
    pqxx::work bookData(*conn);
    bookData.exec_prepared("insertBookData", title, author, publisher, publicationDate, availableCopies);
    bookData.commit();
}

void BookManager::displayAddBookUI() {
    string title;
    string author;
    string publisher;
    string publicationDate;
    int availableCopies;

    cout << "--------------- Add a new book:  ---------------" << endl;
    cout << "Enter a Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter an Author: ";
    getline(cin, author);
    cout << "Enter a Publisher: ";
    getline(cin, publisher);
    cout << "Enter the Publication Date (YYYY-MM-DD): ";
    getline(cin, publicationDate);
    cout << "Enter available copies: ";
    cin >> availableCopies;

    while (availableCopies < 1) {
        cout << "Invalid copy amount entered!" << endl;
        cout << "Enter available copies: ";
        cin >> availableCopies;
    }

    while (!checkDate(publicationDate)) {
        cout << "Invalid date format entered!" << endl;
        cout << "Enter the Publication Date (YYYY-MM-DD): ";
        getline(cin, publicationDate);
    }

    bookManager.appendBookToDatabase(title, author, publisher, publicationDate, availableCopies);
}

void allocatePreparedStatement() {
    try {
        conn->prepare("insertBookData", "INSERT INTO books (title, author, publisher, publication_date, available_copies) VALUES ($1, $2, $3, $4, $5)");
    }
    catch (const pqxx::sql_error& e) {
        //error handling is neccessary because prepared statement might still exist within current session
        if (string(e.what()).find("Failure during \'[PREPARE insertBookData]\': ERROR:  prepared statement \"insertBookData\" already exists"))
            throw;
    }
}

void BookManager::addBookProcess() {
    allocatePreparedStatement();
    displayAddBookUI();
    char userInput = '0';
    while (true) {
;       cout << "Add another book? (Y/N): ";
        cin >> userInput;
        if (userInput != 'Y' && userInput != 'N') {
            cout << "Invalid option selected...\n";
        } else if (userInput == 'Y') {
            system("cls");
            displayAddBookUI();
        }
        else {
            break;
        }
    }
}

void BookManager::editBookProcess() {

}