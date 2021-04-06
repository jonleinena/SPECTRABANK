#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../db/getData.h"
#include "../db/postData.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../db/dbConnection.h"
#include "../utils/colors.h"
#include "../structures/structures.h"

void imprimirListaClientes(Cliente **lista, int *numElems);
void opcionesCltes(Cliente **lista);

void menuProfesional(Profesional *prof)
{

    Cliente **lista;
    lista = (Cliente **)malloc(50 * sizeof(Cliente *));
    int numFilas = 1;

    system("cls"); //limpiar terminal

    printf("**********************Bienvenido, %s**********************\n",
           prof->user->nombreApellidos);

    char *input;
    input = malloc(sizeof(char));
    do
    {

        printf("%s%s"
               "1.- Ver listado de clientes\n"
               "2.- Solicitudes de prestamo\n"
               "3.- Ver datos de mi cuenta\n"
               "q.- Cerrar\n\n"
               "Inserte seleccion: ",
               FCYAN, BBLCK);

        fgets(input, 2, stdin);
        sscanf(input, "%c");
        fflush(stdin);

        switch (*input)
        {
        case '1':
            lista = getListaClientes((prof->idProfesional), &numFilas, db);
            realloc(lista, numFilas);
            imprimirListaClientes(lista, &numFilas);

            opcionesCltes(lista);
            printf("\n");
            break;
        case '2':
            break;
        case '3':
            break;
        case 'q':
            printf("%s\nSaliendo.\n\n", FRED);
            for (int i = 0; i < *(&numFilas); i++)
            {
                free((*(lista + i))->user);
                free(*(lista + i));
            }
            free(lista);
            break;
        default:
            printf("%s\nIntroduce una opcion valida, por favor.\n\n", FRED);
            break;
        }
    } while (*input != 'q');
    free(input);
    input = NULL;
}

void imprimirListaClientes(Cliente **lista, int *numElems)
{
    printf("%-10s%-10s%-25s%-25s%-15s%-25s%-15s\n", "NUMERO", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
    for (int i = 0; i < *numElems; i++)
    {
        printf("%-10i%-10s%-25s%-25s%-15i%-25s%-15s\n", i, ((*(lista + i))->user->dni), ((*(lista + i))->user->nombreApellidos), ((*(lista + i))->user->fechaNacimiento), ((*(lista + i))->user->telefono), ((*(lista + i))->user->email), ((*(lista + i))->domicilio));
    }
}

void opcionesCltes(Cliente **lista)
{
    char *selec, *clte;
    int index, numFilas, numFilas2 = 0;
    selec = malloc(sizeof(char));
    clte = malloc(sizeof(char));
    do
    {
        printf("\n1.- Visualizar datos de cliente\nq.- Atras\n");
        fgets(selec, 2, stdin);
        sscanf(selec, "%c");
        fflush(stdin);
        switch (*selec)
        {
        case '1':
            printf("INTRODUZCA EL INDICE DEL CLIENTE (COLUMNA NUMERO)\n");
            fgets(clte, 2, stdin);
            sscanf(clte, "%i", &index);
            fflush(stdin);
            printf("%-10s%-25s%-25s%-15s%-25s%-15s\n", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
            printf("%-10s%-25s%-25s%-15i%-25s%-15s\n", ((*(lista + index))->user->dni), ((*(lista + index))->user->nombreApellidos), ((*(lista + index))->user->fechaNacimiento), ((*(lista + index))->user->telefono), ((*(lista + index))->user->email), ((*(lista + index))->domicilio));

            Cuenta *listaCuentas;
            listaCuentas = malloc(30 * sizeof(Cuenta));
            listaCuentas = getCuentasCliente(((*(lista + index))->user->dni), &numFilas, db);
            realloc(listaCuentas, numFilas); // resize the memory block pointed to by listaCuentas
            printf("\n************ CUENTAS DE %s**************\n", ((*(lista + index))->user->nombreApellidos));
            printf("%-25s%-15s%-25s%-10s\n", "IBAN", "SALDO", "FECHA CREACION", "DNI");
            for (int i = 0; i < numFilas; i++)
            {
                printf("%-25s%-15.2f%-25s%-10s\n", (listaCuentas + i)->iban, (listaCuentas + i)->saldo, (listaCuentas + i)->fechaCreacion, (listaCuentas + i)->dniPropietario);
            }


            Inversion *listaInversiones;
            listaInversiones = malloc(30 * sizeof(Inversion));
            listaInversiones = getInversionClite(*(lista + index), &numFilas2, db);
            realloc(listaInversiones, numFilas2);
            printf("\n************ INVERSIONES DE %s**************\n", ((*(lista + index))->user->nombreApellidos));
            printf("%-10s%-10s%-20s%-25s%-10s\n", "COMPANIA", "CANTIDAD", "VALOR DE COMPRA", "FECHA DE COMPRA", "POSICION TOTAL");
            for (int i = 0; i < numFilas2; i++)
            {
                printf("%-10s%-10d%-20.2f%-25s%-10.2f\n", (listaInversiones + i)->idCompania, (listaInversiones + i)->cantidad, (listaInversiones + i)->valorCompra, (listaInversiones + i)->fechaCompra,(listaInversiones + i)->cantidad * (listaInversiones + i)->valorCompra);
            }
            

            break;

        case 'q':
            printf("%s\nSaliendo.\n\n", FRED);
            break;
        default:
            printf("%s\nIntroduce una opcion valida, por favor.\n\n", FRED);
            break;
        }
    } while (*selec != 'q');
    free(selec);
    selec = NULL;
}
