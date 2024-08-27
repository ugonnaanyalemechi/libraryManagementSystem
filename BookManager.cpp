#include "BookManager.h"
#include "extern.h"
#include <math.h>
//Remove false positive warning for invalid index
#pragma warning(disable:6385)
using namespace std;

bool BookManager::checkDate(string dateInput) {
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

void BookManager::appendBookToDatabase(string title, string author, string genre, string publisher, string publicationDate, int availableCopies) {
    pqxx::work bookData(*conn);
    bookData.exec_prepared("insertBookData", title, author, genre, publisher, publicationDate, availableCopies);
    bookData.commit();
}

void BookManager::displayAddBookUI() {
    string title;
    string author;
    string genre;
    string publisher;
    string publicationDate;
    int availableCopies;

    cout << "--------------------- Add New Book ---------------------\n\n";
    cout << "NOTE: Seperate multiple entries with a comma (,)\n\n";
    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Book Author(s): ";
    getline(cin, author);
    cout << "Enter Book Genre(s): ";
    getline(cin, genre);
    cout << "Enter Book Publisher(s): ";
    getline(cin, publisher);
    cout << "Enter the Publication Date (YYYY-MM-DD): ";
    getline(cin, publicationDate);
    cout << "Enter Available Copies: ";
    cin >> availableCopies;

    while (availableCopies < 1) {
        while (!std::cin.good())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        cout << "Invalid copy amount entered!" << endl;
        cout << "Enter available copies: ";
        cin >> availableCopies;
    }

    while (!checkDate(publicationDate)) {
        cout << "Invalid date format entered!" << endl;
        cout << "Enter the Publication Date (YYYY-MM-DD): ";
        getline(cin, publicationDate);
    }

    appendBookToDatabase(title, author, genre, publisher, publicationDate, availableCopies);
}

void allocatePreparedInsertStatement() {
    try {
        conn->prepare("insertBookData", "INSERT INTO books (title, author, genre, publisher, publication_date, available_copies) VALUES ($1, $2, $3, $4, $5, $6)");
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
        userInput = toupper(userInput);
        if (userInput != 'Y' && userInput != 'N') {
            cout << "Invalid option selected...\n";
        } else if (userInput == 'Y') {
            system("cls");
            displayAddBookUI();
        }
        else {
            system("cls");
            break;
        }
    }
}

void BookManager::editBookProcess() {
    displayEditBookUI();
    char userInput = '0';
    while (true) {
        cout << "Edit another book? (Y/N): ";
        cin >> userInput;
        userInput = toupper(userInput);
        if (userInput != 'Y' && userInput != 'N') {
            cout << "Invalid option selected...\n";
        }
        else if (userInput == 'Y') {
            system("cls");
            displayEditBookUI();
        }
        else {
            system("cls");
            break;
        }
    }
}

void BookManager::allocatePreparedRetrieveStatement() {
    try {
        conn->prepare("find_book", "SELECT * FROM public.books WHERE book_id = $1");
    }
    catch (const pqxx::sql_error& e) {
        //error handling is neccessary because prepared statement might still exist within current session
        if (string(e.what()).find("Failure during \'[PREPARE find_book]\': ERROR:  prepared statement \"find_book\" already exists"))
            throw;
    }
}

void BookManager::allocatePreparedEditStatement() {
    const int totalOptions = 6;
    string editOptions[totalOptions] = { "title", "author", "genre", "publisher", "publication_date", "available_copies" };

    for (int i = 0; i < totalOptions; i++) {
        try {
            conn->prepare("edit_book_" + editOptions[i] + "", "UPDATE public.books SET " + editOptions[i] + " = $1 WHERE book_id = $2");
        }
        catch (const pqxx::sql_error& e) {
            //error handling is neccessary because prepared statement might still exist within current session
            if (string(e.what()).find("Failure during \'[PREPARE edit_book_" + editOptions[i] + "]\': ERROR:  prepared statement \"edit_book_" + editOptions[i] + "\" already exists"))
                throw;
        }
    }
}

void BookManager::displayEditBookUI() {
    BookInfo* bookDisplayData = new BookInfo();
    int bookID;
    isBookIDValid = false;
    cout << "Enter a valid book ID#: ";
    cin >> bookID;
    while (!std::cin.good())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "\nFinding book";
    allocatePreparedEditStatement();
    retrieveBookByID(bookID, bookDisplayData);

    if(isBookIDValid)
    editBookMenuUI(bookDisplayData);

}

bool BookManager::retrieveBookByID(BookInfo*& bookData) {
    allocatePreparedRetrieveStatement();
    //placing the pqxx::work statement into a try-catch block ensures a new transaction is created each time
    try {
        pqxx::work retrieveBookData(*conn);
        pqxx::result bookResult = retrieveBookData.exec_prepared("find_book", bookData->retrieveBookID());
        retrieveBookData.commit();

        int i = 0;
        if (bookResult.size() == 0) {
            cout << "Invalid book ID#...\n";
            return false;
        }
        else {
            isBookIDValid = true;
            for (auto row : bookResult) {
                bookData->setBookID(row["book_id"].as<int>());
                bookData->setBookTitle(row["title"].c_str());
                bookData->setBookAuthor(row["author"].c_str());
                bookData->setBookGenre(row["genre"].c_str());
                bookData->setBookPublisher(row["publisher"].c_str());
                bookData->setBookPublicationDate(row["publication_date"].c_str());
                bookData->setAvailableCopies(row["available_copies"].as<int>());
            }
        }
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "SQL error: " << e.what() << '\n';
        std::cerr << "Rolling back transaction and aborting...\n";
    }
    return true;

}

void BookManager::retrieveBookByID(int bookID, BookInfo*& bookData) {
    allocatePreparedRetrieveStatement();

    //placing the pqxx::work statement into a try-catch block ensures a new transaction is created each time
    try {
        pqxx::work retrieveBookData(*conn);
        pqxx::result bookResult = retrieveBookData.exec_prepared("find_book", bookID);
        retrieveBookData.commit();

        int i = 0;
        if (bookResult.size() == 0) {
            system("cls");
            cout << "Invalid book ID#...\n";
            isBookIDValid = false;
            delete bookData;
            displayEditBookUI();
        }
        else {
            isBookIDValid = true;
            for (auto row : bookResult) {
                bookData->setBookID(row["book_id"].as<int>());
                bookData->setBookTitle(row["title"].c_str());
                bookData->setBookAuthor(row["author"].c_str());
                bookData->setBookGenre(row["genre"].c_str());
                bookData->setBookPublisher(row["publisher"].c_str());
                bookData->setBookPublicationDate(row["publication_date"].c_str());
                bookData->setAvailableCopies(row["available_copies"].as<int>());
            }
        }
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "SQL error: " << e.what() << '\n';
        std::cerr << "Rolling back transaction and aborting...\n";
    }
}
void BookManager::displayBookListHeader() {
    cout << left <<setw(maxIdDisplayLength) <<"ID#:";
    cout << setw(maxTitleDisplayLength+6) << "Title:";
    cout << setw(maxAuthorDisplayLength+6) << "Author(s):";
    cout << "Available copies:";
    cout << endl;
}

void BookManager::displayBookListFullInfo(BookInfo* bookData) {
    cout << "Book ID#:         " << bookData->retrieveBookID() << endl;
    cout << "Title:            " << bookData->retrieveBookTitle() << endl;
    cout << "Author(s):        " << bookData->retrieveBookAuthor() << endl;
    cout << "Genre(s):         " << bookData->retrieveBookGenre() << endl;
    cout << "Publisher(s):     " << bookData->retrieveBookPublisher() << endl;
    cout << "Publication Date: " << bookData->retrieveBookPublicationDate() << endl;
    cout << "Available Copies: " << bookData->retrieveAvailableCopies() << endl;
}

void BookManager::displayBookDataListFormat(BookInfo* bookData) {
    cout << left << setw(6) << bookData->retrieveBookID();

    if (bookData->retrieveBookTitle().length() > maxTitleDisplayLength) {
        cout << setw(maxTitleDisplayLength) << bookData->retrieveBookTitle().substr(0,maxTitleDisplayLength);
        cout  << setw(6) << "...";
    }
    else {
        cout << setw(maxTitleDisplayLength+6) << bookData->retrieveBookTitle();
    }


    if (bookData->retrieveBookAuthor().length() > maxAuthorDisplayLength) {
        cout << setw(maxAuthorDisplayLength) << bookData->retrieveBookAuthor().substr(0, maxAuthorDisplayLength);
        cout << setw(6) << "...";
    }
    else {
        cout << setw(maxAuthorDisplayLength + 6) << bookData->retrieveBookAuthor();
    }
    cout << bookData->retrieveAvailableCopies();
}

void BookManager::editBookMenuUI(BookInfo*& storedBookData) {
    isBookIDValid = false;
    cout << "...book was found!\n\n";
    displayBookListFullInfo(storedBookData);

    cout << endl << endl;
    cout << "What would you like to modify?\n";
    cout << "\n\nSelect info to change:\n";
    cout << setw(5) << "" << "1 - Title\n";
    cout << setw(5) << "" << "2 - Author\n";
    cout << setw(5) << "" << "3 - Genre\n";
    cout << setw(5) << "" << "4 - Publisher\n";
    cout << setw(5) << "" << "5 - Publication Date\n";
    cout << setw(5) << "" << "6 - Available Copies\n";
    cout << setw(5) << "" << "7 - Delete Book\n";
    cout << setw(5) << "" << "8 - Cancel Operation\n\n";
    cout << "Please enter the numerical digit of the option you would like to select...\n";
    cout << "Enter here: ";
    int selectedOption;
    cin >> selectedOption;
    system("cls");
    manageEditMenuSelection(selectedOption, storedBookData);
}

int BookManager::convertStringToInt(string stringInt) {
    int tempInt = 0;
    for (int i = stringInt.length(); i > 0; i--) {
        tempInt += ((int)stringInt[i-1] - 48) * pow(10, stringInt.length() - i);
    }

    return tempInt;
}

bool BookManager::displayChanges(BookInfo*& storedBookData, BookInfo*& newBookData) {
    cout << "\nBefore change:\n";
    displayBookListFullInfo(storedBookData);
    cout << endl;
    
    cout << "\nAfter change:\n";
    displayBookListFullInfo(newBookData);
    cout << endl;

    while (true) {
        char userInput;
        cout << "\nConfirm change? (Y/N): ";
        cin >> userInput;
        userInput = toupper(userInput);
        if (userInput != 'Y' && userInput != 'N') {
            cout << "Invalid option selected...\n";
        }
        else if (userInput == 'Y') {
            delete storedBookData;
            delete newBookData;
            return true;
            break;
        }
        else {
            system("cls");
            delete newBookData;
            return false;
            break;
        }
    }
}

void BookManager::manageEditMenuSelection(int selectedOption, BookInfo*& storedBookData) {
    string userStringInput;
    string selectedColumn;
    int userIntInput;
    int selectedBookID = storedBookData->retrieveBookID();
    BookInfo* newBookData = new BookInfo(storedBookData->retrieveBookID(), storedBookData->retrieveBookTitle(), storedBookData->retrieveBookAuthor(),
        storedBookData->retrieveBookGenre(), storedBookData->retrieveBookPublisher(), storedBookData->retrieveBookPublicationDate(), storedBookData->retrieveAvailableCopies());
    switch (selectedOption)
    {
    case 1:
        cout << "Previous title: " << storedBookData->retrieveBookTitle() << endl;
        cout << "Enter a new title: ";
        cin.ignore();
        getline(cin, userStringInput);
        newBookData->setBookTitle(userStringInput);
        selectedColumn = "title";
        if (displayChanges(storedBookData, newBookData)) {
            processBookChanges(selectedColumn, selectedBookID, userStringInput);
        }
        else {
            editBookMenuUI(storedBookData);
        }
        
        break;
    case 2:
        cout << "Previous author(s): " << storedBookData->retrieveBookAuthor() << endl;
        cout << "Enter the new author(s): ";
        cin.ignore();
        getline(cin, userStringInput);
        newBookData->setBookAuthor(userStringInput);
        selectedColumn = "author";
        if (displayChanges(storedBookData, newBookData)) {
            processBookChanges(selectedColumn, selectedBookID, userStringInput);
        }
        else {
            editBookMenuUI(storedBookData);
        }
        break;
    case 3:
        cout << "Previous genre(s): " << storedBookData->retrieveBookGenre() << endl;
        cout << "Enter the new genre(s): ";
        cin.ignore();
        getline(cin, userStringInput);
        newBookData->setBookGenre(userStringInput);
        selectedColumn = "genre";
        if (displayChanges(storedBookData, newBookData)) {
            processBookChanges(selectedColumn, selectedBookID, userStringInput);
        }
        else {
            editBookMenuUI(storedBookData);
        }
        break;
    case 4:
        cout << "Previous publisher(s): " << storedBookData->retrieveBookPublisher() << endl;
        cout << "Enter the new publisher(s): ";
        cin.ignore();
        getline(cin, userStringInput);
        newBookData->setBookPublisher(userStringInput);
        selectedColumn = "publisher";
        if (displayChanges(storedBookData, newBookData)) {
            processBookChanges(selectedColumn, selectedBookID, userStringInput);
        }
        else {
            editBookMenuUI(storedBookData);
        }
        
        break;
    case 5:
        cout << "Previous publication date: " << storedBookData->retrieveBookPublicationDate() << endl;
        cout << "Enter a new publication date (YYYY-MM-DD): ";
        cin.ignore();
        getline(cin, userStringInput);

        while (!checkDate(userStringInput)) {
            cout << "Invalid date format entered!" << endl;
            cout << "Enter the Publication Date (YYYY-MM-DD): ";
            getline(cin, userStringInput);
        }
        newBookData->setBookPublicationDate(userStringInput);
        selectedColumn = "publication_date";

        if (displayChanges(storedBookData, newBookData)) {
            processBookChanges(selectedColumn, selectedBookID, userStringInput);
        }
        else {
            editBookMenuUI(storedBookData);
        }
        
        break;
    case 6:
        cout << "Previous copy count: " << storedBookData->retrieveAvailableCopies() << endl;
        cout << "Enter updated available copy count: ";
        cin >> userIntInput;

        while (!std::cin.good())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        while (userIntInput < 1) {
            cout << "Invalid copy amount entered!" << endl;
            cout << "Enter available copies: ";
            cin >> userIntInput;
        }
        newBookData->setAvailableCopies(userIntInput);
        selectedColumn = "available_copies";
        if (displayChanges(storedBookData, newBookData)) {
            processBookChanges(selectedColumn, selectedBookID, userIntInput);
        }
        else {
            editBookMenuUI(storedBookData);
        }
        break;
    case 7:
        allocatePreparedDeletionStatement();
        bookDeletionProcess(selectedBookID, storedBookData);
        break;
    case 8:
        cout << "Operation cancelled...\n";
        if(newBookData != nullptr)
        delete newBookData;
        break;
    default:
        editBookMenuUI(storedBookData);
        break;
    }
}

void BookManager::processBookChanges(string selectedColumn, int bookID, string userInput) {
    try {
            pqxx::work processBookChange(*conn);
            processBookChange.exec_prepared("edit_book_" + selectedColumn + "", userInput, bookID);
            processBookChange.commit();
            cout << "Changes applied...\n";
    }
    catch (const pqxx::sql_error& e) {
        cerr << "SQL error: " << e.what() << '\n';
    }
    catch (const pqxx::usage_error& e) {
        cerr << "Usage error: " << e.what() << '\n';
        throw;
    }
}

void BookManager::processBookChanges(string selectedColumn, int bookID, int userInput) {
    try {
        pqxx::work processBookChange(*conn);
        processBookChange.exec_prepared("edit_book_" + selectedColumn + "", userInput, bookID);
        processBookChange.commit();
        cout << "Changes applied...\n";
    }
    catch (const pqxx::sql_error& e) {
        cerr << "SQL error: " << e.what() << '\n';
    }
    catch (const pqxx::usage_error& e) {
        cerr << "Usage error: " << e.what() << '\n';
        throw;
    }
}

void BookManager::allocatePreparedDeletionStatement() {
    try {
        conn->prepare("delete_book", "DELETE FROM books WHERE book_id = $1");
    }
    catch (const pqxx::sql_error& e) {
        //error handling is neccessary because prepared statement might still exist within current session
        if (string(e.what()).find("Failure during \'[PREPARE delete_book]\': ERROR:  prepared statement \"delete_book\" already exists"))
            throw;
    }
}

void BookManager::bookDeletionProcess(int bookID, BookInfo* storedBookData) {

    cout << "Book to be deleted:\n";
    displayBookDataListFormat(storedBookData);

    cout << endl;

    while (true) {
        char userInput;
        cout << "\n\nConfirm book deletion? (Y/N): ";
        cin >> userInput;
        userInput = toupper(userInput);
        if (userInput != 'Y' && userInput != 'N') {
            cout << "Invalid option selected...\n";
        }
        else if (userInput == 'Y') {
            system("cls");
            break;
        }
        else {
            system("cls");
            return;
            break;
        }
    }

    try {
        pqxx::work bookDelete(*conn);
        bookDelete.exec_prepared("delete_book", bookID);
        bookDelete.commit();
        cout << "Book deleted successfully...\n";
    }
    catch (const pqxx::sql_error& e) {
        cerr << "SQL error: " << e.what() << '\n';
    }
    catch (const pqxx::usage_error& e) {
        cerr << "Usage error: " << e.what() << '\n';
        throw;
    }
}