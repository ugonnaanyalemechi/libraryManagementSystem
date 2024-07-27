#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"
#include "BookManager.h"
#include "EntryManager.h"


extern std::string connInfo;
extern MenuManager menuManager;
extern BookManager bookManager;
extern EntryManager entryManager;
extern pqxx::connection* conn;