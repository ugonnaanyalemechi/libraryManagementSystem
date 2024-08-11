#pragma once
#include <string>

class BookSearch {
private:
    int resultsRecieved = 0;
    void displaySearchBookUI();
    void processSearchMenuInput(int);
    std::string formatSearchText(const std::string&);
    void prepareRichBookTitleSearch();
    void processRichBookTitleSearch(std::string userSearchTerm, int resultOffset);
public:
    void searchBookProcess();
};