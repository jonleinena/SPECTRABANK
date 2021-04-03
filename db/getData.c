#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"
#include "../structures/structures.h"
#include "getData.h"

int getLoginProfesional(char *email, char *contrasenya, sqlite3 *db);

Profesional *getInfoProfesional(char *email, sqlite3 *db);
Cliente **getListaClientes(char *idProf, sqlite3 *db);

int getLoginProfesional(char *email, char *contrasenya, sqlite3 *db)
{
    int comprobacionContrasenya = 0; //0 si es igual, diferente a 0 sino
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

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

    return comprobacionContrasenya;
}

Profesional *getInfoProfesional(char *email, sqlite3 *db)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;
    Profesional *prof;
    prof = (Profesional *)malloc(sizeof(Profesional));
    prof->user = (Usuario *)malloc(sizeof(Usuario));

    char *sql = "SELECT * FROM PROFESIONAL WHERE CORREO = ?";

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

        strcpy(prof->user->dni, sqlite3_column_text(res, 5));
        strcpy(prof->user->contrasenya, sqlite3_column_text(res, 1));
        strcpy(prof->user->email, sqlite3_column_text(res, 4));
        strcpy(prof->user->fechaNacimiento, sqlite3_column_text(res, 3));
        strcpy(prof->user->nombreApellidos, sqlite3_column_text(res, 2));
        strcpy(prof->idProfesional, sqlite3_column_text(res, 0));
        prof->user->telefono = sqlite3_column_int(res, 6);
    }

    sqlite3_finalize(res);

    return prof;
}

Cliente **getListaClientes(char *idProf, sqlite3 *db)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;
    Cliente **lista;
    lista = (Cliente **)malloc(50 * sizeof(Cliente *));
    *lista = (Cliente *)malloc(sizeof(Cliente));
    (*lista)->user = (Usuario *)malloc(sizeof(Usuario));

    char *sql = "SELECT DNI, CONTRASENYA, NOMBRE, NUM_TEL, CORREO, FEC_NAC, DOMICILIO FROM CLIENTE WHERE ID_PROF = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, idProf, (strlen(idProf)), SQLITE_STATIC); //Le pasamos el (strlen(idProf)-1) para que ignore el /0 del email, si no no funciona
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        int i = 0;
        while (step != SQLITE_DONE)
        {

            strcpy((*(lista + i))->user->dni, sqlite3_column_text(res, 0));
            strcpy((*(lista + i))->user->contrasenya, sqlite3_column_text(res, 1));
            strcpy((*(lista + i))->user->nombreApellidos, sqlite3_column_text(res, 2));
            (*(lista + i))->user->telefono = sqlite3_column_int(res, 3);
            strcpy((*(lista + i))->user->email, sqlite3_column_text(res, 4));
            strcpy((*(lista + i))->user->fechaNacimiento, sqlite3_column_text(res, 5));
            strcpy((*(lista + i))->domicilio, sqlite3_column_text(res, 6));

            printf("%s\n", (*(lista + i))->user->dni);
            printf("%s\n", (*(lista + i))->user->contrasenya);
            printf("%s\n", (*(lista + i))->user->nombreApellidos);
            printf("%s\n", (*(lista + i))->user->email);
            printf("%s\n", (*(lista + i))->user->fechaNacimiento);
            printf("%s\n", (*(lista + i))->domicilio);
            printf("%i\n", (*(lista + i))->user->telefono);
            i++;
        }
        step = sqlite3_step(res);
    }

    sqlite3_finalize(res);

    return lista;
}
