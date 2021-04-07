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



float calcularInteres(Prestamo *pres, Inversion *inversiones, int numeroInversiones, Cuenta * cuentas, int numeroCuentas){
    float tin;
    float patrimonioClte = 0.0;
    for (int i = 0; i<numeroInversiones; i++){
        
     patrimonioClte = patrimonioClte + ((inversiones+i)->cantidad * (inversiones+i)->valorCompra);
    }
    for(int j = 0; j<numeroCuentas; j++){
        patrimonioClte = patrimonioClte + (cuentas+j)->saldo;
    }

    if(patrimonioClte/pres->importe >= 1.00){

        if(patrimonioClte/pres->importe == 1){
            tin;
        
        }else if(patrimonioClte/pres->importe <= 1.5){

        }else if(patrimonioClte/pres->importe >1.5){

    }
        
    }  

    float a = 0.00;
    
    return a;
    }