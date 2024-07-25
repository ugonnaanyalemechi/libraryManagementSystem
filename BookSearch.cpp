#include "BookSearch.h"

using namespace std;

void BookSearch::searchBookProcess() {
    displaySearchBookUI();
}

void BookSearch::displaySearchBookUI() {
    cout << "--------------- Search Books:  ---------------" << endl;
    cout << "Search by:\n";
    cout << "#1. Title\n#2. Author\n#3. Publisher\n#4. Date Published\n\n";
    cout << "Please enter the numerical digit of the option you would like to select...\n";
    cout << "Enter here: ";
    int menuIntInput;
    cin >> menuIntInput;
}