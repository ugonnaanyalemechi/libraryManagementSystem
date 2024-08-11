#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"
#include "BookManager.h"
#include "BookSearch.h"
#include "EntryManager.h"
#include "User.h"
#include "Staff.h"

extern std::string connInfo;
extern pqxx::connection* conn;
extern User* user;
extern Staff* admin;