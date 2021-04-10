#include "../../utils/structures.h"

#ifndef _menu_profesional_h
#define _menu_profesional_h

void imprimirListaClientes(Cliente **lista);
void menuProfesional(Profesional *p);
void opcionesCltes(Cliente *cli);
void mostrarCuentas(Cliente *cliente);
void mostrarInversiones(Cliente *cliente);
void mostrarPrestamos(Cliente *cliente);
void verMovimientos(Cuenta *cue);
void verSolicitudesPrestamo(Profesional *prof);
void verDatosProfesional(Profesional *prof);
void modificarDatos(Profesional *prof);

#endif