#include "../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"
#include <stdio.h>

sqlite3 *db;

int startConn(sqlite3 *db)
{
    int rc = sqlite3_open("db/SpectreBankDB.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
}