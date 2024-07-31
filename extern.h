#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"
#include "BookManager.h"
#include "BookSearch.h"


extern std::string connInfo;
extern MenuManager menuManager;
extern BookManager bookManager;
extern BookSearch bookSearch;
extern pqxx::connection* conn;