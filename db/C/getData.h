#include "../../main/C/utils/structures.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../dbConnection.h"
#ifndef getData
#define getData

extern int numFilas;

int getLogin(char *email, char *contrasenya, int userType);
Profesional *getInfoProfesional(char *email);
Cliente *getInfoCliente(char *email);
Cliente **getListaClientes(char *idProf);
Cuenta *getCuentasCliente(char *dniCliente);
Inversion *getInversionClite(char *dniCli);
Prestamo *getPrestamos(char *dniCli);
Movimiento *getMovimientos(char *iban);
Prestamo *getSolicitudesPrestamo(Profesional *prof);
int *getCountTipoPrestamo(char *dniCli);
#endif