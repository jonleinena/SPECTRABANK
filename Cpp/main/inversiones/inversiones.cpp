#include "stockAPI.h"
#include <iostream>
#include <stdio.h>
#include "inversiones.h"
#include "../../containers/containers.h"
#include "../../utils/db/dbConnection.h"
#include "../../utils/db/getDataCPP.h"
#include "../../../C/utils/structures.h"
#include "../../../C/utils/colors.h"

using namespace stockAPI;
using namespace std;
using namespace containers;

int main(void)
{
    if (startConn())
    {
        return 0;
    }
    ClienteCpp cli("1", "CLIENTE 1", "A", "2021/04/08", "CLIENTE1", 0);
    menuInversiones(cli);
    return 0;
}

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
            cout << ("\e[1;1H\e[2J") << endl;
            verInversiones(cli);
            break;
        case '2':
            cout << ("\e[1;1H\e[2J") << endl;
            comprarAcciones(cli);
            break;
        case '3':
            cout << ("\e[1;1H\e[2J") << endl;
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
    char *query;
    cout << "***************COMPRAR ACCIONES***************" << endl;
    cout << "Busque un stock: ";
    cin >> query;
    Search s(query);
    Symbol **searchResults = s.getResults();
    printf("%-5s%-15s%-20s%-30s%-15s\n", "", "SYMBOL", "DISPLAY SYMBOL", "DESCRIPTION", "TYPE");
    for (int i = 0; i < s.getCount(); i++)
    {
        printf("%-5d%-15s%-20s%-30s%-15s\n", i + 1, (*(searchResults + i))->getSymbol(), (*(searchResults + i))->getDisplaySymbol(), (*(searchResults + i))->getDescription(), (*(searchResults + i))->getType());
    }

    int j;
    cout << "Elige un Stock (introduzca su índice): ";
    cin >> j;
    cout << "La cotización actual de " << (*(searchResults + j - 1))->getSymbol() << " es " << (*(searchResults + j - 1))->getCurrentValue() << endl;
}

void venderAcciones(ClienteCpp &cli)
{
}
