#include "BookManager.h"
#include "extern.h"
#include <math.h>
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

void allocatePreparedInsertStatement() {
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
    allocatePreparedInsertStatement();
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
    displayEditBookUI();
    char userInput = '0';
    while (true) {
        ;       cout << "Edit another book? (Y/N): ";
        cin >> userInput;
        if (userInput != 'Y' && userInput != 'N') {
            cout << "Invalid option selected...\n";
        }
        else if (userInput == 'Y') {
            system("cls");
            displayEditBookUI();
        }
        else {
            break;
        }
    }
}

void allocatePreparedRetrieveStatement() {
    try {
        conn->prepare("find_book", "SELECT * FROM public.books WHERE book_id = $1");
    }
    catch (const pqxx::sql_error& e) {
        //error handling is neccessary because prepared statement might still exist within current session
        if (string(e.what()).find("Failure during \'[PREPARE find_book]\': ERROR:  prepared statement \"find_book\" already exists"))
            throw;
    }
}

void BookManager::displayEditBookUI() {
    int bookID;
    cout << "Enter a valid book ID#: ";
    cin >> bookID;
    allocatePreparedRetrieveStatement();
    string storedBookData[6];

    //placing the pqxx::work statement into a try-catch block ensures a new transaction is created each time
    try {
        pqxx::work bookData(*conn);
        pqxx::result bookResult = bookData.exec_prepared("find_book", bookID);
        bookData.commit();
        
        int i = 0;
        if (bookResult.size() == 0) {
            cout << "Invalid book ID#...\n";
        }
        else {
            for (auto row : bookResult) {
                for (auto field : row) {
                    storedBookData[i] = field.c_str();
                    cout << field.c_str() << '\t';
                    i++;
                }
                cout << endl;
            }
        }
        cout << endl;
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "SQL error: " << e.what() << '\n';
        std::cerr << "Rolling back transaction and aborting...\n";
    }
    //allocatePreparedEditStatement();

    cout << "What would you like to modify?\n";
    cout << "#1. Title\n#2. Author\n#3. Publisher\n#4. Publication Date\n#5 Available Copies\n\n";
    cout << "Please enter the numerical digit of the option you would like to select...\n";
    cout << "Enter here: ";
    int selectedOption;
    cin >> selectedOption;
    manageEditMenuSelection(selectedOption, storedBookData);
}

//void BookManager::allocatePreparedEditStatement() {
//    try {
//        conn->prepare("edit_book", "UPDATE public.books SET $1 = $2 WHERE book_id = $3");
//    }
//    catch (const pqxx::sql_error& e) {
//        //error handling is neccessary because prepared statement might still exist within current session
//        if (string(e.what()).find("Failure during \'[PREPARE edit_book]\': ERROR:  prepared statement \"edit_book\" already exists"))
//            throw;
//    }
//}

int BookManager::convertStringToInt(string stringInt) {
    int tempInt = 0;
    for (int i = stringInt.length(); i > 0; i--) {
        tempInt += ((int)stringInt[i-1] - 48) * pow(10, stringInt.length() - i);
    }

    return tempInt;
}

void BookManager::manageEditMenuSelection(int selectedOption, string* storedBookData) {
    pqxx::work editBook(*conn);
    string userStringInput;
    string selectedColumn;
    int userIntInput;
    int selectedBookID = convertStringToInt(storedBookData[0]);
    cout << "selected book id: " << selectedBookID << endl;
    switch (selectedOption)
    {
    case 1:
        //string newTitle;
        cout << "Enter a new title: "; 
        getline(cin, userStringInput);
        selectedColumn = "title";
        processBookChanges(selectedColumn, selectedBookID, userStringInput);
        break;
    case 2:
        cout << "Enter a new author: ";
        getline(cin, userStringInput);
        selectedColumn = "author";
        processBookChanges(selectedColumn, selectedBookID, userStringInput);
        break;
    case 3:
        cout << "Enter a new publisher: ";
        getline(cin, userStringInput);
        selectedColumn = "publisher";
        processBookChanges(selectedColumn, selectedBookID, userStringInput);
        break;
    case 4:
        cout << "Enter a new publication date: ";
        getline(cin, userStringInput);
        selectedColumn = "publication_date";
        processBookChanges(selectedColumn, selectedBookID, userStringInput);
        break;
    case 5:
        cout << "Enter updated available copy count: ";
        cin >> userIntInput;
        break;
    default:
        cout << "Invalid option selected...\n";
        break;
    }
}

void BookManager::processBookChanges(string selectedColumn,int bookID ,string userInput) {
    try {

    }
    catch(const pqxx::sql_error& e) {
        cerr << "SQL error: " << e.what() << '\n';
    }
}

void BookManager::processBookChanges(string selectedColumn,int bookID , int userInput) {

}