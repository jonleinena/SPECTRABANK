#include <string.h>
#include <string>
#include "postDataCPP.h"

int modificarCliente(char *selec, ClienteCpp cli, char *input)
{
    int rc;
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql;
    char *sql1 = "UPDATE CLIENTE SET NUM_TEL = ? WHERE DNI = ?";
    char *sql2 = "UPDATE CLIENTE SET CORREO = ? WHERE DNI = ?";
    char *sql3 = "UPDATE CLIENTE SET DOMICILIO = ? WHERE DNI = ?";
    char *sql4 = "UPDATE CLIENTE SET CONTRASENYA = ? WHERE DNI = ?";

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