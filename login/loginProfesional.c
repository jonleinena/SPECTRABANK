#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "loginProfesional.h"
#include "../db/getData.h"
#include "../db/postData.h"

int main(void)
{
    printf("**********************Bienvenido**********************\n");
    printf("INICIAR SESION\n");

    char *email;
    email = malloc(30 * sizeof(char));
    char *contrasenya;
    contrasenya = malloc(18 * sizeof(char));

    printf("Introduce el correo electronico: ");
    fgets(email, 30, stdin);
    sscanf(email, "%c");
    fflush(stdin);
    //printf("email: %s, tamanyo string (bytes): %i, len string: %i\n", email, sizeof(email), strlen(email));

    printf("Introduce contrasenya: ");
    fgets(contrasenya, 18, stdin);
    sscanf(contrasenya, "%c");

    int resultLogin;
    resultLogin = getLoginProfesional(email, contrasenya);

    printf("El login es: %i", resultLogin);
    return 0;
}