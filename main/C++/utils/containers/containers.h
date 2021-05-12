#include <string>
#include <iostream>
#include "../../../C/utils/structures.h"

#ifndef CONTAINERS
#define CONTAINERS

using namespace std;
namespace containers
{
    class ClienteCpp
    {
    private:
        string dni;
        string nombre;
        string domicilio;
        string email;
        string fecNac;
        unsigned int telf;

    public:
        ClienteCpp(string dni, string nombre, string domicilio, string fecNac, string email, unsigned int telf);
        ClienteCpp(Cliente *cli);
        ~ClienteCpp();
        string getDni() const;
        string getNombre() const;
        string getDomicilio() const;
        string getFecNac() const;
        void setDomicilio(string domicilio);
        string getEmail() const;
        void setEmail(string email);
        unsigned int getTelf() const;
        void setTelf(unsigned int telf);
    };

    class Movimiento
    {
    private:
        unsigned int idMovimiento;
        string ibanOrigen;
        string ibanDestino;
        float importe;
        string fecha;
        string concepto;

    public:
        Movimiento(unsigned int idMovimiento, string ibanOrigen, string ibanDestino, float importe, string fecha, string concepto);
        ~Movimiento();
        void setIdMovimiento(unsigned int idMovimiento);
        unsigned int getIdMovimiento() const;
        void setIbanOrigen(string ibanOrigen);
        string getIbanOrigen() const;
        void setIbanDestino(string ibanDestino);
        string getIbanDestino() const;
        void setImporte(float importe);
        float getImporte() const;
        void setFecha(string fecha);
        string getFecha() const;
        void setConcepto(string concepto);
        string getConcepto() const;
    };

    class CuentaCpp
    {
    private:
        string dniPropietario;
        string iban;
        float saldo;
        string fecCreacion;
        Movimiento *movimientos;

    public:
        CuentaCpp(string dniPropietario, string iban, float saldo, string fecCreacion, Movimiento *movimientos);
        CuentaCpp(string dniPropietario, string iban, float saldo, string fecCreacion); //constructor sin movimientos, para cuando se leen solo las CuentaCpps
        ~CuentaCpp();
        string getDni() const;
        string getIban() const;
        float getSaldo() const;
        void setSaldo(float saldo);
        string getFecCreacion() const;
        Movimiento *getMovimientos() const;
        void setMovimientos(Movimiento *mov);
    };

    class Inversion
    {
    private:
        char *idCompania;
        float valorCompra;
        int cantidad;
        char *fechaCompra;

    public:
        Inversion();
        Inversion(const Inversion &o);
        Inversion(char *idCompania, float valorCompra, int cantidad, char *fechaCompra);
        ~Inversion();
        char *getIdCompania() const;
        float getValorCompra() const;
        int getCantidad() const;
        char *getFechaCompra() const;
    };

    class Inversiones
    {
    private:
        int count;
        Inversion *inversiones;

    public:
        Inversiones(int count);
        ~Inversiones();
        Inversion *getInversiones() const;
        void setInversion(unsigned int index, Inversion *inversion);
        int getCount() const;
    };

};

#endif