#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../db/getData.h"
#include "../db/postData.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../db/dbConnection.h"
#include "../utils/colors.h"
#include "../structures/structures.h"

void imprimirListaClientes(Cliente **lista, int numElems);

void menuProfesional(Profesional *prof)
{

    Cliente **lista;
    lista = (Cliente **)malloc(50 * sizeof(Cliente *));

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
               "Inserte selecciocn: ",
               FCYAN, BBLCK);

        fgets(input, 2, stdin);
        sscanf(input, "%c");
        fflush(stdin);

        switch (*input)
        {
        case '1':

            lista = getListaClientes((prof->idProfesional), db);
            imprimirListaClientes(lista, 3);
            break;
        case '2':
            break;
        case '3':
            break;
        case 'q':
            printf("%s\nSaliendo.\n\n", FRED);
            break;
        default:
            printf("%s\nIntroduce una opcion valida, por favor.\n\n", FRED);
            break;
        }
    } while (*input != 'q');
    free(input);
    input = NULL;
}

void imprimirListaClientes(Cliente **lista, int numElems)
{
    printf("DNI \t NOMBRE \t DOMICILIO \n");

    for (int i = 0; i < numElems; i++)
    {
        printf("%s \t", ((*(lista + i))->user->dni));
        printf("%s \t", ((*(lista + i))->user->nombreApellidos));
        printf("%s \n", ((*(lista + i))->domicilio));
    }
}
