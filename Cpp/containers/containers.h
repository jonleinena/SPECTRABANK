#include <string>
#include <iostream>
#include "../../C/utils/structures.h"

#ifndef CONTAINERS
#define CONTAINERS

using namespace std;
namespace containers
{
    class ClienteCpp
    {
    private:
        const string dni;
        const string nombre;
        string domicilio;
        string email;
        const string fecNac;
        unsigned int telf;

    public:
        ClienteCpp(string dni, string nombre, string domicilio, string fecNac, string email, unsigned int telf);
        ClienteCpp(Cliente cli);
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

    class Cuenta
    {
    private:
        const string dniPropietario;
        const string iban;
        float saldo;
        const string fecCreacion;
        Movimiento *movimientos;

    public:
        Cuenta(string dniPropietario, string iban, float saldo, string fecCreacion, Movimiento *movimientos);
        ~Cuenta();
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
        const char *idCompania;
        const float valorCompra;
        const int cantidad;
        const char *fechaCompra;

    public:
        Inversion(const char *idCompania, float valorCompra, int cantidad, const char *fechaCompra);
        ~Inversion();
        const char *getIdCompania() const;
        const float getValorCompra() const;
        const int getCantidad() const;
        const char *getFechaCompra() const;
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
        void setInversion(int index, Inversion *inversion);
        int getCount() const;
    };

};

#endif