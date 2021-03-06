#include "stockAPI.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "inversiones.h"
#include "../containers/containers.h"
#include "../../../../db/C++/getDataCPP.h"
#include "../../../../db/C++/postDataCPP.h"
#include "../../../C/utils/structures.h"
#include "../../../../utils/colors.h"
#include "../../../../db/dbConnection.h"
#include "../../../../lib/sqlite3/sqlite3.h"

using namespace stockAPI;
using namespace std;
using namespace containers;

void menuInversiones(ClienteCpp &cli)
{
    char *input = new char;

    do
    {
        cout << (FCYAN
                 "1.- Ver mis inversiones\n"
                 "2.- Comprar acciones\n"
                 "3.- Vender acciones\n"
                 "q.- Cerrar\n\n"
                 "Inserte seleccion: ");

        cin >> input;
        switch (*input)
        {
        case '1':
            cout << (CLEAR) << endl;
            verInversiones(cli);
            break;
        case '2':
            cout << (CLEAR) << endl;
            comprarAcciones(cli);
            break;
        case '3':
            cout << (CLEAR) << endl;
            venderAcciones(cli);
            break;
        case 'q':
            cout << (FRED "\nSaliendo.\n") << endl;
            break;
        default:
            cout << (FRED "\nIntroduce una opcion valida, por favor.\n") << endl;
            break;
        }
    } while (*input != 'q');

    delete input;
}

void verInversiones(ClienteCpp &cli)
{
    Inversiones *inversiones = getInversiones(cli.getDni());
    printf("%-10s%-10s%-20s%-25s%-10s\n", "COMPANIA", "CANTIDAD", "VALOR DE COMPRA", "FECHA DE COMPRA", "POSICION TOTAL");
    for (int i = 0; i < inversiones->getCount(); i++)
    {
        printf("%-10s%-10d%-20.2f%-25s%-10.2f\n", (inversiones->getInversiones() + i)->getIdCompania(), (inversiones->getInversiones() + i)->getCantidad(), (inversiones->getInversiones() + i)->getValorCompra(), (inversiones->getInversiones() + i)->getFechaCompra(), (inversiones->getInversiones() + i)->getCantidad() * (inversiones->getInversiones() + i)->getValorCompra());
    }
    
}

void comprarAcciones(ClienteCpp &cli)
{
    cout << "***************COMPRAR ACCIONES***************" << endl;
    cout << "Busque un stock: ";
    char *queryString = new char;
    cin >> queryString;
    cout << "Buscando..." << endl;
    Search s(queryString);
    Symbol **searchResults = s.getResults();
    delete queryString;
    if (s.getCount() == 0)
    {
        cout << "Sin resultados" << endl;
    }
    else
    {
        printf("%-5s%-15s%-20s%-30s%-15s\n", "", "SYMBOL", "DISPLAY SYMBOL", "DESCRIPTION", "TYPE");
        for (int i = 0; i < s.getCount(); i++)
        {
            printf("%-5d%-15s%-20s%-30s%-15s\n", i + 1, (*(searchResults + i))->getSymbol(), (*(searchResults + i))->getDisplaySymbol(), (*(searchResults + i))->getDescription(), (*(searchResults + i))->getType());
        }

        int j;
        do
        {
            cout << "Elige un Stock (introduzca su índice). Introduzca 0 cancelar la operacion: ";
            cin >> j;
        } while (0 > j || j > s.getCount());

        if (j == 0)
        {
            cout << "Cancelando operacion..." << endl;
        }
        else
        {
            cout << "La cotización actual de " << (*(searchResults + j - 1))->getSymbol() << " es " << (*(searchResults + j - 1))->getCurrentValue() << endl;
            int amount;
            cout << "Introduzca la cantidad a comprar (solo valores enteros): ";
            cin >> amount;
            cout << "Realizando compra..." << endl;
            cout << endl;
            int resCompra = comprarAcciones(*searchResults[j - 1], amount, cli);
            if (resCompra == 101)
            {
                cout << "Compra de acciones realizada con éxito" << endl;
            }
            else
            {
                cout << "Error al realizar la compra de acciones" << endl;
            }
        }
    }
    
}

void venderAcciones(ClienteCpp &cli)
{
    //Falta proceso de venta
    verInversiones(cli);
    cout << "Introduce el id de la compania" << endl;
    char *idComp = new char[6];
    cin >> idComp;
    Inversiones *inversiones = getInversiones(cli.getDni());
    bool accEncontrada = false;
    for (int i = 0; i < inversiones->getCount(); i++)
    {
        if (strcmp((inversiones->getInversiones() + i)->getIdCompania(), idComp) == 0)
            {
                accEncontrada = true;
                cout << "Introduce la cantidad de acciones que quieras vender de " << (inversiones->getInversiones() + i)->getIdCompania() << endl;
                int numAcciones;
                cin >> numAcciones;
                if (numAcciones <= (inversiones->getInversiones() + i)->getCantidad())
                    {
                        cout << "Realizando venta..." << endl;
                        int res =  venderAcciones((inversiones->getInversiones() + i)->getCantidad() - numAcciones, cli, idComp);

                        if(res == 101) cout << "Venta realizada con exito" << endl;
                    }
                else
                    cout << "No se pueden vender mas acciones de las que se tienen en posesion." << endl;
            } 
    } if ( accEncontrada == false) cout << "no se ha encontrado el id de la compania" << endl;
}
