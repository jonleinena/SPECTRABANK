#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../login/loginProfesional.h"
#include "../db/getData.h"
#include "../db/postData.h"

int main(void)
{
    char *input;
    input = malloc(sizeof(char));
    do
    {
        printf("------------------------------------------------------------\n------------------------------------------------------------\n------------------ BIENVENIDO A SPECTRABANK ----------------\n------------------------------------------------------------\n");
        printf("1.- Inicio de sesion como profesional\n2.- Inicio de sesion como cliente(No disponible)\n q.-Cerrar\n\n");

        fgets(input, 2, stdin);
        sscanf(input, "%c");
        fflush(stdin);

        switch (*input)
        {
        case '1':
            loginProfesional();
            break;
        default:
            printf("\nIntroduce una opcion valida, por favor.\n\n");

            break;
        }
    } while (*input != 'q');

    return 0;
}