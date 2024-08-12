#pragma once
#include "BookInfo.h"
#include <string>

class BookManager{
private:
    
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
};