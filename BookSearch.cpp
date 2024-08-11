#include "BookSearch.h"
#include "extern.h"
#include <algorithm>

using namespace std;

BookManager bookManager;

void BookSearch::searchBookProcess() {
    displaySearchBookUI();
    char userInput = '0';
    while (true) {
        ;       cout << "Search again? (Y/N): ";
        cin >> userInput;
        userInput = toupper(userInput);
        if (userInput != 'Y' && userInput != 'N') {
            cout << "Invalid option selected...\n";
        }
        else if (userInput == 'Y') {
            system("cls");
            displaySearchBookUI();
        }
        else {
            system("cls");
            break;
        }
    }
}

void BookSearch::displaySearchBookUI() {
    cout << "--------------- Search Books:  ---------------" << endl;
    cout << "Search by:\n";
    cout << "#1. Book ID#\n#2. Title\n#3. Author\n#4. Publisher\n#5. Date Published\n\n";
    cout << "Please enter the numerical digit of the option you would like to select...\n";
    cout << "Enter here: ";
    int menuIntInput;
    cin >> menuIntInput;
    processSearchMenuInput(menuIntInput);
}

void BookSearch::processSearchMenuInput(int menuInput) {
    system("cls");
    std::string userInput;
    BookInfo* bookDisplayData = new BookInfo();
    switch (menuInput) {
    case 1:
        int bookID;
        cout << "Enter a valid book ID#: ";
        cin >> bookID;
        bookDisplayData->setBookID(bookID);
        cout << "--------------- Search Results:  ---------------\n";
        if (bookManager.retrieveBookByID(bookDisplayData)) {
            bookManager.displayBookData(bookDisplayData);
            cout << endl << endl;
        }
        else {
            cout << "Book not found!\n\n";
        }
        break;
    case 2:
        cout << "Enter a Title: ";
        cin.ignore();
        getline(cin, userInput);
        prepareRichBookTitleSearch();
        cout << "--------------- Search Results:  ---------------\n";
        processRichBookTitleSearch(userInput, 0);
        break;
    case 3:
        cout << "--------------- Search Results:  ---------------\n";
        break;
    case 4:
        cout << "--------------- Search Results:  ---------------\n";
        break;
    case 5:
        cout << "--------------- Search Results:  ---------------\n";
        break;
    default:
        cout << "Invalid option selected...\n\n";
        displaySearchBookUI();
        break;
    }
    delete bookDisplayData;
}

std::string BookSearch::formatSearchText(const std::string& userSearchInput) {
    string formattedText = userSearchInput;
    replace(formattedText.begin(), formattedText.end(), ' ', '&');
    return formattedText;
}

void BookSearch::prepareRichBookTitleSearch() {

    try {
        conn->prepare("bookTitleSearch", "SELECT book_id, title, author, publisher, publication_date, available_copies FROM public.books WHERE title_tsvector @@ to_tsquery('english', $1) LIMIT $2 OFFSET $3");
    }//WHERE ts @@ phraseto_tsquery('english', $1) 
    catch (const pqxx::sql_error& e) {
        //error handling is neccessary because prepared statement might still exist within current session
        if (string(e.what()).find("Failure during \'[PREPARE bookTitleSearch]\': ERROR:  prepared statement \"bookTitleSearch\" already exists"))
            throw;
    }
}

void BookSearch::processRichBookTitleSearch(std::string userSearchTerm, int resultOffset) {
    resultsRecieved = 0;
    BookInfo* bookData = new BookInfo();
    // Define the search term, limit, and offset
    int limit = 25;
    // Change resultOffset value to paginate through results
    string formattedUserSearchTerm = formatSearchText(userSearchTerm);
    try {
        pqxx::work processTitleSearch(*conn);
        pqxx::result searchResult = processTitleSearch.exec_prepared("bookTitleSearch", formattedUserSearchTerm, limit, resultOffset);
        for (auto row : searchResult) {
            bookData->setBookID(row["book_id"].as<int>());
            bookData->setBookTitle(row["title"].c_str());
            bookData->setBookAuthor(row["author"].c_str());
            bookData->setBookPublisher(row["publisher"].c_str());
            bookData->setBookPublicationDate(row["publication_date"].c_str());
            bookData->setAvailableCopies(row["available_copies"].as<int>());
            bookManager.displayBookData(bookData);
            cout << endl;
        }
        processTitleSearch.commit();
    }
    catch (const pqxx::sql_error& e) {
        cerr << "SQL error: " << e.what() << '\n';
    }
    catch (const pqxx::usage_error& e) {
        cerr << "Usage error: " << e.what() << '\n';
        throw;
    }
}