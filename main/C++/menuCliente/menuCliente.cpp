#include <stdlib.h>
#include <iostream>
#include "menuCliente.h"
#include "../utils/inversiones/inversiones.h"
#include "../../../db/dbConnection.h"
#include "../../../utils/colors.h"

using namespace std;
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
        cout << (FGREN "**********************Bienvenido, %s**********************", cli.getNombre()) << endl;
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
            mostrarCuentas(&cli);
            cout << endl;
            break;
        case '2':
            cout << ("\e[1;1H\e[2J") << endl;
            menuInversiones(&cli);
            cout << endl;
            break;
        case '3':
            verDatosProfesional(prof);
            break;
        case 'q':
            cout << (FRED "\nSaliendo.\n") << endl;
            //revisar los free/delete
            for (int i = 0; i < numFilas; i++)
            {
                free((*(lista + i))->user);
                free(*(lista + i));
            }
            free(lista);
            free(input);
            break;
        default:
            cout << (FRED "\nIntroduce una opcion valida, por favor.\n") << endl;
            break;
        }
    } while (*input != 'q');
}

void mostrarCuentas(Cliente &cli)
{
    char *input;
    input = malloc(sizeof(char));
    int *index;
    index = malloc(sizeof(int));

    containers::Cuenta *listaCuentas;
    listaCuentas = malloc(30 * sizeof(containers::Cuenta));
    listaCuentas = getCuentasCliente((cli.getDni).c_str());
    listaCuentas = realloc(listaCuentas, numFilas * sizeof(containers::Cuenta)); // resize the memory block pointed to by listaCuentas

    printf("\n************ CUENTAS DE %s**************\n", cli.getNombre()); //Transformar Cli a Clase
    printf("%-10s%-30s%-15s%-25s%-10s\n", "INDICE", "IBAN", "SALDO", "FECHA CREACION", "DNI");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-10d%-30s%-15.2f%-25s%-10s\n", i, (listaCuentas + i)->iban, (listaCuentas + i)->saldo, (listaCuentas + i)->fechaCreacion, (listaCuentas + i)->dniPropietario);
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
                verMovimientos((listaCuentas + *index));
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