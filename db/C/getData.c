#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getData.h"
#include "../dbConnection.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../../main/C/utils/structures.h"

int numFilas = 1;

int getLogin(char *id, char *contrasenya, int userType) //userType=0 -> Cliente / userType=1 -> Profesional
{
    int comprobacionContrasenya = 0; //0 si es igual, diferente a 0 sino
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "SELECT C.CONTRASENYA, P.CONTRASENYA FROM PROFESIONAL P, CLIENTE C WHERE P.ID_PROF = ? OR C.DNI = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, id, (strlen(id) - userType), SQLITE_STATIC);
        sqlite3_bind_text(res, 2, id, (strlen(id) - userType), SQLITE_STATIC); //Le pasamos el (strlen(email)-1) para que ignore el /0 del email, si no no funciona
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        comprobacionContrasenya = strcmp(contrasenya, (const char *)sqlite3_column_text(res, userType));
    }
    else
        comprobacionContrasenya = 1;

    return comprobacionContrasenya;
}

Profesional *getInfoProfesional(char *id)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;
    Profesional *prof;
    prof = (Profesional *)malloc(sizeof(Profesional));
    prof->user = (Usuario *)malloc(sizeof(Usuario));

    char *sql = "SELECT * FROM PROFESIONAL WHERE ID_PROF = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, id, (strlen(id) - 1), SQLITE_STATIC); //Le pasamos el (strlen(email)-1) para que ignore el /0 del email, si no no funciona
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {

        strcpy(prof->user->dni, (const char *)sqlite3_column_text(res, 5));
        strcpy(prof->user->contrasenya, (const char *)sqlite3_column_text(res, 1));
        strcpy(prof->user->email, (const char *)sqlite3_column_text(res, 4));
        strcpy(prof->user->fechaNacimiento, (const char *)sqlite3_column_text(res, 3));
        strcpy(prof->user->nombreApellidos, (const char *)sqlite3_column_text(res, 2));
        strcpy(prof->idProfesional, (const char *)sqlite3_column_text(res, 0));
        prof->user->telefono = sqlite3_column_int(res, 6);
    }

    return prof;
    free(prof);
}

Cliente *getInfoCliente(char *dni)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;
    Cliente *cli;
    cli = (Cliente *)malloc(sizeof(Cliente));
    cli->user = (Usuario *)malloc(sizeof(Usuario));

    char *sql = "SELECT * FROM CLIENTE WHERE DNI = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, dni, strlen(dni), SQLITE_STATIC); //Le pasamos el (strlen(email)-1) para que ignore el /0 del email, si no no funciona
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {

        strcpy(cli->user->dni, (const char *)sqlite3_column_text(res, 0));
        strcpy(cli->user->contrasenya, (const char *)sqlite3_column_text(res, 1));
        strcpy(cli->user->nombreApellidos, (const char *)sqlite3_column_text(res, 2));
        cli->user->telefono = sqlite3_column_int(res, 3);
        strcpy(cli->user->email, (const char *)sqlite3_column_text(res, 4));
        strcpy(cli->domicilio, (const char *)sqlite3_column_text(res, 5));
        strcpy(cli->user->fechaNacimiento, (const char *)sqlite3_column_text(res, 6));
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
        strcpy((*(lista + i))->user->dni, (const char *)sqlite3_column_text(res, 0));
        strcpy((*(lista + i))->user->contrasenya, (const char *)sqlite3_column_text(res, 1));
        strcpy((*(lista + i))->user->nombreApellidos, (const char *)sqlite3_column_text(res, 2));
        (*(lista + i))->user->telefono = sqlite3_column_int(res, 3);
        strcpy((*(lista + i))->user->email, (const char *)sqlite3_column_text(res, 4));
        strcpy((*(lista + i))->domicilio, (const char *)sqlite3_column_text(res, 5));
        strcpy((*(lista + i))->user->fechaNacimiento, (const char *)sqlite3_column_text(res, 6));

        i++;
        step = sqlite3_step(res);
    }

    sqlite3_finalize(res);

    return lista; //El resto de punteros se liberan desde el menu, accediendo a ellos a traves del puntero que se crea ahi
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
        strcpy((listaCuentas + i)->iban, (const char *)sqlite3_column_text(res, 0));
        (listaCuentas + i)->saldo = sqlite3_column_double(res, 1);
        strcpy((listaCuentas + i)->fechaCreacion, (const char *)sqlite3_column_text(res, 2));
        strcpy((listaCuentas + i)->dniPropietario, (const char *)sqlite3_column_text(res, 3));

        step = sqlite3_step(res);
        i++;
    }

    return listaCuentas;
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
        strcpy((listaInversiones + i)->idCompania, (const char *)sqlite3_column_text(res, 1));
        (listaInversiones + i)->valorCompra = sqlite3_column_double(res, 2);
        (listaInversiones + i)->cantidad = sqlite3_column_double(res, 3);
        strcpy((listaInversiones + i)->fechaCompra, (const char *)sqlite3_column_text(res, 4));
        i++;
        step = sqlite3_step(res);
    }

    return listaInversiones;
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
        strcpy((listaPrestamos + i)->idProfesional, (const char *)sqlite3_column_text(res, 2));
        (listaPrestamos + i)->importe = sqlite3_column_double(res, 3);
        strcpy((listaPrestamos + i)->fechaEmision, (const char *)sqlite3_column_text(res, 4));
        sqlite3_column_text(res, 5) == NULL ? strcpy((listaPrestamos + i)->fechaDevol, "NULL") : strcpy((listaPrestamos + i)->fechaDevol, (const char *)sqlite3_column_text(res, 5));
        sqlite3_column_text(res, 6) == NULL ? strcpy((listaPrestamos + i)->fechaComp, "NULL") : strcpy((listaPrestamos + i)->fechaComp, (const char *)sqlite3_column_text(res, 6));
        (listaPrestamos + i)->tae = sqlite3_column_double(res, 7);

        i++;
        step = sqlite3_step(res);
    }

    return listaPrestamos;
}

Movimiento *getMovimientos(char *iban)
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
        sqlite3_bind_text(res, 1, iban, (strlen(iban)), SQLITE_STATIC);
        sqlite3_bind_text(res, 2, iban, (strlen(iban)), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, iban, (strlen(iban)), SQLITE_STATIC);
        sqlite3_bind_text(res1, 2, iban, (strlen(iban)), SQLITE_STATIC);
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
        strcpy((movimientos + i)->ibanOrigen, (const char *)sqlite3_column_text(res, 1));
        strcpy((movimientos + i)->ibanDestino, (const char *)sqlite3_column_text(res, 2));
        (movimientos + i)->importe = sqlite3_column_double(res, 3);
        strcpy((movimientos + i)->fecha, (const char *)sqlite3_column_text(res, 4));
        strcpy((movimientos + i)->concepto, (const char *)sqlite3_column_text(res, 5));
        i++;
        step = sqlite3_step(res);
    }

    return movimientos;
}

Prestamo *getSolicitudesPrestamo(Profesional *prof)
{
    int rc, rc1;
    char *err_msg = 0;
    sqlite3_stmt *res, *res1;

    char *sql = "SELECT * FROM PRESTAMO WHERE ID_PROF = ? AND ESTADO = 1";
    char *sql1 = "SELECT COUNT(*) FROM PRESTAMO WHERE ID_PROF = ? AND ESTADO = 1";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, prof->idProfesional, (strlen(prof->idProfesional)), SQLITE_STATIC);
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
        (listaPrestamosPendientes + i)->cli = malloc(sizeof(Cliente));
        (listaPrestamosPendientes + i)->cli->user = malloc(sizeof(Usuario));
        strcpy((listaPrestamosPendientes + i)->cli->user->dni, (const char *)sqlite3_column_text(res, 1));
        (listaPrestamosPendientes + i)->importe = sqlite3_column_double(res, 3);
        strcpy((listaPrestamosPendientes + i)->fechaSoli, (const char *)sqlite3_column_text(res, 4));
        i++;
        step = sqlite3_step(res);
    }

    return listaPrestamosPendientes;
}

int *getCountTipoPrestamo(char *dniCli)
{
    int rc1;
    int rc2;
    int rc3;
    char *err_msg = 0;
    sqlite3_stmt *res1, *res2, *res3;

    char *sql1 = "SELECT COUNT() FROM PRESTAMO WHERE DNI_CLI = ? AND ESTADO = 1";
    char *sql2 = "SELECT COUNT() FROM PRESTAMO WHERE DNI_CLI = ? AND ESTADO = 2";
    char *sql3 = "SELECT COUNT() FROM PRESTAMO WHERE DNI_CLI = ? AND ESTADO = 3";

    rc1 = sqlite3_prepare_v2(db, sql1, -1, &res1, 0);
    rc2 = sqlite3_prepare_v2(db, sql2, -1, &res2, 0);
    rc3 = sqlite3_prepare_v2(db, sql3, -1, &res3, 0);

    if (rc1 == SQLITE_OK && rc2 == SQLITE_OK && rc3 == SQLITE_OK)
    {
        sqlite3_bind_text(res1, 1, dniCli, (strlen(dniCli)), SQLITE_STATIC);
        sqlite3_bind_text(res2, 1, dniCli, (strlen(dniCli)), SQLITE_STATIC);
        sqlite3_bind_text(res3, 1, dniCli, (strlen(dniCli)), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step1 = sqlite3_step(res1);
    int step2 = sqlite3_step(res2);
    int step3 = sqlite3_step(res3);

    int *estados;
    estados = malloc(3 * sizeof(int));

    if (step1 == SQLITE_ROW && step2 == SQLITE_ROW && step3 == SQLITE_ROW)
    {
        *estados = sqlite3_column_int(res1, 0);
        *(estados + 1) = sqlite3_column_int(res2, 0);
        *(estados + 2) = sqlite3_column_int(res3, 0);
    }

    return estados;
}