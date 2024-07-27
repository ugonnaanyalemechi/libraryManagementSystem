#pragma once
#include <string>

class BookManager {
private:
    void appendBookToDatabase(std::string, std::string, std::string, std::string, int);
    void displayAddBookUI();
    void displayEditBookUI();
    void manageEditMenuSelection(int, std::string*);
    void processBookChanges(std::string,int ,std::string);
    void processBookChanges(std::string, int, int);
    int convertStringToInt(std::string);
    void allocatePreparedEditStatement();
    void editBookMenuUI(std::string*);
    bool displayChanges(std::string*, std::string, int);
    void bookDeletionProcess(int, std::string*);
    void allocatePreparedDeletionStatement();
public:
    void addBookProcess();
    void editBookProcess();
};