#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../db/getData.h"
#include "../db/postData.h"


int main(void){
    printf("**********************Bienvenido**********************\n");
    printf("INICIAR SESION\n");

    char *email;
    email = malloc(30*sizeof(char));
    char *contrasenya;
    contrasenya = malloc(18*sizeof(char));


    printf("Introduce el correo electronico: ");
    fgets(email, 30, stdin);
    sscanf(email, "%c");
    fflush(stdin);

    printf("Introduce contrasenya: ");
    fgets(contrasenya, 18, stdin);
    sscanf(contrasenya, "%c");

    loginProfesional(email, contrasenya);

    return 0;

}