#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"
#include "BookManager.h"


extern std::string connectionInfo;
extern MenuManager menuManager;
extern BookManager bookManager;
extern pqxx::connection* conn;