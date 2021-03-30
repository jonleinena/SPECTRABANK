#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "loginProfesional.h"
#include "../db/getData.h"
#include "../db/postData.h"

int main(void)
{
    int resultLogin = 0;
    char *email;
    email = malloc(30 * sizeof(char));
    char *contrasenya;
    contrasenya = malloc(18 * sizeof(char));
    printf("**********************Bienvenido**********************\n");
    printf("INICIAR SESION\n");
    do
    {
        printf("Introduce el correo electronico: ");
        fgets(email, 30, stdin);
        sscanf(email, "%c");
        fflush(stdin);

        printf("Introduce contrasenya: ");
        fgets(contrasenya, 18, stdin);
        sscanf(contrasenya, "%c");
        *(contrasenya + strlen(contrasenya) - 1) = '\0'; //para quitar el salto de linea que añade sscanf

        resultLogin = getLoginProfesional(email, contrasenya);

        if (resultLogin == 0)
        {
            printf("INICIO DE SESION CORRECTO\n");
        }
        else
            printf("Error en el inicio de sesion\n");
    } while (resultLogin != 0);

    free(email);
    email = NULL;
    free(contrasenya);
    contrasenya = NULL;
    return 0;
}