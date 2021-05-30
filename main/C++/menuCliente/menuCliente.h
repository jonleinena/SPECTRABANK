#include "../utils/containers/containers.h"

#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

using namespace containers;

void menuCliente(ClienteCpp &cli);
void menuCuentas(ClienteCpp &cli);
void menuDatosCliente(ClienteCpp &cli);
void mostrarCuentas(ClienteCpp &cli);
void cargarMovimientos(CuentaCpp &c);
void mostrarMovimientos(CuentaCpp &c);
void mostrarDatosCliente(ClienteCpp &cli);
void modificarDatosCliente(ClienteCpp &c);

#endif