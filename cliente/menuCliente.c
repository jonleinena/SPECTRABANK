#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../db/getData.h"
#include "../db/postData.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../db/dbConnection.h"
#include "../utils/colors.h"
#include "../structures/structures.h"

void menuCliente(Cliente *cli)
{

    Cuenta *listaCuentas;
    listaCuentas = malloc(30 * sizeof(Cuenta));
    int numFilas = 1;

    system("cls"); //limpiar terminal

    printf("**********************Bienvenido, %s**********************\n",
           cli->user->nombreApellidos);

    char *input;
    input = malloc(sizeof(char));
    do
    {
        printf("%s%s"
               "1.- Ver mis cuentas\n"
               "q.- Cerrar\n\n"
               "Inserte seleccion: ",
               FCYAN, BBLCK);

        fgets(input, 2, stdin);
        sscanf(input, "%c");
        fflush(stdin);

        switch (*input)
        {
        case '1':

            listaCuentas = getCuentasCliente(cli->user->dni, &numFilas, db);
            printf("\n************ CUENTAS DE %s**************\n", (cli->user->nombreApellidos));
            printf("IBAN \t \t \t SALDO \t\t FECHA DE CREACION \t\t TITULAR \n");
            for (int i = 0; i < numFilas; i++)
            {
                printf("%s \t %f \t %s \t\t %s \n", (listaCuentas + i)->iban, (listaCuentas + i)->saldo, (listaCuentas + i)->fechaCreacion, (listaCuentas + i)->dniPropietario);
            }

            printf("\n");
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