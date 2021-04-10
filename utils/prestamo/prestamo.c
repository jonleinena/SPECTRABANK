#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prestamo.h"
#include "../../db/getData.h"
#include "../db/postData.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../db/dbConnection.h"
#include "../utils/colors.h"
#include "../structures.h"



float calcularInteres(Prestamo *pres, Inversion *inversiones, int numeroInversiones, Cuenta *cuentas, int numeroCuentas, int *idPrestamo){
    float tin;
    float patrimonioClte = 0.0;
    for (int i = 0; i<numeroInversiones; i++){
        
     patrimonioClte = patrimonioClte + ((inversiones+i)->cantidad * (inversiones+i)->valorCompra);
    }
    for(int j = 0; j<numeroCuentas; j++){
        patrimonioClte = patrimonioClte + (cuentas+j)->saldo;
    }

    //1º Apartado de la Lógica

    if(patrimonioClte/pres->importe > 1.00){

        if(patrimonioClte/pres->importe <= 1.67){
            tin = 0.07;
        
        }else if(patrimonioClte/pres->importe <= 3.33){
            tin = 0.04;

        }else if(patrimonioClte/pres->importe >3.33){
            tin = 0.03;

    }else{
        //Inserta en la base de datos en la tabla del Prestamo en el apartado idprestamo el prestamo como "denegado"
        modificarPrestamoADenegado(*idPrestamo);
    }
        
    }



    float a = 0.00;
    
    return a;
    }