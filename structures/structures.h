#ifndef structures.h
#define structurres.h

typedef struct{
    char dni[10];
    char contrasenya[11];
    char nombreApellidos[30];
    char fechaNacimiento[11];
    int telefono;
    char email[30];
} Usuario;

typedef struct{
    Usuario user;
    char domicilio[30];
} Cliente;
typedef struct{
    Usuario user;
    char idProfesional[7];
} Profesional;

#endif