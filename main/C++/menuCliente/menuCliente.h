#include "../utils/containers/containers.h"

#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

using namespace containers;

void menuCliente(ClienteCpp &cli);
void mostrarCuentas(ClienteCpp &cli);
void verDatosCliente(ClienteCpp &cli);
void cargarMovimientos(CuentaCpp &c);
void verMovimientos(CuentaCpp &c);
void modificarDatosCliente(ClienteCpp &c);

#endif