#include "stockAPI.h"
#include <iostream>
#include <stdio.h>

using namespace stockAPI;
using namespace std;

int main(void)
{
    char *query;
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

    return 0;
}