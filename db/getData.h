#include "../structures/structures.h"
#include "../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"
#ifndef getData
#define getData

int startConn();

int getLoginProfesional(char *email, char *contrasenya, sqlite3 *db);
Profesional *getInfoProfesional(char *email, sqlite3 *db);
Cliente **getListaClientes(char *idProf, int *numFilas, sqlite3 *db);
Cuenta *getCuentasCliente(char *dniCliente, int *numFilas, sqlite3 *db);

#endif