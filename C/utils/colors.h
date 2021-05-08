//Atributos
#define RESET "\x1B[0m" //Resetea a la apariencia por defecto
#define BOLD_ON "\x1B[1m"
#define CURS_ON "\x1B[3m"
#define UNDER_ON "\x1B[4m"

//Los colores siguen el siguiente patrón:
//
//  Color de letra --> \x1B[38;2;R;G;Bm
//  Color de fondo --> \x1B[48;2;R;G;Bm 
//
//Sustituir R G B por los valores deseados

//Colores de fuente (Foreground)
#define FBLCK "\x1B[38;2;0;0;0m"
#define FWHITE "\x1B[38;2;255;255;255m"
#define FRED "\x1B[38;2;255;0;0m"
#define FGREN "\x1B[38;2;0;255;0m"
#define FBLUE "\x1B[38;2;0;0;255m"
#define FCYAN "\x1B[38;2;51;244;255m"


//Colores de fondo (Background)
#define BBLCK "\x1B[48;2;0;0;0m"
#define BCYAN "\x1B[48;2;51;244;255m"

