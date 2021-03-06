#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "loginProfesional.h"
#include "../../../db/C/getData.h"
#include "../../../db/C/postData.h"
#include "../../../lib/sqlite3/sqlite3.h"
#include "../../../utils/colors.h"
#include "../menuProfesional/menuProfesional.h"

void loginProfesional(void)
{
    int resultLogin = 0;
    char *dni;
    dni = malloc(30 * sizeof(char));
    char *contrasenya;
    contrasenya = malloc(18 * sizeof(char));
    Profesional *prof;
    prof = (Profesional *)malloc(sizeof(Profesional));
    printf("**********************Bienvenido**********************\n");
    printf("INICIAR SESION\n");
    do
    {
        printf("Introduce el DNI: ");
        fgets(dni, 30, stdin);
        sscanf(dni, "%c", dni);
        fflush(stdin);

        printf("Introduce contraseña: ");
        fgets(contrasenya, 18, stdin);
        sscanf(contrasenya, "%c", contrasenya);
        fflush(stdin);
        *(contrasenya + strlen(contrasenya) - 1) = '\0'; //para quitar el salto de linea que añade sscanf

        resultLogin = getLogin(dni, contrasenya, 1);

        if (resultLogin == 0)
        {
            printf("%sINICIO DE SESION CORRECTO\n", FGREN);
            printf(CLEAR);
            prof = getInfoProfesional(dni);
            menuProfesional(prof);
        }
        else
            printf(FRED "Error en el inicio de sesion\n" FCYAN);
    } while (resultLogin != 0);

    free(dni);
    dni = NULL;
    free(contrasenya);
    contrasenya = NULL;
    free(prof->user);
    prof->user = NULL;
    free(prof);
    prof = NULL;
}