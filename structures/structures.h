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
    char fechaCreacion[11];
    char dniPropietario[10];
} Cuenta;

typedef struct
{
    Cliente *cli;
    char idCompania[5];
    float valorCompra;
    int cantidad;
    char fechaCompra[11];
} Inversion;

typedef struct
{
    Cliente *cli;
    int idPres;
    float importe;
    char idProfesional[7];
    char fechaEmision[11];
    char fechaDevol[11];
    char fechaComp[11];
    float tae;

} Prestamo;

typedef struct
{
    int idTransaccion;
    char ibanOrigen[24];
    char ibanDestino[24];
    float importe;
    char fecha[11];
    char concepto[30];

} Movimiento;

#endif