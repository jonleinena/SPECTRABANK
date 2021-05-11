#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prestamo.h"
#include "../../../../db/C/getData.h"
#include "../../../../db/C/postData.h"
#include "../../../../lib/sqlite3/sqlite3.h"
#include "../../../../db/dbConnection.h"
#include "../../../../utils/colors.h"
#include "../structures.h"

float calcularInteres(Prestamo *pres)
{
    Inversion *inversiones;
    Cuenta *cuentas;

    inversiones = (Inversion *)malloc(30 * sizeof(Inversion));
    cuentas = (Cuenta *)malloc(10 * sizeof(Cuenta));

    inversiones = getInversionClite(pres->cli->user->dni);
    inversiones = realloc(inversiones, numFilas * sizeof(Inversion));

    int numeroInversiones = numFilas;

    cuentas = getCuentasCliente(pres->cli->user->dni);
    cuentas = realloc(cuentas, numFilas * sizeof(Cuenta));

    int numeroCuentas = numFilas;

    float tae;
    float patrimonioClte = 0.0;
    int *prestamosEstados;
    prestamosEstados = malloc(3 * sizeof(int));
    prestamosEstados = getCountTipoPrestamo(cuentas->dniPropietario);

    for (int i = 0; i < numeroInversiones; i++)
    {
        patrimonioClte = patrimonioClte + ((inversiones + i)->cantidad * (inversiones + i)->valorCompra);
    }
    for (int j = 0; j < numeroCuentas; j++)
    {
        patrimonioClte = patrimonioClte + (cuentas + j)->saldo;
    }

    //1º Apartado de la Lógica

    if (patrimonioClte / pres->importe > 1.00)
    {

        if (patrimonioClte / pres->importe <= 1.67)
        {
            tae = 0.07;
        }
        else if (patrimonioClte / pres->importe <= 3.33)
        {
            tae = 0.04;
        }
        else if (patrimonioClte / pres->importe > 3.33)
        {
            tae = 0.03;
        }
        else
        {
            //Inserta en la base de datos en la tabla del Prestamo en el apartado idprestamo el prestamo como "denegado"
            modificarPrestamoADenegado(&(pres->idPres));
        }
    }

    //2º Apartado de la Lógica
    //Numero de prestamos pendientes
    switch (*(prestamosEstados))
    {
    case 1:
        tae = tae + (tae * 0.35);
        break;
    case 2:
        tae = tae + (tae * 0.70);
        break;
    default:
        modificarPrestamoADenegado(&(pres->idPres));
        break;
    }

    if (*(prestamosEstados + 1) > 3 && *(prestamosEstados + 1) <= 6)
    {
        tae = tae - (tae * 0.05);
    }
    else if (*(prestamosEstados + 1) > 6 && *(prestamosEstados + 1) <= 10)
    {
        tae = tae - (tae * 0.08);
    }
    else if (*(prestamosEstados + 1) > 10)
    {
        tae = tae - (tae * 0.1);
    }
    else if (*(prestamosEstados + 2) > 0)
    {
        modificarPrestamoADenegado(&(pres->idPres));
    }

    free(prestamosEstados);

    return tae;
}