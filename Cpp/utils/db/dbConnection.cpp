#include "dbConnection.h"
#include "../../../lib/sqlite3/sqlite3.h"
#include <iostream>

using namespace std;

sqlite3 *db;

int startConn()
{
    int rc = sqlite3_open("../SpectreBankDB.db", &db);
    if (rc != SQLITE_OK)
    {
        cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 0;
    }
    return 1;
}