#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../login/loginProfesional.h"
#include "../login/loginCliente.h"
#include "../db/getData.h"
#include "../db/postData.h"
#include "../db/dbConnection.h"
#include "../utils/colors.h"

int main(void)
{
    if (startConn(db))
    {
        return 0;
    }

    system("cls"); //Esta limpieza se ejecuta para el buen funcionamiento de la apariencia de la consola
    char *input;
    input = malloc(sizeof(char));

    printf("%s%s"
           "                                                            \n"
           "                                                            \n"
           "                  BIENVENIDO A SPECTRABANK                  \n"
           "                                                            \n"
           "                                                            \n",
           FBLCK, BCYAN);
    do
    {
        printf("%s%s"
               "1.- Inicio de sesion como profesional\n"
               "2.- Inicio de sesion como cliente\n"
               "q.- Cerrar\n\n"
               "Inserte selecci%cn: ",
               FCYAN, BBLCK, 162);

        fgets(input, 2, stdin);
        sscanf(input, "%c");
        fflush(stdin);

        switch (*input)
        {
        case '1':
            system("cls"); //Limpia el terminal
            loginProfesional();
            break;
        case '2':
            system("cls");
            loginCliente();
            break;
        case 'q':
            printf("%s\nSaliendo.\n\n", FRED);
            break;
        default:
            printf("%s\nIntroduce una opcion valida, por favor.\n\n", FRED);
            break;
        }
    } while (*input != 'q');

    printf(RESET); //Resetea los atributos de fuente cuando salimos del programa
    sqlite3_close(db);
    free(input);
    input = NULL;

    return 0;
}