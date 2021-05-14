#include <stdlib.h>
#include <iostream>
#include "menuCliente.h"
#include "../utils/inversiones/inversiones.h"

extern "C"
{
#include "../../../lib/sqlite3/sqlite3.h"
#include "../../../utils/colors.h"
#include "../../../db/dbConnection.h"
#include "../../../db/C/getData.h"
#include "../../C/utils/structures.h"
}
#include "../utils/containers/containers.h"
#include <iomanip>

using namespace std;
using std::setw;
using namespace containers;

void menuCliente(ClienteCpp &cli)
{

    char *input;
    input = new char;

    cout << "\e[1;1H\e[2J" << endl; //limpiar terminal

    do
    {
        cout << FGREN "**********************Bienvenido " << cli.getNombre() << "**********************" << endl;
        cout << (FCYAN
                 "1.- Ver listado de cuentas\n"
                 "2.- Gestionar inversiones\n"
                 "3.- Ver datos de mi cuenta\n"
                 "q.- Cerrar\n\n"
                 "Inserte seleccion: ");

        cin >> input;

        switch (*input)
        {
        case '1':
            cout << ("\e[1;1H\e[2J") << endl;
            mostrarCuentas(cli);
            cout << endl;
            break;
        case '2':
            cout << ("\e[1;1H\e[2J") << endl;
            // menuInversiones(cli);
            cout << endl;
            break;
        case '3':
            verDatosCliente(cli);
            break;
        case 'q':
            cout << (FRED "\nSaliendo.\n") << endl;
            delete (input);
            break;
        default:
            cout << (FRED "\nIntroduce una opcion valida, por favor.\n") << endl;
            break;
        }
    } while (*input != 'q');
}

void mostrarCuentas(ClienteCpp &cli)
{
    char *input;
    input = new char;
    int index;

    cout << cli.getNombre() << endl;

    containers::CuentaCpp *listaCuentas;

    Cuenta *cuentasCliente = (Cuenta *)malloc(30 * sizeof(Cuenta));
    // el &cli.getDni()[0] es para pasar el puntero de la pos. 0 del dni al metodo. el c_str() davuelve un const char* y da errores
    cuentasCliente = getCuentasCliente(&cli.getDni()[0]);
    listaCuentas = new CuentaCpp[numFilas];
    for (int i = 0; i < numFilas; i++)
    {

        //inicializamos el array de listaCuentas con cuentas SIN movimientos porque todavía no tenemos estos
        listaCuentas[i].setDni(string((cuentasCliente + i)->dniPropietario));
        listaCuentas[i].setFecCreacion(string((cuentasCliente + i)->fechaCreacion));
        listaCuentas[i].setIban(string((cuentasCliente + i)->iban));
        listaCuentas[i].setSaldo((cuentasCliente + i)->saldo);
    }

    cout << "\n************ CUENTAS DE " << cli.getNombre() << "**************"
         << endl;
    printf("%-10s%-30s%-15s%-25s%-10s\n", "INDICE", "IBAN", "SALDO", "FECHA CREACION", "DNI");

    for (int i = 0; i < numFilas; i++)
    {
        //el printf da errores por los string
        cout << i << setw(30) << listaCuentas[i].getIban() << setw(15) << listaCuentas[i].getSaldo() << setw(25) << listaCuentas[i].getFecCreacion() << setw(10) << listaCuentas[i].getDni() << endl;
    }

    do
    {
        printf(FCYAN
               "\n1.- Visualizar movimientos de una cuenta\n"
               "q.- Atras\n");
        cin >> input;

        switch (*input)
        {
        case '1':
            printf("INTRODUZCA EL INDICE DE LA CUENTA\n");
            cin >> index;
            if (index < 0 || index > numFilas)
            {
                printf(FRED "Introduce un indice valido\n" FCYAN);
            }
            else
            {

                cargarMovimientos((listaCuentas[index]));
                verMovimientos(listaCuentas[index]);
            }
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n" FCYAN);
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n" FCYAN);
            break;
        }
    } while (*input != 'q');

    delete (input);
}

void verDatosCliente(ClienteCpp &cli)
{
    printf("\e[1;1H\e[2J");
    char *input = new char;

    do
    {
        printf(FCYAN "%-15s%-25s%-25s%-15s%-25s%-15s\n", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
        cout << setw(15) << cli.getDni() << setw(25) << cli.getNombre() << setw(25) << cli.getFecNac() << setw(15) << cli.getDomicilio() << setw(15) << cli.getTelf() << setw(25) << cli.getEmail() << setw(15) << cli.getDomicilio() << endl;
        printf("1.-Modificar datos\nq.-Salir\n");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);
        switch (*input)
        {
        case '1':
            modificarDatosCliente(cli);
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }
    } while (*input != 'q');
    delete (input);
}
void cargarMovimientos(CuentaCpp &c)
{
    Movimiento *movimientos = (Movimiento *)malloc(50 * sizeof(Movimiento));
    movimientos = getMovimientos(&c.getIban()[0]);
    MovimientoCpp *listaMovimientos = new MovimientoCpp[numFilas];

    for (int i = 0; i < numFilas; i++)
    {
        listaMovimientos[i] = MovimientoCpp((movimientos + i));
        free(movimientos + i);
    }

    c.setMovimientos(listaMovimientos);
}
void verMovimientos(CuentaCpp &c)
{
    cout << "\n************ MOVIMIENTOS CUENTA" << c.getIban() << "**************"
         << endl;
    printf("%-10s%-30s%-30s%-10s%-25s%-25s\n", "ID", "ORIGEN", "DESTINO", "IMPORTE", "FECHA", "CONCEPTO");

    for (int i = 0; i < numFilas; i++)
    {
        cout << c.getMovimientos()[i].getIdMovimiento() << setw(30) << c.getMovimientos()[i].getIbanOrigen() << setw(30) << c.getMovimientos()[i].getIbanDestino()
             << setw(10) << c.getMovimientos()[i].getImporte() << setw(25) << c.getMovimientos()[i].getFecha() << setw(25) << c.getMovimientos()[i].getConcepto() << endl;
    }
}
void modificarDatosCliente(ClienteCpp &cli)
{
}