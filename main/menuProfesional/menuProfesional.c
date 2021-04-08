#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menuProfesional.h"
#include "../../db/getData.h"
#include "../../db/postData.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../../utils/colors.h"
#include "../../utils/structures.h"

int numFilas = 1;

void menuProfesional(Profesional *prof)
{

    char *input;
    input = malloc(sizeof(char));

    Cliente **lista;
    lista = (Cliente **)malloc(50 * sizeof(Cliente *));

    printf("\e[1;1H\e[2J"); //limpiar terminal

    printf("**********************Bienvenido, %s**********************\n",
           prof->user->nombreApellidos);

    do
    {
        printf(FCYAN
               "1.- Ver listado de clientes\n"
               "2.- Solicitudes de prestamo\n"
               "3.- Ver datos de mi cuenta\n"
               "q.- Cerrar\n\n"
               "Inserte seleccion: ");

        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);

        switch (*input)
        {
        case '1':
            lista = getListaClientes((prof->idProfesional), &numFilas);
            realloc(lista, numFilas * sizeof(Cliente *));
            imprimirListaClientes(lista, &numFilas);

            printf("\n");
            break;
        case '2':
            break;
        case '3':
            verDatosProfesional(prof);
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            for (int i = 0; i < *(&numFilas); i++)
            {
                free((*(lista + i))->user);
                free(*(lista + i));
            }
            free(lista);
            free(input);
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }
    } while (*input != 'q');
}

void imprimirListaClientes(Cliente **lista, int *numElems)
{
    char *input;
    int *index;
    input = malloc(sizeof(char));
    index = malloc(sizeof(int));

    printf("%-10s%-10s%-25s%-25s%-15s%-25s%-15s\n", "INDICE", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
    for (int i = 0; i < *numElems; i++)
    {
        printf("%-10i%-10s%-25s%-25s%-15i%-25s%-15s\n", i, ((*(lista + i))->user->dni), ((*(lista + i))->user->nombreApellidos), ((*(lista + i))->user->fechaNacimiento), ((*(lista + i))->user->telefono), ((*(lista + i))->user->email), ((*(lista + i))->domicilio));
    }

    printf("Introduce indice del cliente: ");
    fgets(input, 2, stdin);
    sscanf(input, "%i", index);
    fflush(stdin);

    Cliente *clienteSel;
    clienteSel = (Cliente *)malloc(sizeof(Cliente));
    clienteSel = (*(lista + *index));

    printf("\e[1;1H\e[2J");
    printf("%-10s%-25s%-25s%-15s%-25s%-15s\n", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
    printf("%-10s%-25s%-25s%-15i%-25s%-15s\n", (clienteSel->user->dni), (clienteSel->user->nombreApellidos), (clienteSel->user->fechaNacimiento), (clienteSel->user->telefono), (clienteSel->user->email), (clienteSel->domicilio));

    opcionesCltes(clienteSel);

    free(input);
    free(index);
    free(clienteSel);
}

void opcionesCltes(Cliente *cli)
{
    char *input;
    input = malloc(sizeof(char));

    do
    {
        printf(FCYAN
               "\n1.- Mostrar cuentas de cliente\n"
               "2.- Mostrar inversiones\n"
               "3.- Mostrar prestamos\n"
               "q.- Atras\n");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);

        switch (*input)
        {
        case '1':
            mostrarCuentas(cli);
            break;
        case '2':
            mostrarInversiones(cli);
            break;
        case '3':
            mostrarPrestamos(cli);
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }
    } while (*input != 'q');

    free(input);
}

void mostrarCuentas(Cliente *cli)
{
    char *input;
    input = malloc(sizeof(char));
    int *index;
    index = malloc(sizeof(int));
    char *selec;
    selec = malloc(sizeof(char));

    Cuenta *listaCuentas;
    listaCuentas = malloc(30 * sizeof(Cuenta));
    listaCuentas = getCuentasCliente(cli->user->dni, &numFilas);
    realloc(listaCuentas, numFilas * sizeof(Cuenta)); // resize the memory block pointed to by listaCuentas

    printf("\n************ CUENTAS DE %s**************\n", (cli->user->nombreApellidos));
    printf("%-10s%-25s%-15s%-25s%-10s\n", "INDICE", "IBAN", "SALDO", "FECHA CREACION", "DNI");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-10d%-25s%-15.2f%-25s%-10s\n", i, (listaCuentas + i)->iban, (listaCuentas + i)->saldo, (listaCuentas + i)->fechaCreacion, (listaCuentas + i)->dniPropietario);
    }

    do
    {
        printf(FCYAN
               "\n1.- Visualizar movimientos de una cuenta\n"
               "q.- Atras\n");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);
        switch (*input)
        {
        case '1':
            printf("INTRODUZCA EL INDICE DE LA CUENTA\n");
            fgets(selec, 2, stdin);
            sscanf(selec, "%i", index);
            fflush(stdin);
            verMovimientos((listaCuentas + *index), &numFilas);
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }

    } while (*input != 'q');

    free(input);
    free(index);
    free(selec);
}

void mostrarInversiones(Cliente *cli)
{
    Inversion *listaInversiones;
    listaInversiones = malloc(30 * sizeof(Inversion));
    listaInversiones = getInversionClite(cli, &numFilas);
    realloc(listaInversiones, numFilas * sizeof(Inversion));

    printf("\n************ INVERSIONES DE %s**************\n", (cli->user->nombreApellidos));
    printf("%-10s%-10s%-20s%-25s%-10s\n", "COMPANIA", "CANTIDAD", "VALOR DE COMPRA", "FECHA DE COMPRA", "POSICION TOTAL");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-10s%-10d%-20.2f%-25s%-10.2f\n", (listaInversiones + i)->idCompania, (listaInversiones + i)->cantidad, (listaInversiones + i)->valorCompra, (listaInversiones + i)->fechaCompra, (listaInversiones + i)->cantidad * (listaInversiones + i)->valorCompra);
    }
}

void mostrarPrestamos(Cliente *cli)
{
    Prestamo *listaPrestamos;
    listaPrestamos = (Prestamo *)malloc(15 * sizeof(Prestamo));
    listaPrestamos = getPrestamos(cli, &numFilas);
    realloc(listaPrestamos, numFilas * sizeof(Prestamo));

    printf("\n************ PRESTAMOS DE %s**************\n", (cli->user->nombreApellidos));
    printf("%-10s%-10s%-25s%-25s%-25s%-5s\n", "ID", "IMPORTE", "FECHA EMISION", "FECHA DEVOLUCION", "FECHA COMPLETADO", "TAE");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-10i%-10.2f%-25s%-25s%-25s%-5.2f%%\n", (listaPrestamos + i)->idPres, (listaPrestamos + i)->importe, (listaPrestamos + i)->fechaEmision, (listaPrestamos + i)->fechaDevol, strcmp((listaPrestamos + i)->fechaComp, "NULL") != 0 ? (listaPrestamos + i)->fechaComp : "Sin completar", (listaPrestamos + i)->tae);
    }
}

//Hacer este metodo (el getData esta ya)
void verMovimientos(Cuenta *cue, int *numFilas)
{
    Movimiento *movimientos;
    movimientos = (Movimiento *)malloc(40 * sizeof(Movimiento));
    movimientos = getMovimientos(cue, numFilas);
    realloc(movimientos, *numFilas * sizeof(Movimiento));

    printf("\n************ MOVIMIENTOS CUENTA %s**************\n", cue->iban);
    printf("%-10s%-25s%-25s%-10s%-25s%-25s\n", "ID", "ORIGEN", "DESTINO", "IMPORTE", "FECHA", "CONCEPTO");
    for (int i = 0; i < *numFilas; i++)
    {
        printf("%-10i%-25s%-25s%-10.2f%-25s%-25s\n", (movimientos + i)->idTransaccion, (movimientos + i)->ibanOrigen, (movimientos + i)->ibanDestino, (movimientos + i)->importe, (movimientos + i)->fecha, (movimientos + i)->concepto);
    }
}

void verDatosProfesional(Profesional *prof)
{
    printf("\e[1;1H\e[2J");
    printf("%-15s%-10s%-25s%-25s%-15s%-25s\n", "idProfesional", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO");
    printf("%-15s%-10s%-25s%-25s%-15i%-25s\n", (prof->idProfesional), (prof->user->dni), (prof->user->nombreApellidos), (prof->user->fechaNacimiento), (prof->user->telefono), (prof->user->email));
    char *input;
    input = malloc(sizeof(char));

    do
    {
        printf("1.-Modificar datos\nq.-Salir\n");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);
        switch (*input)
        {
        case '1':
            modificarDatos(prof);
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }
    } while (*input != 'q');
    free(input);
}

void modificarDatos(Profesional *prof)
{

    char *input, *selec;
    input = malloc(10 * sizeof(char));
    selec = malloc(sizeof(char));

    do
    {
        printf("1.-Modificar telefono\n2.-Modificar correo\n3.-Modificar contrasena\nq.-Salir\n");
        fgets(selec, 2, stdin);
        sscanf(selec, "%c", selec);
        fflush(stdin);
        switch (*selec)
        {
        case '1':
            printf("INTRODUCE EL NUEVO TELEFONO: \n");
            fgets(input, 10, stdin);
            sscanf(input, "%c", input);
            fflush(stdin);
            printf("%i\n", modificarProfesional(selec, prof, input));
            break;
        case '2':

            break;
        case '3':

            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }

    } while (*selec != 'q');

    free(input);
}