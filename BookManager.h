#pragma once
#include "BookInfo.h"
#include <string>

class BookManager{
private:
    //Values to adjust # of characters in elements for in-terminal book info display:
    int maxIdDisplayLength = 6;
    int maxTitleDisplayLength = 30;
    int maxAuthorDisplayLength = 15;
    int maxGenreDisplayLength = 20;
    int maxPublisherDisplayLength = 20;

    void appendBookToDatabase(std::string, std::string, std::string, std::string, std::string, int);
    void displayAddBookUI();
    void displayEditBookUI();
    void processBookChanges(std::string,int ,std::string);
    void processBookChanges(std::string, int, int);
    int convertStringToInt(std::string);
    bool displayChanges(BookInfo*&, BookInfo*&);
    void allocatePreparedEditStatement();
    void allocatePreparedRetrieveStatement();
    void editBookMenuUI(BookInfo*&);
    void manageEditMenuSelection(int, BookInfo*&);
    void bookDeletionProcess(int, BookInfo*);
    void allocatePreparedDeletionStatement();
    bool isBookIDValid; 
    void retrieveBookByID(int, BookInfo*&);
public:
    bool checkDate(std::string);
    void addBookProcess();
    void editBookProcess();
    bool retrieveBookByID(BookInfo* bookData);
    void displayBookData(BookInfo*);
    void displayBookListHeader();
};