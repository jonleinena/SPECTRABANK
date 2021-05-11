#include <stdio.h>
#include <string.h>
#include "fechas.h"

void formatDate(char *stringFecha, int *ano, int *mes, int *dia, int *hora, int *min, int *seg)
{
    sscanf(stringFecha, "%d-%d-%d %d:%d:%d", ano, mes, dia, hora, min, seg);
}