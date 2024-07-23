#pragma once
#include <iostream>

class MenuManager
{
private:
	bool quit = false;
	int getUserInput();
	void showWelcomeMenu();
	void processWelcomeMenuInput(int);
	void showMemberMainMenu();
	void processMemberMainMenu(int);
	void showAdminMainMenu();
	void processAdminMainMenu(int);
public:
	void beginMenuProcess();
};