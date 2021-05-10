#include "../../../lib/sqlite3/sqlite3.h"
#ifndef DB_CONN
#define DB_CONN

extern sqlite3 *db;

int startConn();

#endif