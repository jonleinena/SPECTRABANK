#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getData.h"
#include "dbConnection.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../utils/structures.h"

int numFilas = 1;

int getLogin(char *email, char *contrasenya)
{
    int comprobacionContrasenya = 0; //0 si es igual, diferente a 0 sino
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "SELECT P.CONTRASENYA, C.CONTRASENYA FROM PROFESIONAL P, CLIENTE C WHERE P.CORREO = ? OR C.CORREO = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, email, (strlen(email) - 1), SQLITE_STATIC);
        sqlite3_bind_text(res, 2, email, (strlen(email) - 1), SQLITE_STATIC); //Le pasamos el (strlen(email)-1) para que ignore el /0 del email, si no no funciona
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

Profesional *getInfoProfesional(char *email)
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

    return prof;
    free(prof);
}

//ESTE METODO SE USA PARA ALGO??

Cliente *getInfoCliente(char *email)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;
    Cliente *cli;
    cli = (Cliente *)malloc(sizeof(Cliente));
    cli->user = (Usuario *)malloc(sizeof(Usuario));

    char *sql = "SELECT * FROM CLIENTE WHERE CORREO = ?";

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

        strcpy(cli->user->dni, sqlite3_column_text(res, 0));
        strcpy(cli->user->contrasenya, sqlite3_column_text(res, 1));
        strcpy(cli->user->nombreApellidos, sqlite3_column_text(res, 2));
        cli->user->telefono = sqlite3_column_int(res, 3);
        strcpy(cli->user->email, sqlite3_column_text(res, 4));
        strcpy(cli->domicilio, sqlite3_column_text(res, 5));
        strcpy(cli->user->fechaNacimiento, sqlite3_column_text(res, 6));
    }

    sqlite3_finalize(res);

    return cli;
}

Cliente **getListaClientes(char *idProf)
{
    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT * FROM CLIENTE WHERE ID_PROF = ? ORDER BY DNI ASC";
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

    numFilas = sqlite3_column_int(res1, 0);

    Cliente **lista;
    lista = (Cliente **)malloc(numFilas * sizeof(Cliente *));
    for (int i = 0; i < numFilas; i++)
    {
        *(lista + i) = (Cliente *)malloc(sizeof(Cliente));
        (*(lista + i))->user = (Usuario *)malloc(sizeof(Usuario));
    }

    int i = 0;

    while (step == SQLITE_ROW)
    {
        strcpy((*(lista + i))->user->dni, sqlite3_column_text(res, 0));
        strcpy((*(lista + i))->user->contrasenya, sqlite3_column_text(res, 1));
        strcpy((*(lista + i))->user->nombreApellidos, sqlite3_column_text(res, 2));
        (*(lista + i))->user->telefono = sqlite3_column_int(res, 3);
        strcpy((*(lista + i))->user->email, sqlite3_column_text(res, 4));
        strcpy((*(lista + i))->domicilio, sqlite3_column_text(res, 5));
        strcpy((*(lista + i))->user->fechaNacimiento, sqlite3_column_text(res, 6));


        i++;
        step = sqlite3_step(res);
    }

    sqlite3_finalize(res);

    return lista;
    free(lista); //El resto de punteros se liberan desde el menu, accediendo a ellos a traves del puntero que se crea ahi
}
Cuenta *getCuentasCliente(char *dniCliente)
{

    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT * FROM CUENTA_BANCARIA WHERE DNI_CLI = ?";
    char *sql1 = "SELECT COUNT(*) FROM CUENTA_BANCARIA WHERE DNI_CLI = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, dniCliente, (strlen(dniCliente)), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, dniCliente, (strlen(dniCliente)), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    int step1 = sqlite3_step(res1);
    numFilas = sqlite3_column_int(res1, 0); //PARA SABER CUANTAS FILAS HAY TRAS LA QUERY Y RESERVAR MEMORIA EN FUNVCION A ELLO

    Cuenta *listaCuentas;
    listaCuentas = (Cuenta *)malloc((numFilas) * sizeof(Cuenta));
    int i = 0;
    while (step == SQLITE_ROW)
    {
        strcpy((listaCuentas + i)->iban, sqlite3_column_text(res, 0));
        (listaCuentas + i)->saldo = sqlite3_column_double(res, 1);
        strcpy((listaCuentas + i)->fechaCreacion, sqlite3_column_text(res, 2));
        strcpy((listaCuentas + i)->dniPropietario, sqlite3_column_text(res, 3));
        
        step = sqlite3_step(res);
        i++;
    }

    return listaCuentas;
    free(listaCuentas);
}

Inversion *getInversionClite(char *dniCliente)
{

    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT * FROM ACC_CLI WHERE DNI = ?";
    char *sql1 = "SELECT COUNT(*) FROM ACC_CLI WHERE DNI = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, dniCliente, strlen(dniCliente), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, dniCliente, strlen(dniCliente), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    int step1 = sqlite3_step(res1);
    numFilas = sqlite3_column_int(res1, 0); //PARA SABER CUANTAS FILAS HAY TRAS LA QUERY Y RESERVAR MEMORIA EN FUNVCION A ELLO

    Inversion *listaInversiones;
    listaInversiones = (Inversion *)malloc(numFilas * sizeof(Inversion));

    int i = 0;
    while (step == SQLITE_ROW)
    {
        strcpy((listaInversiones + i)->idCompania, sqlite3_column_text(res, 1));
        (listaInversiones + i)->valorCompra = sqlite3_column_double(res, 2);
        (listaInversiones + i)->cantidad = sqlite3_column_double(res, 3);
        strcpy((listaInversiones + i)->fechaCompra, sqlite3_column_text(res, 4));
        i++;
        step = sqlite3_step(res);
    }

    return listaInversiones;
    free(listaInversiones);
}

Prestamo *getPrestamos(char *dniCliente)
{
    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT * FROM PRESTAMO WHERE DNI_CLI = ?";
    char *sql1 = "SELECT COUNT(*) FROM PRESTAMO WHERE DNI_CLI = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, dniCliente, strlen(dniCliente), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, dniCliente, strlen(dniCliente), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    int step1 = sqlite3_step(res1);
    numFilas = sqlite3_column_int(res1, 0);

    Prestamo *listaPrestamos;
    listaPrestamos = (Prestamo *)malloc(numFilas * sizeof(Prestamo));

    int i = 0;
    while (step == SQLITE_ROW)
    {
        (listaPrestamos + i)->idPres = sqlite3_column_int(res, 0);
        strcpy((listaPrestamos + i)->idProfesional, sqlite3_column_text(res, 2));
        (listaPrestamos + i)->importe = sqlite3_column_double(res, 3);
        strcpy((listaPrestamos + i)->fechaEmision, sqlite3_column_text(res, 4));
        sqlite3_column_text(res, 5) == NULL ? strcpy((listaPrestamos + i)->fechaDevol, "NULL") : strcpy((listaPrestamos + i)->fechaDevol, sqlite3_column_text(res, 5));
        sqlite3_column_text(res, 6) == NULL ? strcpy((listaPrestamos + i)->fechaComp, "NULL") : strcpy((listaPrestamos + i)->fechaComp, sqlite3_column_text(res, 6));
        (listaPrestamos + i)->tae = sqlite3_column_double(res, 7);

        i++;
        step = sqlite3_step(res);
    }

    return listaPrestamos;
    free(listaPrestamos);
}

Movimiento *getMovimientos(Cuenta *cue)
{
    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT * FROM MOVIMIENTO WHERE IBAN_ORIGEN = ? OR IBAN_DESTINO = ? ORDER BY ID_MOV DESC";
    char *sql1 = "SELECT COUNT(*) FROM MOVIMIENTO WHERE IBAN_ORIGEN = ? OR IBAN_DESTINO = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, cue->iban, (strlen(cue->iban)), SQLITE_STATIC);
        sqlite3_bind_text(res, 2, cue->iban, (strlen(cue->iban)), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, cue->iban, (strlen(cue->iban)), SQLITE_STATIC);
        sqlite3_bind_text(res1, 2, cue->iban, (strlen(cue->iban)), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    int step1 = sqlite3_step(res1);
    numFilas = sqlite3_column_int(res1, 0);

    Movimiento *movimientos;
    movimientos = (Movimiento *)malloc(numFilas * sizeof(Movimiento));

    int i = 0;
    while (step == SQLITE_ROW)
    {
        (movimientos + i)->idTransaccion = sqlite3_column_int(res, 0);
        strcpy((movimientos + i)->ibanOrigen, sqlite3_column_text(res, 1));
        strcpy((movimientos + i)->ibanDestino, sqlite3_column_text(res, 2));
        (movimientos + i)->importe = sqlite3_column_double(res, 3);
        strcpy((movimientos + i)->fecha, sqlite3_column_text(res, 4));
        strcpy((movimientos + i)->concepto, sqlite3_column_text(res, 5));
        i++;
        step = sqlite3_step(res);
    }

    return movimientos;
    free(movimientos);
}

Prestamo *getSolicitudesPrestamo(Profesional *prof)
{
    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT * FROM PRESTAMO WHERE ID_PROF = ? AND ESTADO = ?";
    char *sql1 = "SELECT COUNT(*) FROM PRESTAMO WHERE ID_PROF = ? AND ESTADO = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
        sqlite3_bind_int(res, 2, 1);
        sqlite3_bind_text(res1, 1, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
        sqlite3_bind_int(res1, 2, 1);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    int step1 = sqlite3_step(res1);
    numFilas = sqlite3_column_int(res1, 0);

    Prestamo *listaPrestamosPendientes;
    listaPrestamosPendientes = (Prestamo *)malloc(numFilas * sizeof(Prestamo));

    int i = 0;
    while (step == SQLITE_ROW)
    {
        (listaPrestamosPendientes + i)->idPres = sqlite3_column_int(res, 0);
        printf("%i", i);
        strcpy((listaPrestamosPendientes + i)->cli->user->dni, sqlite3_column_text(res, 1));
        printf("%s",(listaPrestamosPendientes + i)->cli->user->dni);
        (listaPrestamosPendientes + i)->importe = sqlite3_column_double(res, 3);
        printf("%i", i);
        strcpy((listaPrestamosPendientes + i)->fechaSoli, sqlite3_column_text(res, 4));
        printf("%i", i);
        i++;
        step = sqlite3_step(res);
    }
    

    return listaPrestamosPendientes;
    free(listaPrestamosPendientes);
}