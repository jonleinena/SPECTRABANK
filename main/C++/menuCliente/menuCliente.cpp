#include <stdlib.h>
#include <iostream>
#include "menuCliente.h"
#include "../utils/inversiones/inversiones.h"

extern "C"
{
#include "../../../lib/sqlite3/sqlite3.h"
#include "../../../utils/colors.h"
#include "../../../db/dbConnection.h"
#include "../../../db/C/getData.h"
#include "../../C/utils/structures.h"
}
#include "../utils/containers/containers.h"
#include <iomanip>

using namespace std;
using std::setw;
using namespace containers;

void menuCliente(ClienteCpp &cli)
{
    /* if (startConn() == 0)
    {
        return 0;
    } */
    char *input;
    input = new char;

    cout << "\e[1;1H\e[2J" << endl; //limpiar terminal

    do
    {
        cout << FGREN "**********************Bienvenido " << cli.getNombre() << "**********************" << endl;
        cout << (FCYAN
                 "1.- Ver listado de cuentas\n"
                 "2.- Gestionar inversiones\n"
                 "3.- Ver datos de mi cuenta\n"
                 "q.- Cerrar\n\n"
                 "Inserte seleccion: ");

        cin >> input;

        switch (*input)
        {
        case '1':
            cout << ("\e[1;1H\e[2J") << endl;
            mostrarCuentas(cli);
            cout << endl;
            break;
        case '2':
            cout << ("\e[1;1H\e[2J") << endl;
            // menuInversiones(cli);
            cout << endl;
            break;
        case '3':
            verDatosCliente(cli);
            break;
        case 'q':
            cout << (FRED "\nSaliendo.\n") << endl;
            //revisar los free/delete
            /**
            for (int i = 0; i < numFilas; i++)
            {
                free((*(lista + i))->user);
                free(*(lista + i));
            }
            free(lista);
            free(input);
            */

            break;
        default:
            cout << (FRED "\nIntroduce una opcion valida, por favor.\n") << endl;
            break;
        }
    } while (*input != 'q');
}

void mostrarCuentas(ClienteCpp &cli)
{
    char *input;
    input = new char;
    int *index;
    index = new int;

    cout << cli.getNombre() << endl;

    containers::CuentaCpp *listaCuentas;
    listaCuentas = new CuentaCpp[10];
    for (int i = 0; i < numFilas; i++)
    {
        // el &cli.getDni()[0] es para pasar el puntero de la pos. 0 del dni al metodo. el c_str() davuelve un const char* y da errores

        Cuenta *cuentasCliente = (Cuenta *)malloc(30 * sizeof(Cuenta));
        cuentasCliente = getCuentasCliente(&cli.getDni()[0]);
        //inicializamos el array de listaCuentas con cuentas SIN movimientos porque todavía no tenemos estos
        listaCuentas[i].setDni(string((cuentasCliente + i)->dniPropietario));
        listaCuentas[i].setFecCreacion(string((cuentasCliente + i)->fechaCreacion));
        listaCuentas[i].setIban(string((cuentasCliente + i)->iban));
        listaCuentas[i].setSaldo((cuentasCliente + i)->saldo);
    }

    //PROBLEMAS CON REALLOC
    //listaCuentas = (CuentaCpp *)realloc(listaCuentas, numFilas * sizeof(CuentaCpp)); // resize the memory block pointed to by listaCuentas

    cout << "\n************ CUENTAS DE" << cli.getNombre() << "**************"
         << endl;
    printf("%-10s%-30s%-15s%-25s%-10s\n", "INDICE", "IBAN", "SALDO", "FECHA CREACION", "DNI");
    for (int i = 0; i < numFilas; i++)
    {

        //printf("%-10d%-30s%-15.2f%-25s%-10s\n", i, cuentas_ptr[i].getIban(), cuentas_ptr[i].getSaldo(), cuentas_ptr[i].getFecCreacion(), cuentas_ptr[i].getDni());
        //el printf da errores por los string
        cout << i << setw(30) << listaCuentas[i].getIban() << setw(15) << listaCuentas[i].getSaldo() << setw(25) << listaCuentas[i].getFecCreacion() << setw(10) << listaCuentas[i].getDni() << endl;
    }

    do
    {
        printf(FCYAN
               "\n1.- Visualizar movimientos de una cuenta\n"
               "q.- Atras\n");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);
        switch (*input)
        {
        case '1':
            printf("INTRODUZCA EL INDICE DE LA CUENTA\n");
            fgets(input, 4, stdin);
            sscanf(input, "%i", index);
            fflush(stdin);
            if (*index < 0 || *index > numFilas)
            {
                printf(FRED "Introduce un indice valido\n" FCYAN);
            }
            else
            {
                //verMovimientos((listaCuentas + *index));
            }
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n" FCYAN);
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n" FCYAN);
            break;
        }

    } while (*input != 'q');

    free(input);
    free(index);
}

void verDatosCliente(ClienteCpp &cli)
{
    printf("\e[1;1H\e[2J");
    char *input = new char;

    do
    {
        printf(FCYAN "%-15s%-25s%-25s%-15s%-25s%-15s\n", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
        printf("%-15s%-10s%-25s%-25s%-15i%-25s\n", cli.getDni(), cli.getNombre(), cli.getFecNac(), cli.getDomicilio(), cli.getTelf(), cli.getEmail(), cli.getDomicilio());
        printf("1.-Modificar datos\nq.-Salir\n");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);
        switch (*input)
        {
        case '1':
            // modificarDatos(prof);
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }
    } while (*input != 'q');
    free(input);
}