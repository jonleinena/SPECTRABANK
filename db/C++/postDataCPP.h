#include "../../main/C++/utils/containers/containers.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../dbConnection.h"
#include "../../main/C++/utils/inversiones/stockAPI.h"

#ifndef postDataCPP
#define postDataCPP

using namespace containers;
using namespace stockAPI;

int modificarCliente(char *selec, ClienteCpp cli, char *input);
int comprarAcciones(Symbol &symbol, int amount, ClienteCpp &cli);
int venderAcciones(int cantidad, ClienteCpp &cli, char *idComp);

#endif