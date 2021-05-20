#include <iostream>
#include <string.h>
#include <stdlib.h>

extern "C"
{
#include "../../../lib/sqlite3/sqlite3.h"
#include "../../../utils/colors.h"
#include "../../../db/dbConnection.h"
#include "../../../db/C/getData.h"
#include "../../C/utils/structures.h"
}
#include "loginCliente.h"
#include "../utils/containers/containers.h"
#include "../menuCliente/menuCliente.h"

using namespace std;
using namespace containers;

void loginCliente(void)
{

    int resultLogin = 0;
    char *email;
    email = (char *)malloc(30 * sizeof(char));
    char *contrasenya;
    contrasenya = (char *)malloc(18 * sizeof(char));

    cout << "**********************Bienvenido**********************" << endl;
    cout << "INICIAR SESION" << endl;

    do
    {
        cout << "Introduce el correo electronico: ";
        cin >> email;
        cout << endl;

        cout << "Introduce contrasena: " << endl;
        cin >> contrasenya;
        cout << endl;

        // *(contrasenya + strlen(contrasenya) - 1) = '\0'; //para quitar el salto de linea que añade sscanf

        if (startConn != SQLITE_OK)
        {
            resultLogin = getLogin(email, contrasenya, 0);
        }
        else
            break;

        if (resultLogin == 0)
        {
            cout << FGREN "INICIO DE SESION CORRECTO" << endl;
            cout << CLEAR << endl;
            ClienteCpp c(getInfoCliente(email));
            menuCliente(c);
        }
        else
            cout << FRED << "Error en el inicio de sesion" << FCYAN << endl;
    } while (resultLogin != 0);

    delete[] email;
    delete[] contrasenya;
}