#include "../../main/C++/utils/containers/containers.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../dbConnection.h"

#ifndef postDataCPP
#define postDataCPP

using namespace containers;

int modificarCliente(char *selec, ClienteCpp cli, char *input);

#endif