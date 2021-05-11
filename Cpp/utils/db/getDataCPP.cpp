#include "getDataCPP.h"
#include <string.h>
#include <string>
#include "../../../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"
#include "../../containers/containers.h"

using namespace std;

containers::Inversiones *getInversiones(string dni)
{
    sqlite3_stmt *res, *res1;
    char *SQL = "SELECT * FROM ACC_CLI WHERE DNI = ?";
    char *SQL1 = "SELECT * FROM ACC_CLI WHERE DNI = ?";

    int rc = sqlite3_prepare_v2(db, SQL, -1, &res, 0);
    int rc1 = sqlite3_prepare_v2(db, SQL1, -1, &res1, 0);

    if (rc == SQLITE_OK && rc1 == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, dni.c_str(), dni.length(), SQLITE_STATIC);
        sqlite3_bind_text(res1, 1, dni.c_str(), dni.length(), SQLITE_STATIC);
    }

    sqlite3_step(res1);
    int numFilas = sqlite3_column_int(res1, 0);

    containers::Inversiones *inversiones = new containers::Inversiones(numFilas);

    int step;
    int i = 0;
    while ((step = sqlite3_step(res)) == SQLITE_ROW)
    {
        inversiones->setInversion(i, new containers::Inversion(strdup((const char *)sqlite3_column_text(res, 1)), sqlite3_column_double(res, 2), sqlite3_column_double(res, 3), strdup((const char *)sqlite3_column_text(res, 4))));
        i++;
    }

    return inversiones;
}