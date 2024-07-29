#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"
#include "BookManager.h"
#include "EntryManager.h"
#include "User.h"
#include "Staff.h"

extern std::string connInfo;
extern MenuManager menuManager;
extern BookManager bookManager;
extern EntryManager entryManager;
extern User* user;
extern Staff* admin;
extern pqxx::connection* conn;