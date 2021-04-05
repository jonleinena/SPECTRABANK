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
    printf("NUMERO \tDNI \t NOMBRE \t DOMICILIO \n");

    for (int i = 0; i < *numElems; i++)
    {
        printf("%i\t %s \t %s \t %s\n", i, ((*(lista + i))->user->dni), ((*(lista + i))->user->nombreApellidos), ((*(lista + i))->domicilio));
    }
}

void opcionesCltes(Cliente **lista)
{
    char *selec, *clte;
    int index, numFilas = 0;
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
            printf("DNI \t NOMBRE Y APELLIDOS \t FECHA DE NACIMIENTO \t TELEFONO \t CORREO ELECTRONICO \t DOMICILIO \n");
            printf("%s \t %s \t\t\t %s \t\t", ((*(lista + index))->user->dni), ((*(lista + index))->user->nombreApellidos), ((*(lista + index))->user->fechaNacimiento));
            printf(" %i \t\t %s \t\t %s \n", ((*(lista + index))->user->telefono), ((*(lista + index))->user->email), ((*(lista + index))->domicilio));

            Cuenta *listaCuentas;
            listaCuentas = malloc(30 * sizeof(Cuenta));
            listaCuentas = getCuentasCliente(((*(lista + index))->user->dni), &numFilas, db);
            printf("\n************ CUENTAS DE %s**************\n", ((*(lista + index))->user->nombreApellidos));
            printf("IBAN \t \t \t SALDO \t\t FECHA DE CREACION \t\t TITULAR \n");
            for (int i = 0; i < numFilas; i++)
            {
                printf("%s \t %f \t %s \t\t %s \n", (listaCuentas + i)->iban, (listaCuentas + i)->saldo, (listaCuentas + i)->fechaCreacion, (listaCuentas + i)->dniPropietario);
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
