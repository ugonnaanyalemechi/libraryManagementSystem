#pragma once
#include <string>

class BookManager {
private:
    void appendBookToDatabase(std::string, std::string, std::string, std::string, int);
    void displayAddBookUI();
public:
    void addBookProcess();
};