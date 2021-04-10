#ifndef structures_h
#define structures_h

typedef struct
{
    char dni[10];
    char contrasenya[11];
    char nombreApellidos[30];
    char fechaNacimiento[11];
    int telefono;
    char email[30];
} Usuario;

typedef struct
{
    Usuario *user;
    char domicilio[30];
} Cliente;
typedef struct
{
    char idProfesional[7];
    Usuario *user;
} Profesional;

typedef struct
{
    char iban[24];
    float saldo;
    char fechaCreacion[20];
    char dniPropietario[9];
} Cuenta;

typedef struct
{
    Cliente *cli;
    char idCompania[5];
    float valorCompra;
    int cantidad;
    char fechaCompra[20];
} Inversion;

typedef struct
{
    Cliente *cli;
    int idPres;
    float importe;
    char idProfesional[7];
    char fechaSoli[20];
    char fechaEmision[20];
    char fechaDevol[20];
    char fechaComp[20];
    float tae;

} Prestamo;

typedef struct
{
    int idTransaccion;
    char ibanOrigen[24];
    char ibanDestino[24];
    float importe;
    char fecha[20];
    char concepto[30];

} Movimiento;

#endif