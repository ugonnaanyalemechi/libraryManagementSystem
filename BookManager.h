#pragma once
#include "BookInfo.h"
#include <string>

class BookManager{
private:
    void appendBookToDatabase(std::string, std::string, std::string, std::string, int);
    void displayAddBookUI();
    void displayEditBookUI();
    void processBookChanges(std::string,int ,std::string);
    void processBookChanges(std::string, int, int);
    int convertStringToInt(std::string);
    bool displayChanges(BookInfo*&, BookInfo*&);
    void allocatePreparedEditStatement();
    void allocatePreparedRetrieveStatement();
    void displayBookData(BookInfo*);
    void editBookMenuUI(BookInfo*&);
    void manageEditMenuSelection(int, BookInfo*&);
    void bookDeletionProcess(int, BookInfo*);
    void allocatePreparedDeletionStatement();
    bool isBookIDValid;
    BookInfo* retrieveBookByID(int);
    void retrieveBookByID(int, BookInfo*&);
public:
    void addBookProcess();
    void editBookProcess();
};