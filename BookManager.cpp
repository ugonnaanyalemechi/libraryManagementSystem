#include "BookManager.h"
#include "extern.h"
//Remove false positive warning for invalid index
#pragma warning(disable:6385)


void BookManager::printDatabaseName() {
    string dbname = conn->dbname();
    cout << "Connected to database: " << dbname << endl;
}

//Checks date format before sending to database
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

    if (1 > month > 12) {
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

void BookManager::displayAddBookMenu() {
    string title;
    string author;
    string publisher;
    string publicationDate;

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

    while (!checkDate(publicationDate)) {
        cout << "Invalid date format entered!" << endl;
        cout << "Enter the Publication Date (YYYY-MM-DD): ";
        getline(cin, publicationDate);
    }
}