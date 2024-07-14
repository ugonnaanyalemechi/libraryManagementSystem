#pragma once
#include <iostream>
#include "BookManager.h"

using namespace std;

class MenuManager
{
private:
	int userInput;
public:
	void getUserInput();
	void showWelcomeMenu();
	void processWelcomeMenuInput();
};