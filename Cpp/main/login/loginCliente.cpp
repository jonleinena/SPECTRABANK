#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "../../../lib/sqlite3/sqlite3.h"
#include "loginCliente.h"
#include "../../containers/containers.h"
#include "../../../C/utils/colors.h"

using namespace std;
using namespace containers;

void loginCliente(void)
{

    int resultLogin = 0;
    char *email;
    email = malloc(30 * sizeof(char));
    char *contrasenya;
    contrasenya = malloc(18 * sizeof(char));

    cout << "**********************Bienvenido**********************" << endl;
    cout << "INICIAR SESION" << endl;

    do
    {
        cout << "Introduce el correo electronico: ";
        cin >> email;
        cout << endl;

        cout << ("Introduce contrase%ca: ", 164);
        cin >> contrasenya;
        cout << endl;

        *(contrasenya + strlen(contrasenya) - 1) = '\0'; //para quitar el salto de linea que añade sscanf

        if (startConn != SQLITE_OK)
        {
            resultLogin = getLogin(email, contrasenya);
        }
        else
            break;

        if (resultLogin == 0)
        {
            cout << "%sINICIO DE SESION CORRECTO", FGREN) << endl;
            cout << "\e[1;1H\e[2J" << endl;
            ClienteCpp c(getInfoCliente(email));
            menuCliente(&c);
        }
        else
            cout << FRED "Error en el inicio de sesion" FCYAN) << endl;
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