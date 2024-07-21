#pragma once
#include <iostream>
#include "BookManager.h"

class MenuManager
{
private:
	int userInput;
public:
	void getUserInput();
	void showWelcomeMenu();
	void processWelcomeMenuInput();
	void showMemberMainMenu();
	void processMemberMainMenu();
};