#include "../utils/structures.h"
#include "../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"
#ifndef getData
#define getData

int getLogin(char *email, char *contrasenya);
Profesional *getInfoProfesional(char *email);
Cliente *getInfoCliente(char *email);
Cliente **getListaClientes(char *idProf, int *numFilas);
Cuenta *getCuentasCliente(char *dniCliente, int *numFilas);
Inversion *getInversionClite(Cliente *cli, int *numFilas);
Prestamo *getPrestamos(Cliente *cli, int *numFilas);
Movimiento *getMovimientos(Cuenta *cue, int *numFilas);
Prestamo *getSolicitudesPrestamo(Profesional *prof, int *numFilas);

#endif