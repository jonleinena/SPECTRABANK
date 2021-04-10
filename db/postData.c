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
    char *sql1 = "UPDATE PROFESIONAL SET TELEFONO = ? WHERE ID_PROF = ?";
    char *sql2 = "UPDATE PROFESIONAL SET CORREO = ? WHERE ID_PROF = ?";
    char *sql3 = "UPDATE PROFESIONAL SET TELEFONO = ? WHERE ID_PROF = ?";

    switch (*selec)
    {
    case '1':
        sql = sql1;
        break;
    case '2':
        sql = sql2;
        break;
    case '3':
        sql = sql3;
        break;
    default:
        break;
    }

    //printf("%s\n", sql);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {

        switch (*selec)
        {
        case '1':

            sqlite3_bind_text(res, 1, input, (strlen(input)), SQLITE_STATIC);
            sqlite3_bind_text(res, 2, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);

            break;
        case '2':
            sqlite3_bind_text(res, 1, input, (strlen(input)), SQLITE_STATIC);
            sqlite3_bind_text(res, 2, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
            break;
        case '3':
            sqlite3_bind_text(res, 1, input, (strlen(input)), SQLITE_STATIC);
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

    int step = sqlite3_step(res);
    sqlite3_finalize(res);

    return step;
}
/////////////////

int modificarPrestamoADenegado(int *idPrestamo)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "UPDATE PRESTAMO SET ESTADO = ? WHERE ID_PREST = ?";

    //printf("%s\n", sql);
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {

        sqlite3_bind_int(res, 1, 3);
        sqlite3_bind_int(res, 2, *idPrestamo);

    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    sqlite3_finalize(res);

    return step;
}