#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"
#include "BookManager.h"
#include "BookSearch.h"
#include "EntryManager.h"


extern std::string connInfo;
extern pqxx::connection* conn;