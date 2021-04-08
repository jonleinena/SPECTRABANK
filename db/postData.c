#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postData.h"
#include "dbConnection.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../utils/structures.h"
int modificarProfesional(char *selec, Profesional *prof, char *input)
{

    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql;
    switch (*selec)
    {
    case '1':
        strcpy(sql, "UPDATE PROFESIONAL SET TELEFONO = ? WHERE ID_PROF = ?");
        break;
    case '2':
        strcpy(sql, "UPDATE PROFESIONAL SET CORREO = ? WHERE ID_PROF = ?");
        break;
    case '3':
        strcpy(sql, "UPDATE PROFESIONAL SET TELEFONO = ? WHERE ID_PROF = ?");
        break;
    default:
        break;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        switch (*selec)
        {
        case '1':
            sqlite3_bind_text(res, 1, input, (strlen(input) - 1), SQLITE_STATIC);
            sqlite3_bind_text(res, 2, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
            break;
        case '2':
            sqlite3_bind_text(res, 1, input, (strlen(input) - 1), SQLITE_STATIC);
            sqlite3_bind_text(res, 2, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
            break;
        case '3':
            sqlite3_bind_text(res, 1, input, (strlen(input) - 1), SQLITE_STATIC);
            sqlite3_bind_text(res, 2, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
            break;
        default:
            break;
        }
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    return 0;
}