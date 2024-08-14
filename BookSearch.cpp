#include "BookSearch.h"
#include "extern.h"
#include <algorithm>
#include "LoanManager.h"
#include "BookInfo.h"

using namespace std;

BookManager bookManager;
LoanManager loanManager;

void BookSearch::searchBookProcess() {
    BookInfo* savedBookSearchResults = new BookInfo[25];
    displaySearchBookUI(savedBookSearchResults);
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
            displaySearchBookUI(savedBookSearchResults);
        }
        else {
            system("cls");
            break;
        }
    }
    delete[] savedBookSearchResults;
}

void BookSearch::displaySearchBookUI(BookInfo*& savedBookSearchResults) {
    cout << "--------------- Search Books:  ---------------" << endl;
    cout << "Search by:\n";
    cout << "#1. Book ID#\n#2. Title\n#3. Author\n#4. Genre\n#5. Cancel Operation\n\n";
    cout << "Please enter the numerical digit of the option you would like to select...\n";
    cout << "Enter here: ";
    int menuIntInput;
    cin >> menuIntInput;

    while (!std::cin.good())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    processSearchMenuInput(menuIntInput, savedBookSearchResults);
}

bool isStringAnInt(const string userString) {
    return userString.find_first_not_of("0123456789") == string::npos;
}

void BookSearch::processSearchMenuInput(int menuInput, BookInfo*& savedBookSearchResults) {
    bool validSearchSelected = false;

    if (menuInput != 200) {
        system("cls");
    } 

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
        cout << "--------------- Search Result:  ---------------\n";
        if (bookManager.retrieveBookByID(bookDisplayData)) {
            bookManager.displayBookListFullInfo(bookDisplayData);
            cout << endl << endl;
        }
        break;
    case 2:
        validSearchSelected = true;
        cout << "Enter a Title: ";
        cin.ignore();
        getline(cin, userInput);
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processRichBookTextSearch(userInput, 0, "title", savedBookSearchResults);
        break;
    case 3:
        validSearchSelected = true;
        cout << "Enter an Author: ";
        cin.ignore();
        getline(cin, userInput);
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processRichBookTextSearch(userInput, 0, "author", savedBookSearchResults);
        break;
    case 4:
        validSearchSelected = true;
        cout << "Enter a Genre: ";
        cin.ignore();
        getline(cin, userInput);
        cout << "--------------- Search Results:  ---------------\n";
        bookManager.displayBookListHeader();
        processRichBookTextSearch(userInput, 0, "genre", savedBookSearchResults);
        break;
    case 5:
        break;
    case 200:
        validSearchSelected = true;
        break;
    default:
        cout << "Invalid option selected...\n\n";
        displaySearchBookUI(savedBookSearchResults);
        break;
    }


    if (validSearchSelected) {
        bool firstRun = true;
        bool isBookIdValid = false;
        string optionInput;
        while (!isBookIdValid) {
            cout << "\nEnter a Book ID# to view more details and options (enter 'C' to cancel): ";
            if (menuInput == 200 && firstRun) {
                cin.ignore();
                firstRun = false;
            }
                
            getline(cin, optionInput);

            if (toupper(optionInput[0]) == 'C') {
                isBookIdValid = true;
            }
            else if (isStringAnInt(optionInput) && optionInput.length() != 0) {
                int bookIndex = stoi(optionInput);
                bookDisplayData->setBookID(bookIndex);
                isBookIdValid = bookManager.retrieveBookByID(bookDisplayData);

                if (isBookIdValid) {
                    system("cls");
                    bookManager.displayBookListFullInfo(bookDisplayData);
                    cout << endl;
                }

                char searchReturnInput = '0';
                while (isBookIdValid) {

                    cout << "1 - Checkout Book" << endl;
                    cout << "2 - Return to Search" << endl;
                    cout << "3 - Exit Search" << endl;

                    cin >> searchReturnInput;
                    switch (searchReturnInput)
                    {
                    case '1':
                        BookInfo* bookToLoan();
                        for (auto book : savedBookSearchResults) {
                            if (to_string(book->retrieveBookId()) == optionInput) {
                                bookToLoan = book;
                                break;
                            }
                        }
                        loanManager.(bookToLoan);
                        break;
                    default:
                        break;
                    }

                    /*
                    cout << "Return to search? (Y/N): ";
                    cin >> searchReturnInput;
                    searchReturnInput = toupper(searchReturnInput);
                    if (searchReturnInput != 'Y' && searchReturnInput != 'N') {
                        cout << "Invalid option selected...\n";
                    }
                    else if (searchReturnInput == 'Y') {
                        system("cls");
                        displayPreviousSearchResults(savedBookSearchResults);
                        processSearchMenuInput(200, savedBookSearchResults);
                        break;
                    }
                    else {
                        system("cls");
                        break;
                    }
                    */
                }
            }
            else {
                isBookIdValid = false;
                cout << "Invalid book ID#...\n";
            }

        }

    }
    delete bookDisplayData;
}

void BookSearch::displayPreviousSearchResults(BookInfo* bookSearchResult) {
    cout << "--------------- Search Results:  ---------------\n";
    for (int i = 0; i < 25; i++) {
        if (bookSearchResult[i].retrieveBookID() != 0) {
            bookManager.displayBookDataListFormat(&bookSearchResult[i]);
            cout << endl;
        }
    }
}

std::string BookSearch::formatSearchText(const std::string& userSearchInput) {
    string formattedText = userSearchInput;
    replace(formattedText.begin(), formattedText.end(), ' ', '&');
    return formattedText;
}

void BookSearch::prepareRichBookSearch() {
    const int richSearchTypeTotal = 3;
    string searchTypes[richSearchTypeTotal] = { "title", "author", "genre"};

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
}


void BookSearch::processRichBookTextSearch(std::string userSearchTerm, int resultOffset, std::string searchType, BookInfo*& savedBookSearch) {
    resultsRecieved = 0;
    //BookInfo* bookData = new BookInfo();
    int rowIterationCounter = 0;
    // Define the search term, limit, and offset
    int limit = 25;
    // Change resultOffset value to paginate through results
    string formattedUserSearchTerm = formatSearchText(userSearchTerm);
    try {
        pqxx::work processTitleSearch(*conn);
        pqxx::result searchResult = processTitleSearch.exec_prepared("book_search_" + searchType + "", formattedUserSearchTerm, limit, resultOffset);
        for (auto row : searchResult) {
            savedBookSearch[rowIterationCounter].setBookID(row["book_id"].as<int>());
            savedBookSearch[rowIterationCounter].setBookTitle(row["title"].c_str());
            savedBookSearch[rowIterationCounter].setBookAuthor(row["author"].c_str());
            savedBookSearch[rowIterationCounter].setBookGenre(row["genre"].c_str());
            savedBookSearch[rowIterationCounter].setBookPublisher(row["publisher"].c_str());
            savedBookSearch[rowIterationCounter].setBookPublicationDate(row["publication_date"].c_str());
            savedBookSearch[rowIterationCounter].setAvailableCopies(row["available_copies"].as<int>());
            bookManager.displayBookDataListFormat(&savedBookSearch[rowIterationCounter]);
            cout << endl;
            rowIterationCounter++;
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