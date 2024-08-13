#pragma once
#include <string>
#include "pqxx/pqxx"
#include "BookInfo.h"

class BookSearch {
private:
    int resultsRecieved = 0;
    void processSearchMenuInput(int menuInput, BookInfo*& savedBookSearchResults);
    void displayPreviousSearchResults(BookInfo* bookSearchResult);
    std::string formatSearchText(const std::string&);
    void prepareRichBookSearch();
    void processRichBookTextSearch(std::string userSearchTerm, int resultOffset, std::string searchType, BookInfo*& savedBookSearch);
public:
    void searchBookProcess();
    void displaySearchBookUI(BookInfo*& savedBookSearchResults);
};