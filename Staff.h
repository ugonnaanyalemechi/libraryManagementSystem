#pragma once
#include <iostream>
#include "User.h";

using std::string;

class Staff :
	public User
{
private:
	string identifyMemberToPromote();
	bool checkMemberExists(string, string&, string&);
	bool confirmPromotion(string, string, bool&);
	void promoteMemberToStaff(string);
public:
	Staff(string, string);
	void staffSignOut();
	void promoteMemberToStaffProcess();
};