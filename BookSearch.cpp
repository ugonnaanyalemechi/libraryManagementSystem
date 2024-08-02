#include "BookSearch.h"
#include "extern.h"

using namespace std;

void BookSearch::searchBookProcess() {
    displaySearchBookUI();
}

void BookSearch::displaySearchBookUI() {
    cout << "--------------- Search Books:  ---------------" << endl;
    cout << "Search by:\n";
    cout << "#1. Book ID#\n#2. Title\n#3. Author\n#4. Publisher\n#5. Date Published\n\n";
    cout << "Please enter the numerical digit of the option you would like to select...\n";
    cout << "Enter here: ";
    int menuIntInput;
    cin >> menuIntInput;
}

void BookSearch::processSearchMenuInput(int menuInput) {
    switch (menuInput) {
    case 1:
        BookInfo* bookDisplayData;
        int bookID;
        //bool isBookIDValid = false;
        cout << "Enter a valid book ID#: ";
        cin >> bookID;
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    default:
        cout << "Invalid option selected...\n\n";
        break;
    }
}