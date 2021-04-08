#include "../../utils/structures.h"

#ifndef _menu_profesional_h
#define _menu_profesional_h

void imprimirListaClientes(Cliente **lista, int *numElems);
void menuProfesional(Profesional *p);
void opcionesCltes(Cliente *cli);
void mostrarCuentas(Cliente *cliente);
void mostrarInversiones(Cliente *cliente);
void mostrarPrestamos(Cliente *cliente);
void verMovimientos(Cuenta *cue, int *numFilas);
void verDatosProfesional(Profesional *prof);
void modificarDatos(Profesional *prof);

#endif