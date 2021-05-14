#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "menuCliente.h"
#include "../utils/inversiones/inversiones.h"
#include "../../../db/C++/postDataCPP.h"

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

    cout << CLEAR << endl; //limpiar terminal

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
        cin.ignore();

        switch (*input)
        {
        case '1':
            cout << CLEAR << endl;
            menuCuentas(cli);
            cout << endl;
            break;
        case '2':
            cout << CLEAR << endl;
            // menuInversiones(cli);
            cout << endl;
            break;
        case '3':
            cout << CLEAR << endl;
            menuDatosCliente(cli);
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


void menuCuentas(ClienteCpp &cli)
{
    char *input;
    input = new char;
    int index;

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

    do
    {
        mostrarCuentas(cli, listaCuentas);
        cout << FCYAN << "\n1.- Visualizar movimientos de una cuenta\n"
                      << "q.- Atras\n" << endl;
        cin >> input;
        cout << CLEAR << endl;

        switch (*input)
        {
        case '1':
            mostrarCuentas(cli, listaCuentas);
            cout << FCYAN << "\nINTRODUZCA INDICE DE LA CUENTA: ";
            cin >> index;
            cout << CLEAR << endl;

            if (index < 0 || index > numFilas)
            {
                cout << FRED << "Introduce un indice valido" << endl;
            }
            else
            {
                cargarMovimientos((listaCuentas[index]));
                mostrarMovimientos(listaCuentas[index]);
            }
            break;
        case 'q':
            break;
        default:
            cout << CLEAR << endl;
            cout << FRED << "\nIntroduce una opcion valida, por favor.\n" << endl;
            break;
        }
    } while (*input != 'q');

    delete (input);
}


void menuDatosCliente(ClienteCpp &cli){
    char *input = new char;

    do
    {
        mostrarDatosCliente(cli);
        cout << FCYAN << "1.-Modificar datos\n"
                      << "q.-Salir" << endl;

        cin >> input;
        cin.ignore();

        switch (*input)
        {
        case '1':
            cout << CLEAR << endl;
            modificarDatosCliente(cli);
            break;
        case 'q':
            cout << CLEAR << endl;
            break;
        default:
            cout << CLEAR << endl;
            cout << FRED << "\nIntroduce una opcion valida, por favor.\n" << endl;
            break;
        }
    } while (*input != 'q');
    delete (input);
}


void mostrarCuentas(ClienteCpp &cli, CuentaCpp *listaCuentas)
{
    cout << "************ CUENTAS DE " << cli.getNombre() << " **************" << endl;
    cout << "INDICE" << setw(25) << "IBAN" << setw(15) << "SALDO" << setw(25) << "FECHA CREACION" << setw(10) << "DNI" << endl;

    for (int i = 0; i < numFilas; i++)
    {
        cout << i << setw(30) << listaCuentas[i].getIban() << setw(15) << listaCuentas[i].getSaldo() << setw(25) << listaCuentas[i].getFecCreacion() << setw(10) << listaCuentas[i].getDni() << endl;
    }
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


void mostrarMovimientos(CuentaCpp &c)
{
    cout << "\n************ MOVIMIENTOS CUENTA " << c.getIban() << " **************" << endl;
    cout << "ID" << setw(30) << "ORIGEN" << setw(30) << "DESTINO" << setw(10) << "IMPORTE" << setw(25) << "FECHA" << setw(25) << "CONCEPTO" << endl;

    for (int i = 0; i < numFilas; i++)
    {
        cout << c.getMovimientos()[i].getIdMovimiento() << setw(30) << c.getMovimientos()[i].getIbanOrigen() << setw(30) << c.getMovimientos()[i].getIbanDestino()
             << setw(10) << c.getMovimientos()[i].getImporte() << setw(25) << c.getMovimientos()[i].getFecha() << setw(25) << c.getMovimientos()[i].getConcepto() << endl;
    }

    cout << "\nPresione Enter para salir";
    
    cin.get();
    cin.ignore();
    cout << CLEAR << endl;
}


void mostrarDatosCliente(ClienteCpp &cli)
{
    cout << "DNI" << setw(25) << "NOMBRE Y APELLIDOS" << setw(25) << "FECHA DE NACIMIENTO" << setw(15) << "TELEFONO" << setw(25) << "CORREO ELECTRONICO" << setw(15) << "DOMICILIO" << endl;
    cout << cli.getDni() << setw(25) << cli.getNombre() << setw(25) << cli.getFecNac() << setw(15) << cli.getTelf() << setw(25) << cli.getEmail() << setw(15) << cli.getDomicilio() << endl;
}


void modificarDatosCliente(ClienteCpp &cli)
{
    char *input, *selec;
    input = new char[30];
    selec = new char;

    do
    {
        mostrarDatosCliente(cli);
        cout << FCYAN << "1.-Modificar telefono\n"
                      << "2.-Modificar correo\n"
                      << "3.-Modificar domicilio\n"
                      << "4.-Modificar contrasena\n"
                      << "q.-Salir" << endl;
        cin >> selec;
        switch (*selec)
        {
        case '1':
            cout << FCYAN << "INTRODUCE EL NUEVO TELEFONO: ";
            break;
        case '2':
            cout << FCYAN << "INTRODUCE EL NUEVO CORREO: ";
            break;
        case '3':
            cout << FCYAN << "INTRODUCE EL NUEVO DOMICILIO: ";
            break;
        case '4':
            cout << FCYAN << "INTRODUCE LA NUEVA CONTRASENA: ";
            break;
        case 'q':
            cout << CLEAR << endl;
            break;
        default:
            cout << FRED << "\nIntroduce una opcion valida, por favor.\n" << endl;
            break;
        }

        cin >> input;
        cin.ignore();

        if (modificarCliente(selec, cli, input) == 101)
        {
            if(atoi(selec) == 1){
                cout << FGREN << "TELEFONO CAMBIADO CORRECTAMENTE" << endl;
                cli.setTelf(atoi(input));
            } else if (atoi(selec)==2){
                cout << FGREN << "CORREO CAMBIADO CORRECTAMENTE" << FCYAN << endl;
                cli.setEmail(string(input));
            } else if (atoi(selec)==3){
                cout << FGREN << "DOMICILIO CAMBIADO CORRECTAMENTE" << FCYAN << endl;
                cli.setDomicilio(string(input));
            } else if (atoi(selec)==4){
                cout << FGREN << "CONTRASENA CAMBIADA CORRECTAMENTE" << FCYAN << endl;
            }

            sleep(2);
            cout << CLEAR << endl;

        }else{
            cout << FRED << "ERROR EN EL GUARDADO DE DATOS" << endl; 
        }
            
    } while (*selec != 'q');

    delete input, selec;
}