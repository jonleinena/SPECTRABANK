#include "../structures/structures.h"

#ifndef _menu_profesional_h
#define _menu_profesional_h
void imprimirListaClientes(Cliente **lista, int *numElems);
void menuProfesional(Profesional *p);
void opcionesCltes(Cliente **lista);
void verMovimientos(Cuenta *cue, int *numFilas, int *indice);

#endif