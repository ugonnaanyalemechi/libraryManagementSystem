#include "BookManager.h"
#include "extern.h"



void BookManager::printDatabaseName() {
    string dbname = conn->dbname();
    cout << "Connected to database: " << dbname << endl;
}

bool checkDate(string dateInput) {
    while ((dateInput.length() != 10) && (dateInput[4] != '-') && (dateInput[7] != '-')) {
        cout << "Invalid date format entered!" << endl;
        cout << "Enter the Publication Date (YYYY-MM-DD): ";
        return false;
    }
    return true;
}

void BookManager::displayAddBookMenu() {
    string title;
    string author;
    string publisher;
    string publicationDate;

    cout << "--------------- Add new book:  ---------------" << endl;
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
        getline(cin, publicationDate);
    }
}