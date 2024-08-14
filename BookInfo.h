#pragma once
#include <string>

class BookInfo {
private:
    int bookID;
    std::string title;
    std::string author;
    std::string genre;
    std::string publisher;
    std::string publicationDate;
    int availableCopies;
    
public:
    void setBookID(int);
    void setBookID(std::string);
    void setBookTitle(std::string);
    void setBookAuthor(std::string);
    void setBookGenre(std::string);
    void setBookPublisher(std::string);
    void setBookPublicationDate(std::string);
    void setAvailableCopies(int);

    int retrieveBookID();
    std::string retrieveBookTitle();
    std::string retrieveBookAuthor();
    std::string retrieveBookGenre();
    std::string retrieveBookPublisher();
    std::string retrieveBookPublicationDate();
    int retrieveAvailableCopies();
    BookInfo();
    BookInfo(int, std::string, std::string, std::string, std::string, std::string, int);
};