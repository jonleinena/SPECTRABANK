#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"
#include "../structures/structures.h"
#include "getData.h"

int getLoginProfesional(char *email, char *contrasenya, sqlite3 *db);

Profesional *getInfoProfesional(char *email, sqlite3 *db);
Cliente **getListaClientes(char *idProf, int *numFilas, sqlite3 *db);

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

Cliente **getListaClientes(char *idProf, int *numFilas, sqlite3 *db)
{
    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT DNI, CONTRASENYA, NOMBRE, NUM_TEL, CORREO, FEC_NAC, DOMICILIO FROM CLIENTE WHERE ID_PROF = ? ORDER BY DNI ASC";
    char *sql1 = "SELECT COUNT(*) FROM CLIENTE WHERE ID_PROF = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, idProf, (strlen(idProf)), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, idProf, (strlen(idProf)), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    int step1 = sqlite3_step(res1);

    *numFilas = sqlite3_column_int(res1, 0);

    Cliente **lista;
    lista = (Cliente **)malloc((*numFilas) * sizeof(Cliente *));
    for (int i = 0; i < *numFilas; i++)
    {
        *(lista + i) = (Cliente *)malloc(sizeof(Cliente));
        (*(lista + i))->user = (Usuario *)malloc(sizeof(Usuario));
    }

    printf("NUMFILAS: %i\n", *numFilas);

    int i = 0;

    while (step == SQLITE_ROW && i <= *numFilas)
    {

        strcpy((*(lista + i))->user->dni, sqlite3_column_text(res, 0));
        strcpy((*(lista + i))->user->contrasenya, sqlite3_column_text(res, 1));
        strcpy((*(lista + i))->user->nombreApellidos, sqlite3_column_text(res, 2));
        (*(lista + i))->user->telefono = sqlite3_column_int(res, 3);
        strcpy((*(lista + i))->user->email, sqlite3_column_text(res, 4));
        strcpy((*(lista + i))->user->fechaNacimiento, sqlite3_column_text(res, 5));
        strcpy((*(lista + i))->domicilio, sqlite3_column_text(res, 6));

        step = sqlite3_step(res);

        i += 1;
    }

    sqlite3_finalize(res);

    return lista;

    //EL FREE DE LA MEMORIA SE HACE DESDE EL MENU, CUANDO EL USUARIO DECIDE SALIR
}
