#pragma once
#include <iostream>

class MenuManager
{
private:
	bool quit = false;
	void processWelcomeMenuInput(int);
	void processMemberMainMenu(int);
	void processAdminMainMenu(int);
public:
	int getUserInput();
	void beginMenuProcess();
	void showWelcomeMenu();
	void showAdminMainMenu();
	void showMemberMainMenu();
};