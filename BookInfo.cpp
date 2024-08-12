#include "BookInfo.h"

BookInfo::BookInfo() {
    bookID = 0;
    title = "N/A";
    author = "N/A";
    genre = "N/A";
    publisher = "N/A";
    publicationDate = "N/A";
    availableCopies = 0;
}

BookInfo::BookInfo(int newBookID, std::string newBookTitle, std::string newBookAuthor, std::string newBookGenre, 
                   std::string newBookPublisher, std::string newBookPublicationDate, int newCopyCount)
{
    bookID = newBookID;
    title = newBookTitle;
    author = newBookAuthor;
    publisher = newBookPublisher;
    publicationDate = newBookPublicationDate;
    availableCopies = newCopyCount;
}

void BookInfo::setBookID(int newBookID)
{
    bookID = newBookID;
}

void BookInfo::setBookID(std::string newBookID)
{
    bookID = stoi(newBookID);
}

void BookInfo::setBookTitle(std::string newBookTitle)
{
    title = newBookTitle;
}

void BookInfo::setBookAuthor(std::string newBookAuthor)
{
    author = newBookAuthor;
}

void BookInfo::setBookGenre(std::string newBookGenre)
{
    genre = newBookGenre;
}

void BookInfo::setBookPublisher(std::string newBookPublisher)
{
    publisher = newBookPublisher;
}

void BookInfo::setBookPublicationDate(std::string newBookPublicationDate)
{
    publicationDate = newBookPublicationDate;
}

void BookInfo::setAvailableCopies(int newCopyCount)
{
    availableCopies = newCopyCount;
}

int BookInfo::retrieveBookID()
{
    return bookID;
}

std::string BookInfo::retrieveBookTitle()
{
    return title;
}

std::string BookInfo::retrieveBookAuthor()
{
    return author;
}

std::string BookInfo::retrieveBookGenre()
{
    return genre;
}

std::string BookInfo::retrieveBookPublisher()
{
    return publisher;
}

std::string BookInfo::retrieveBookPublicationDate()
{
    return publicationDate;
}

int BookInfo::retrieveAvailableCopies()
{
    return availableCopies;
}