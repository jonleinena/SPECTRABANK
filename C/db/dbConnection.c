#include "../../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"
#include <stdio.h>

sqlite3 *db;

int startConn()
{
    int rc = sqlite3_open("../SpectreBankDB.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 0;
    }

    return 1;
}