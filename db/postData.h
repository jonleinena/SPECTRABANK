
#include "../utils/structures.h"
#include "../lib/sqlite3/sqlite3.h"
#include "dbConnection.h"

#ifndef postData
#define postData

int modificarProfesional(char *selec, Profesional *prof, char *input);

#endif