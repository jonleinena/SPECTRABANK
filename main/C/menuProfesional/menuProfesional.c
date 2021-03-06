#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menuProfesional.h"
#include "../../../db/C/getData.h"
#include "../../../db/C/postData.h"
#include "../../../lib/sqlite3/sqlite3.h"
#include "../../../utils/colors.h"
#include "../utils/structures.h"
#include "../utils/fechas.h"
#include "../utils/prestamo/prestamo.h"

void menuProfesional(Profesional *prof)
{

    char *input;
    input = malloc(sizeof(char));

    Cliente **lista;
    lista = (Cliente **)malloc(50 * sizeof(Cliente *));

    printf(CLEAR); //limpiar terminal

    do
    {
        printf(FGREN "**********************Bienvenido, %s**********************\n", prof->user->nombreApellidos);
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
            lista = getListaClientes((prof->idProfesional));
            lista = realloc(lista, numFilas * sizeof(Cliente *));
            printf(CLEAR);
            imprimirListaClientes(lista);
            printf("\n");
            for (int i = 0; i < numFilas; i++)
            {
                free((*(lista + i))->user);
                free(*(lista + i));
            }
            free(lista);
            break;
        case '2':
            verSolicitudesPrestamo(prof);
            break;
        case '3':
            verDatosProfesional(prof);
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

void imprimirListaClientes(Cliente **lista)
{
    char *input;
    int *index;
    input = malloc(sizeof(char));
    index = malloc(sizeof(int));

    printf("%-10s%-10s%-25s%-25s%-15s%-25s%-15s\n", "INDICE", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-10i%-10s%-25s%-25s%-15i%-25s%-15s\n", i, ((*(lista + i))->user->dni), ((*(lista + i))->user->nombreApellidos), ((*(lista + i))->user->fechaNacimiento), ((*(lista + i))->user->telefono), ((*(lista + i))->user->email), ((*(lista + i))->domicilio));
    }

    if (numFilas > 0)
    {
        int valorAceptable = 0;
        do
        {
            printf("Introduce indice del cliente o la letra q para salir: ");
            fgets(input, 4, stdin);
            if (*input != 'q')
            {
                sscanf(input, "%i", index);
                fflush(stdin);

                if ((*index < 0) || (*index > numFilas))
                {
                    printf(FRED "Introduzca un indice valido\n" FCYAN);
                }
                else
                {
                    valorAceptable = 1;
                }
            }
            fflush(stdin);

        } while (*input != 'q' && valorAceptable == 0);

        if (*input != 'q')
        {
            Cliente *clienteSel;
            clienteSel = (Cliente *)malloc(sizeof(Cliente));
            clienteSel = (*(lista + *index));

            printf(CLEAR);

            opcionesCltes(clienteSel);
            free(clienteSel);
        }
    }
    else
        printf("\nNO HAY CLIENTES PARA MOSTRAR\n");

    free(input);
    free(index);
}

void opcionesCltes(Cliente *cli)
{
    char *input;
    input = malloc(sizeof(char));

    do
    {
        printf("%-10s%-25s%-25s%-15s%-25s%-15s\n", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO", "DOMICILIO");
        printf("%-10s%-25s%-25s%-15i%-25s%-15s\n", (cli->user->dni), (cli->user->nombreApellidos), (cli->user->fechaNacimiento), (cli->user->telefono), (cli->user->email), (cli->domicilio));
        printf(FCYAN
               "\n1.- Mostrar cuentas de cliente\n"
               "2.- Mostrar inversiones\n"
               "3.- Mostrar prestamos\n"
               "q.- Atras\n\n"
               "Inserte opcion: ");
        fgets(input, 2, stdin); //ponemos 2 al fgets porque hay 3 opciones, pero si metes el 12 entra
        sscanf(input, "%c", input);
        fflush(stdin);

        if (*input != '0' && *input != '1' && *input != '2' && *input != '3' && *input != 'q')
        {
            printf(CLEAR);
            printf(FRED "Inserte un valor valido\n" FCYAN);
        }
        else
        {
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
                printf(FRED "\nSaliendo.\n\n" FCYAN);
                printf(CLEAR);
                break;
            default:
                printf(FRED "\nIntroduce una opcion valida, por favor.\n\n" FCYAN);
                break;
            }
        }

    } while (*input > 3 && *input != 'q');

    free(input);
}

void mostrarCuentas(Cliente *cli)
{
    char *input;
    input = malloc(sizeof(char));
    int *index;
    index = malloc(sizeof(int));

    Cuenta *listaCuentas;
    listaCuentas = malloc(30 * sizeof(Cuenta));
    listaCuentas = getCuentasCliente(cli->user->dni);
    listaCuentas = realloc(listaCuentas, numFilas * sizeof(Cuenta)); // resize the memory block pointed to by listaCuentas

    printf("\n************ CUENTAS DE %s**************\n", (cli->user->nombreApellidos));
    printf("%-10s%-30s%-15s%-25s%-10s\n", "INDICE", "IBAN", "SALDO", "FECHA CREACION", "DNI");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-10d%-30s%-15.2f%-25s%-10s\n", i, (listaCuentas + i)->iban, (listaCuentas + i)->saldo, (listaCuentas + i)->fechaCreacion, (listaCuentas + i)->dniPropietario);
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
            fgets(input, 4, stdin);
            sscanf(input, "%i", index);
            fflush(stdin);
            if (*index < 0 || *index > numFilas)
            {
                printf(FRED "Introduce un indice valido\n" FCYAN);
            }
            else
            {
                verMovimientos((listaCuentas + *index));
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

    free(input);
    free(index);
}

void mostrarInversiones(Cliente *cli)
{
    char *input;
    input = malloc(sizeof(char));

    printf(CLEAR);

    do
    {
        Inversion *listaInversiones;
        listaInversiones = malloc(30 * sizeof(Inversion));
        listaInversiones = getInversionClite(cli->user->dni);
        listaInversiones = realloc(listaInversiones, numFilas * sizeof(Inversion));

        printf("\n************ INVERSIONES DE %s**************\n", (cli->user->nombreApellidos));
        printf("%-10s%-10s%-20s%-25s%-10s\n", "COMPANIA", "CANTIDAD", "VALOR DE COMPRA", "FECHA DE COMPRA", "POSICION TOTAL");
        for (int i = 0; i < numFilas; i++)
        {
            printf("%-10s%-10d%-20.2f%-25s%-10.2f\n", (listaInversiones + i)->idCompania, (listaInversiones + i)->cantidad, (listaInversiones + i)->valorCompra, (listaInversiones + i)->fechaCompra, (listaInversiones + i)->cantidad * (listaInversiones + i)->valorCompra);
        }

        printf("Presione Enter para salir");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);

    } while (*input != '\n');

    printf(CLEAR);
    free(input);
}

void mostrarPrestamos(Cliente *cli)
{
    char *input;
    input = malloc(sizeof(char));
    printf(CLEAR);

    do
    {
        Prestamo *listaPrestamos;
        listaPrestamos = (Prestamo *)malloc(15 * sizeof(Prestamo));
        listaPrestamos = getPrestamos(cli->user->dni);
        listaPrestamos = realloc(listaPrestamos, numFilas * sizeof(Prestamo));

        printf("\n************ PRESTAMOS DE %s**************\n", (cli->user->nombreApellidos));
        printf("%-10s%-10s%-25s%-25s%-25s%-5s\n", "ID", "IMPORTE", "FECHA EMISION", "FECHA DEVOLUCION", "FECHA COMPLETADO", "TAE");
        for (int i = 0; i < numFilas; i++)
        {
            printf("%-10i%-10.2f%-25s%-25s%-25s%-5.2f%%\n", (listaPrestamos + i)->idPres, (listaPrestamos + i)->importe, (listaPrestamos + i)->fechaEmision, (listaPrestamos + i)->fechaDevol, strcmp((listaPrestamos + i)->fechaComp, "NULL") != 0 ? (listaPrestamos + i)->fechaComp : "Sin completar", (listaPrestamos + i)->tae);
        }

        printf("Presione Enter para salir");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);

    } while (*input != '\n');

    printf(CLEAR);
    free(input);
}

void verMovimientos(Cuenta *cue)
{
    Movimiento *movimientos;
    movimientos = (Movimiento *)malloc(40 * sizeof(Movimiento));
    movimientos = getMovimientos(cue->iban);
    movimientos = realloc(movimientos, numFilas * sizeof(Movimiento));

    printf("\n************ MOVIMIENTOS CUENTA %s**************\n", cue->iban);
    printf("%-10s%-30s%-30s%-10s%-25s%-25s\n", "ID", "ORIGEN", "DESTINO", "IMPORTE", "FECHA", "CONCEPTO");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-10i%-30s%-30s%-10.2f%-25s%-25s\n", (movimientos + i)->idTransaccion, (movimientos + i)->ibanOrigen, (movimientos + i)->ibanDestino, (movimientos + i)->importe, (movimientos + i)->fecha, (movimientos + i)->concepto);
    }
}

void verSolicitudesPrestamo(Profesional *prof)
{
    char *input;
    input = malloc(sizeof(char));
    int *index;
    index = malloc(sizeof(int));

    Prestamo *listaPrestamosPendientes;
    listaPrestamosPendientes = (Prestamo *)malloc(40 * sizeof(Prestamo));
    listaPrestamosPendientes = getSolicitudesPrestamo(prof);
    listaPrestamosPendientes = realloc(listaPrestamosPendientes, numFilas * sizeof(Prestamo));

    printf("\n************ TIENES %i SOLICITUDES PENDIENTES **************\n", numFilas);
    printf("%-5s%-15s%-14s%-25s\n", "ID", "CLIENTE", "IMPORTE", "FECHA SOLICITUD");
    for (int i = 0; i < numFilas; i++)
    {
        printf("%-5i%-15s%-14.2f%-25s\n", i, (listaPrestamosPendientes + i)->cli->user->dni, (listaPrestamosPendientes + i)->importe, (listaPrestamosPendientes + i)->fechaSoli);
    }

    do
    {
        printf(FCYAN
               "\n1.- Procesar una solicitud\n"
               "q.- Atras\n");
        fgets(input, 2, stdin);
        sscanf(input, "%c", input);
        fflush(stdin);
        switch (*input)
        {
        case '1':
            printf("Introduzca el ID de la solicitud a procesar: \n");
            fgets(input, 2, stdin);
            sscanf(input, "%i", index);
            fflush(stdin);
            (listaPrestamosPendientes + *index)->tae = calcularInteres((listaPrestamosPendientes + *index));
            printf("LA TAE DEL PRESTAMO ES: %f", (listaPrestamosPendientes + *index)->tae);
            //Actualizar prestamo con su TAE calculada y estado 2 (Aceptado)
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n" FCYAN);
            for (int i = 0; i < numFilas; i++)
            {
                free((listaPrestamosPendientes + i)->cli);
                free((listaPrestamosPendientes + i)->cli->user);
            }
            free(listaPrestamosPendientes);
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n" FCYAN);
            break;
        }

    } while (*input != 'q');
    free(input);
    free(index);
}

void verDatosProfesional(Profesional *prof)
{
    printf(CLEAR);
    char *input;
    input = malloc(sizeof(char));

    do
    {
        printf(FCYAN "%-15s%-10s%-25s%-25s%-15s%-25s\n", "idProfesional", "DNI", "NOMBRE Y APELLIDOS", "FECHA DE NACIMIENTO", "TELEFONO", "CORREO ELECTRONICO");
        printf("%-15s%-10s%-25s%-25s%-15i%-25s\n", (prof->idProfesional), (prof->user->dni), (prof->user->nombreApellidos), (prof->user->fechaNacimiento), (prof->user->telefono), (prof->user->email));
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
    input = malloc(30 * sizeof(char));
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
            sscanf(input, "%s", input);
            fflush(stdin);
            if (modificarProfesional(selec, prof, input) == 101)
            {
                printf("CAMBIO COMPLETADO SATISFACTORIAMENTE\n");
                prof->user->telefono = atoi(input);
            }
            else
                printf("ERROR EN EL GUARDADO DE DATOS\n");

            break;
        case '2':
            printf("INTRODUCE EL NUEVO CORREO: \n");
            fgets(input, 30, stdin);
            sscanf(input, "%s", input);
            fflush(stdin);
            if (modificarProfesional(selec, prof, input) == 101)
            {
                printf("CAMBIO COMPLETADO SATISFACTORIAMENTE\n");
                strcpy(prof->user->email, input);
            }
            else
                printf("ERROR EN EL GUARDADO DE DATOS\n");
            break;
        case '3':
            printf("INTRODUCE EL NUEVO CONTRASENA: \n");
            fgets(input, 11, stdin);
            sscanf(input, "%s", input);
            fflush(stdin);
            if (modificarProfesional(selec, prof, input) == 101)
            {
                printf("CAMBIO COMPLETADO SATISFACTORIAMENTE\n");
                strcpy(prof->user->contrasenya, input);
            }
            else
                printf("ERROR EN EL GUARDADO DE DATOS\n");
            break;
        case 'q':
            printf(FRED "\nSaliendo.\n\n");
            printf(CLEAR);
            fflush(stdin);
            break;
        default:
            printf(FRED "\nIntroduce una opcion valida, por favor.\n\n");
            break;
        }
        fflush(stdin);

    } while (*selec != 'q');

    free(input);
}