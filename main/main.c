#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../login/loginProfesional.h"
#include "../login/loginCliente.h"
#include "../db/getData.h"
#include "../db/postData.h"
#include "../db/dbConnection.h"
#include "../utils/colors.h"

int main(void)
{
    if (startConn(db))
    {
        return 0;
    }

    system("cls"); //Esta limpieza se ejecuta para el buen funcionamiento de la apariencia de la consola
    char *input;
    input = malloc(sizeof(char));

    printf("%s%s"
            "\t\t                                               ``                                                \n"
            "\t\t                                           ``......``                                            \n"
            "\t\t                                       ``..../sdmy/-...``                                        \n"
            "\t\t                                    .....:ohNMMMMMMNds/.....`                                    \n"
            "\t\t                               ``....-+ymMMMMMMMMMMMMMMNho:....`                                 \n"
            "\t\t                            ``...-+ymNMMMMMMMMMMMMMMMMMMMMMmy+:...``                             \n"
            "\t\t                        ``...-/sdNMMMMMMMMMMMMMMMMMMMMMMMMMMMMNmy+-...``                         \n"
            "\t\t                    ``....:ohNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNds/-...``                     \n"
            "\t\t                ``....:+hmNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNho/....``                 \n"
            "\t\t             ``...-+ymNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNho:...```             \n"
            "\t\t         ``...-/sdNMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMNmy+-...``          \n"
            "\t\t     ``.....:oyhddddddddddddddddddddddddddho/-.``..:+ydddddddddddddddddddddddddddhs/.....``      \n"
            "\t\t    -....-------------------------------.``           ``.------------------------------......    \n"
            "\t\t    `-..dNNNNNNNNNNNNNNNNNNNNNNNNNNNNNh.                 +NNNNNNNNNNNNNNNNNNNNNNNNNNNNNm:...`    \n"
            "\t\t     -.-NMMMMMMMMMMMMMMMMMMMMMMMMMMMMN-                   yMMMMMMMMMMMMMMMMMMMMMMMMMMMMM/..      \n"
            "\t\t     ...mMMMMMMMMMMMMMMMMMMMMMMMMMMMMy                    .MMMMMMMMMMMMMMMMMMMMMMMMMMMMN:.-      \n"
            "\t\t      ..-::::::::::::::::::::::::::::-                    `::::::::::::::::::::::::::::-...      \n"
            "\t\t       `..oyyyyyyyyyyyyy+.............`                   .............-yyyyyyyyyyyyyy..`        \n"
            "\t\t        ..:+++++++++++++:.-`          .                  ``          `..+++++++++++++/..`        \n"
            "\t\t        ../ooooooooo+///-.-`          ..`               `.           `..///+ooooooooo+..`        \n"
            "\t\t        ..:ssssssso:-..`` ``````      ....            `...       ````  ```..-+sssssss+..`        \n"
            "\t\t        ``...-/-`              ````    `..`          `..`    ```                ./:....`         \n"
            "\t\t           -.+d.    ``             ``` ``.`           . ` ```              `     +y..`           \n"
            "\t\t           -.+-   :yd:`.               ``               `               ``.ddo`   /..`           \n"
            "\t\t           -..   +MMM/.:`                                               ...NMMd`  `..`           \n"
            "\t\t           -.`  `NMMM/.-    ``   ``                           ``   `    ...NMMMo   ..`           \n"
            "\t\t           -.`  :MMMM/..   ``     .                          `      .   `..NMMMd   ..`           \n"
            "\t\t           -.`  /MMMM/.`   `      .    ` .``.      ```.```   .       `   ..NMMMm   ..`           \n"
            "\t\t           -..  /MMMM/.`   `      `   .  -..y/    `y..-  ``  `       `  `..NMMMm  `..`           \n"
            "\t\t           -./. :MMMM/..  ``      `  ``  -..hm    /N..-   .   `      `  `..NMMMd  :..`           \n"
            "\t\t           -.+s .MMMM/.:  ``      .  `   -..hM.   yN..-   `   `      .  ...NMMMy .s..`           \n"
            "\t\t           -.+N: mMMM/.:` ``      `  .   -..hM:   dN..-   `  `       `  -..NMMM/`hy..`           \n"
            "\t\t           -.+Mm.sMMM/.:.  `      .  `   -..hM+  `NN..-      `       ` ....NMMN.sMy..`           \n"
            "\t\t           -.+MMmsMMM/.: ` `      ``     -..hMs  .MN..-      `       ` .`..NMMmsMMy..`           \n"
            "\t\t           -.+MMMMMMM/.: ```       . `   -..hMh  -MN..-   ` ``      ``. `..NMMMMMMy..`           \n"
            "\t\t           -.+MMMMMMM/.:  .`       ``.   -..hMm  /MN..-   ` .       ``` `..NMMMMMMy..`           \n"
            "\t\t           -.+MMMMMMM/.:            ..   -..hMN` oMN..-   ```           `..NMMMMMMy..`           \n"
            "\t\t         `.-./hhhhhhh:.-`            `  `-..ohh` +hy..-.  `            `...yhhhhhho...`          \n"
            "\t\t        ...-------------...           `..------` .-----..`           ...-------------...`        \n"
            "\t\t       `..ommmmmmmmmmmmm+.-`          -..hmmmmm- hmmmmm-..           `.-mmmmmmmmmmmmmh..`        \n"
            "\t\t        ..................-`          -........` .........           `..................`        \n"
            "\t\t       `..sdddddddddddddo.-`          -..hddddd+`dddddd:..           `.:dddddddddddddh..`        \n"
            "\t\t      ....--------------.................------.`------.................--------------....       \n"
            "\t\t     ...shhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhs-hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhy-.-      \n"
            "\t\t     -.-NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMm+MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM/..      \n"
            "\t\t     ...::::::::::::::::::::::::::::::::::::::::-:::::::::::::::::::::::::::::::::::::::..-      \n"
            "\t\t      `````````````````````````````````````````````````````````````````````````````````````      \n\n\n", FWHITE, BBLCK);
    printf(
            "\t   /$$$$$$                                  /$$                         /$$$$$$$                      /$$       \n"
            "\t  /$$__  $$                                | $$                        | $$__  $$                    | $$       \n"
            "\t | $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$ | $$  \\ $$  /$$$$$$  /$$$$$$$ | $$   /$$ \n"
            "\t |  $$$$$$  /$$__  $$ /$$__  $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$| $$$$$$$  |____  $$| $$__  $$| $$  /$$/ \n"
            "\t  \\____  $$| $$  \\ $$| $$$$$$$$| $$        | $$    | $$  \\__/| $$$$$$$$| $$__  $$  /$$$$$$$| $$  \\ $$| $$$$$$/  \n"
            "\t  /$$  \\ $$| $$  | $$| $$_____/| $$        | $$ /$$| $$      | $$_____/| $$  \\ $$ /$$__  $$| $$  | $$| $$_  $$  \n"
            "\t |  $$$$$$/| $$$$$$$/|  $$$$$$$|  $$$$$$$  |  $$$$/| $$      |  $$$$$$$| $$$$$$$/|  $$$$$$$| $$  | $$| $$ \\  $$ \n"
            "\t  \\______/ | $$____/  \\_______/ \\_______/   \\___/  |__/       \\_______/|_______/  \\_______/|__/  |__/|__/  \\__/ \n"
            "\t           | $$                                                                                                 \n"
            "\t           | $$                                                                                                 \n"
            "\t           |__/                                                                                                 \n\n\n\n"
    );
    do
    {
        printf("%s%s"
               "1.- Inicio de sesion como profesional\n"
               "2.- Inicio de sesion como cliente\n"
               "q.- Cerrar\n\n"
               "Inserte selecci%cn: ",
               FCYAN, BBLCK, 162);

        fgets(input, 2, stdin);
        sscanf(input, "%c");
        fflush(stdin);

        switch (*input)
        {
        case '1':
            system("cls"); //Limpia el terminal
            loginProfesional();
            break;
        case '2':
            system("cls");
            loginCliente();
            break;
        case 'q':
            printf("%s\nSaliendo.\n\n", FRED);
            break;
        default:
            printf("%s\nIntroduce una opcion valida, por favor.\n\n", FRED);
            break;
        }
    } while (*input != 'q');

    printf(RESET); //Resetea los atributos de fuente cuando salimos del programa
    sqlite3_close(db);
    free(input);
    input = NULL;

    return 0;
}