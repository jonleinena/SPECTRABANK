#include <stdio.h>
#include <string.h>
#include "../lib/sqlite3/sqlite3.h"
#include "getData.h"

int getLoginProfesional(char *email, char *contrasenya)
{

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;

    int rc = sqlite3_open("db/SpectreBankDB.db", &db);

    if (rc != SQLITE_OK)
    {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    //TODO - OPTIMIZAR ESTO
    char *sql = "SELECT * FROM PROFESIONAL WHERE CORREO = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {

        sqlite3_bind_text(res, 1, email, -1, SQLITE_STATIC);
    }
    else
    {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    printf("PRIMERA COLUMNA: %s\n", sqlite3_column_text(res, 1)); //pero esto si lo printea

    if (step == SQLITE_ROW)
    {

        printf("%s: ", sqlite3_column_text(res, 0));
        printf("%s\n", sqlite3_column_text(res, 1));
    }

    sqlite3_close(db);

    return 0;
}
