#pragma once
#include <string>

class BookSearch {
private:
    int resultsRecieved = 0;
    void displaySearchBookUI();
    void processSearchMenuInput(int);
    std::string formatSearchText(const std::string&);
    void prepareRichBookSearch();
    void processPublicationDateSearch(std::string);
    void processRichBookTextSearch(std::string userSearchTerm, int resultOffset, std::string);
public:
    void searchBookProcess();
};