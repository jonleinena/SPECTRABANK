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
    char iban[21];
    float saldo;
    char fechaCreacion[11];
    char dniPropietario[10];
} Cuenta;

#endif