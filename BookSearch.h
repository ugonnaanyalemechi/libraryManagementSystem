#pragma once
#include <string>

class BookSearch {
private:
    int resultsRecieved = 0;
    void displaySearchBookUI();
    void processSearchMenuInput(int);
    void prepareRichBookTitleSearch();
    void processRichBookTitleSearch(std::string userSearchTerm, int resultOffset);
public:
    void searchBookProcess();
};