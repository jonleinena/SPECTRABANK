#include <string>
#include <iostream>
#include "../../../C/utils/structures.h"

#ifndef CONTAINERS
#define CONTAINERS

using namespace std;
namespace containers
{
    

    class MovimientoCpp
    {
    private:
        unsigned int idMovimiento;
        string ibanOrigen;
        string ibanDestino;
        float importe;
        string fecha;
        string concepto;

    public:
        MovimientoCpp(unsigned int idMovimiento, string ibanOrigen, string ibanDestino, float importe, string fecha, string concepto);
        MovimientoCpp(const MovimientoCpp &m);
        MovimientoCpp();
        MovimientoCpp(Movimiento *m);
        ~MovimientoCpp();
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
        MovimientoCpp *movimientos;

    public:
        CuentaCpp(string dniPropietario, string iban, float saldo, string fecCreacion, MovimientoCpp *movimientos);
        CuentaCpp(char *dniPropietario, char *iban, float saldo, char *fecCreacion); //constructor sin movimientos, para cuando se leen solo las CuentaCpps
        CuentaCpp(const CuentaCpp &c);
        CuentaCpp();
        ~CuentaCpp();
        string getDni() const;
        void setDni(string dni);
        string getIban() const;
        void setIban(string iban);
        float getSaldo() const;
        void setSaldo(float saldo);
        string getFecCreacion() const;
        void setFecCreacion(string fecCreacion);
        MovimientoCpp *getMovimientos() const;
        void setMovimientos(MovimientoCpp *mov);
    };
    class ClienteCpp
    {
    private:
        string dni;
        string nombre;
        string domicilio;
        string email;
        string fecNac;
        unsigned int telf;
        containers::CuentaCpp *cuentas;
        int numeroCuentas;

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
        void setCuenta(CuentaCpp &cue);
        containers::CuentaCpp *getCuentas();
        int getNumCuentas();
    };

    class InversionCpp
    {
    private:
        char *idCompania;
        float valorCompra;
        int cantidad;
        char *fechaCompra;

    public:
        InversionCpp();
        InversionCpp(const InversionCpp &o);
        InversionCpp(char *idCompania, float valorCompra, int cantidad, char *fechaCompra);
        ~InversionCpp();
        char *getIdCompania() const;
        float getValorCompra() const;
        int getCantidad() const;
        char *getFechaCompra() const;
    };

    class Inversiones
    {
    private:
        int count;
        InversionCpp *inversiones;

    public:
        Inversiones(int count);
        ~Inversiones();
        InversionCpp *getInversiones() const;
        void setInversionCpp(unsigned int index, InversionCpp *InversionCpp);
        int getCount() const;
    };

};

#endif