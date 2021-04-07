#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "loginProfesional.h"
#include "../../db/getData.h"
#include "../../db/postData.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../../utils/colors.h"
#include "../menuProfesional/menuProfesional.h"

void loginProfesional(void)
{
    int resultLogin = 0;
    char *email;
    email = malloc(30 * sizeof(char));
    char *contrasenya;
    contrasenya = malloc(18 * sizeof(char));
    Profesional *prof;
    prof = (Profesional *)malloc(sizeof(Profesional));
    printf("**********************Bienvenido**********************\n");
    printf("INICIAR SESION\n");
    do
    {
        printf("Introduce el correo electronico: ");
        fgets(email, 30, stdin);
        sscanf(email, "%c", email);
        fflush(stdin);

        printf("Introduce contrase%ca: ", 164);
        fgets(contrasenya, 18, stdin);
        sscanf(contrasenya, "%c", contrasenya);
        fflush(stdin);
        *(contrasenya + strlen(contrasenya) - 1) = '\0'; //para quitar el salto de linea que añade sscanf

        if (startConn != SQLITE_OK)
        {
            resultLogin = getLogin(email, contrasenya);
        }
        else
            break;

        if (resultLogin == 0)
        {
            printf("%sINICIO DE SESION CORRECTO\n", FGREN);
            system("cls");
            prof = getInfoProfesional(email);
            menuProfesional(prof);
        }
        else
            printf("%sError en el inicio de sesion\n", FRED);
    } while (resultLogin != 0);

    free(email);
    email = NULL;
    free(contrasenya);
    contrasenya = NULL;
    free(prof->user);
    prof->user = NULL;
    free(prof);
    prof = NULL;
}