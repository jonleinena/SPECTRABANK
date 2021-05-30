#include <string.h>
#include <string>
#include "postDataCPP.h"
#include "../../main/C++/utils/containers/containers.h"
#include "../../main/C++/utils/inversiones/stockAPI.h"
#include <iostream>

using namespace containers;
using namespace stockAPI;
using namespace std;

int modificarCliente(char *selec, ClienteCpp cli, char *input)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    const char *sql;
    const char *sql1 = "UPDATE CLIENTE SET NUM_TEL = ? WHERE DNI = ?";
    const char *sql2 = "UPDATE CLIENTE SET CORREO = ? WHERE DNI = ?";
    const char *sql3 = "UPDATE CLIENTE SET DOMICILIO = ? WHERE DNI = ?";
    const char *sql4 = "UPDATE CLIENTE SET CONTRASENYA = ? WHERE DNI = ?";

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
    case '4':
        sql = sql4;
        break;
    default:
        break;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, input, (strlen(input)), SQLITE_STATIC);
        sqlite3_bind_text(res, 2, cli.getDni().c_str(), (strlen(cli.getDni().c_str())), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    sqlite3_finalize(res);

    return step;
}

int comprarAcciones(Symbol &symbol, int amount, ClienteCpp &cli)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    const char *sql = "INSERT INTO ACC_CLI (DNI, ID_COMPAÑIA, VALOR_COMPRA, CANTIDAD) VALUES (?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, cli.getDni().c_str(), (strlen(cli.getDni().c_str())), SQLITE_STATIC);
        sqlite3_bind_text(res, 2, symbol.getSymbol(), strlen(symbol.getSymbol()), SQLITE_STATIC);
        sqlite3_bind_double(res, 3, symbol.getCurrentValue());
        sqlite3_bind_int(res, 4, amount);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    sqlite3_finalize(res);

    return step;
}

int venderAcciones(int cantidad, ClienteCpp &cli, char *idComp)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    const char *sql = "UPDATE ACC_CLI SET CANTIDAD = ? WHERE DNI = ? AND ID_COMPAÑIA = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_int(res, 1, cantidad);
        sqlite3_bind_text(res, 2, cli.getDni().c_str(), (strlen(cli.getDni().c_str())), SQLITE_STATIC);
        sqlite3_bind_text(res, 3, idComp, (strlen(idComp)), SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    sqlite3_finalize(res);

    return step;
}