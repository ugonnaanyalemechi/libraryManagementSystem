#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"
#include "BookManager.h"

using namespace std;

extern string connectionInfo;
extern MenuManager menuManager;
extern BookManager bookManager;
extern pqxx::connection* conn;