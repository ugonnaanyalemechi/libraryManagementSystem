#include <string>
#include "pqxx/pqxx"
#include "MenuManager.h"

using namespace std;

extern string connectionInfo;
extern MenuManager menuManager;
extern pqxx::connection* conn;