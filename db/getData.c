#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/sqlite3/sqlite3.h"
#include "getData.h"

int getLoginProfesional(char *email, char *contrasenya)
{
    int comprobacionContrasenya = 0; //0 si es igual, 1 sino
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
    char *sql = "SELECT CONTRASENYA FROM PROFESIONAL WHERE CORREO = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {

        sqlite3_bind_text(res, 1, email, (strlen(email) - 1), SQLITE_STATIC); //Le pasamos el (strlen(email)-1) para que ignore el /0 del email, si no no funciona
    }
    else
    {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        comprobacionContrasenya = strcmp(contrasenya, sqlite3_column_text(res, 0));
    }
    else
        comprobacionContrasenya = 1;

    sqlite3_close(db);

    return comprobacionContrasenya;
}
