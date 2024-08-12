#include "BookSearch.h"
#include "extern.h"
#include <algorithm>

using namespace std;

BookManager bookManager;

void BookSearch::searchBookProcess() {
    displaySearchBookUI();
    char userInput = '0';
    while (true) {
        cout << "Search again? (Y/N): ";
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
    cout << "#1. Book ID#\n#2. Title\n#3. Author\n#4. Genre\n#5. Publisher\n#6. Date Published\n#7. Cancel Operation\n\n";
    cout << "Please enter the numerical digit of the option you would like to select...\n";
    cout << "Enter here: ";
    int menuIntInput;
    cin >> menuIntInput;

    while (!std::cin.good())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    processSearchMenuInput(menuIntInput);
}

void BookSearch::processSearchMenuInput(int menuInput) {
    system("cls");
    std::string userInput;
    BookInfo* bookDisplayData = new BookInfo();
    prepareRichBookSearch();
    switch (menuInput) {
    case 1:
        int bookID;
        cout << "Enter a valid book ID#: ";
        cin >> bookID;
        while (!std::cin.good())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        bookDisplayData->setBookID(bookID);
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
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
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processRichBookTextSearch(userInput, 0, "title");
        break;
    case 3:
        cout << "Enter an Author: ";
        cin.ignore();
        getline(cin, userInput);
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processRichBookTextSearch(userInput, 0, "author");
        break;
    case 4:
        cout << "Enter a Genre: ";
        cin.ignore();
        getline(cin, userInput);
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processRichBookTextSearch(userInput, 0, "genre");
        break;
    case 5:
        cout << "Enter a Publisher: ";
        cin.ignore();
        getline(cin, userInput);
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processRichBookTextSearch(userInput, 0, "publisher");
        break;
    case 6:
        cout << "Enter the Publication Date (YYYY-MM-DD): ";
        cin.ignore();
        getline(cin, userInput);
        while (!bookManager.checkDate(userInput)) {
            cout << "Invalid date format entered!" << endl;
            cout << "Enter the Publication Date (YYYY-MM-DD): ";
            getline(cin, userInput);
        }
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processPublicationDateSearch(userInput);
        break;
    case 7:
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

void BookSearch::prepareRichBookSearch() {
    const int richSearchTypeTotal = 4;
    string searchTypes[richSearchTypeTotal] = { "title", "author", "genre", "publisher"};

    //Prepares search for text-based searches
    for (int i = 0; i < richSearchTypeTotal; i++) {
        try {
            conn->prepare("book_search_" + searchTypes[i] + "", "SELECT book_id, title, author, genre, publisher, publication_date, available_copies FROM public.books WHERE " + searchTypes[i] + "_tsvector @@ to_tsquery('english', $1) LIMIT $2 OFFSET $3");
        }
        catch(const pqxx::sql_error& e) {
            //error handling is neccessary because prepared statement might still exist within current session
            if (string(e.what()).find("Failure during \'[PREPARE book_search_" + searchTypes[i] + "]\': ERROR:  prepared statement \"book_search_" + searchTypes[i] + "\" already exists"))
                throw;
        }
    }

    //Prepares search for publication_date searches
    try {
        conn->prepare("book_search_publication_date", "SELECT book_id, title, author, genre, publisher, publication_date, available_copies FROM public.books WHERE publication_date = $1");
    }
    catch(const pqxx::sql_error& e) {
        if (string(e.what()).find("Failure during \'[PREPARE book_search_publication_date]\': ERROR:  prepared statement \"book_search_publication_date\" already exists"))
            throw;
    }
}

void BookSearch::processPublicationDateSearch(std::string userDateInput) {
    resultsRecieved = 0;
    BookInfo* bookData = new BookInfo();
    try {
        pqxx::work processDateSearch(*conn);
        pqxx::result searchResult = processDateSearch.exec_prepared("book_search_publication_date", userDateInput);
        for (auto row : searchResult) {
            bookData->setBookID(row["book_id"].as<int>());
            bookData->setBookTitle(row["title"].c_str());
            bookData->setBookAuthor(row["author"].c_str());
            bookData->setBookGenre(row["genre"].c_str());
            bookData->setBookPublisher(row["publisher"].c_str());
            bookData->setBookPublicationDate(row["publication_date"].c_str());
            bookData->setAvailableCopies(row["available_copies"].as<int>());
            bookManager.displayBookData(bookData);
            cout << endl;
        }
        processDateSearch.commit();
    }
    catch (const pqxx::sql_error& e) {
        cerr << "SQL error: " << e.what() << '\n';
    }
    catch (const pqxx::usage_error& e) {
        cerr << "Usage error: " << e.what() << '\n';
        throw;
    }
}


void BookSearch::processRichBookTextSearch(std::string userSearchTerm, int resultOffset, std::string searchType) {
    resultsRecieved = 0;
    BookInfo* bookData = new BookInfo();
    // Define the search term, limit, and offset
    int limit = 25;
    // Change resultOffset value to paginate through results
    string formattedUserSearchTerm = formatSearchText(userSearchTerm);
    try {
        pqxx::work processTitleSearch(*conn);
        pqxx::result searchResult = processTitleSearch.exec_prepared("book_search_" + searchType + "", formattedUserSearchTerm, limit, resultOffset);
        for (auto row : searchResult) {
            bookData->setBookID(row["book_id"].as<int>());
            bookData->setBookTitle(row["title"].c_str());
            bookData->setBookAuthor(row["author"].c_str());
            bookData->setBookGenre(row["genre"].c_str());
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