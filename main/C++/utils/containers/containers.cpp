#include "containers.h"
#include <string>
#include <iostream>
#include "../../../C/utils/structures.h"
#include <stdlib.h>

using namespace std;

//ClienteCpp
containers::ClienteCpp::ClienteCpp(string dni, string nombre, string domicilio, string fecNac, string email, unsigned int telf)
{
    this->dni = dni;
    this->nombre = nombre;
    this->domicilio = domicilio;
    this->fecNac = fecNac;
    this->email = email;
    this->telf = telf;
}
containers::ClienteCpp::ClienteCpp(Cliente *cli)
{
    this->dni = string(cli->user->dni);
    this->nombre = string(cli->user->nombreApellidos);
    this->domicilio = string(cli->domicilio);
    this->email = string(cli->user->email);
    this->fecNac = string(cli->user->fechaNacimiento);
    this->telf = cli->user->telefono;
}
containers::ClienteCpp::~ClienteCpp()
{
}
string containers::ClienteCpp::getDni() const
{
    return this->dni;
}
string containers::ClienteCpp::getNombre() const
{
    return this->nombre;
}
string containers::ClienteCpp::getDomicilio() const
{
    return this->domicilio;
}
string containers::ClienteCpp::getFecNac() const
{
    return this->fecNac;
}
void containers::ClienteCpp::setDomicilio(string domicilio)
{
    this->domicilio = domicilio;
}
string containers::ClienteCpp::getEmail() const
{
    return this->email;
}
void containers::ClienteCpp::setEmail(string email)
{
    this->email = email;
}
unsigned int containers::ClienteCpp::getTelf() const
{
    return this->telf;
}
void containers::ClienteCpp::setTelf(unsigned int telf)
{
    this->telf = telf;
}

//CuentaCpp
containers::CuentaCpp::CuentaCpp(string dniPropietario, string iban, float saldo, string fecCreacion, Movimiento *movimientos)
{
    this->dniPropietario = dniPropietario;
    this->iban = iban;
    this->saldo = saldo;
    this->fecCreacion = fecCreacion;
    this->movimientos = movimientos;
}
containers::CuentaCpp::CuentaCpp(string dniPropietario, string iban, float saldo, string fecCreacion)
{
    this->dniPropietario = dniPropietario;
    this->iban = iban;
    this->saldo = saldo;
    this->fecCreacion = fecCreacion;
}
containers::CuentaCpp::~CuentaCpp()
{
    delete[] movimientos;
}
string containers::CuentaCpp::getDni() const
{
    return this->dniPropietario;
}
string containers::CuentaCpp::getIban() const
{
    return this->iban;
}
float containers::CuentaCpp::getSaldo() const
{
    return this->saldo;
}
void containers::CuentaCpp::setSaldo(float saldo)
{
    this->saldo = saldo;
}
string containers::CuentaCpp::getFecCreacion() const
{
    return this->fecCreacion;
}
containers::Movimiento *containers::CuentaCpp::getMovimientos() const
{
    return this->movimientos;
}
void containers::CuentaCpp::setMovimientos(containers::Movimiento *mov)
{
    this->movimientos = mov;
}

//Movimiento
containers::Movimiento::Movimiento(unsigned int idMovimiento, string ibanOrigen, string ibanDestino, float importe, string fecha, string concepto)
{
    this->idMovimiento = idMovimiento;
    this->ibanOrigen = ibanOrigen;
    this->ibanDestino = ibanDestino;
    this->importe = importe;
    this->fecha = fecha;
    this->concepto = concepto;
}
containers::Movimiento::~Movimiento()
{
}
void containers::Movimiento::setIdMovimiento(unsigned int idMovimiento)
{
    this->idMovimiento = idMovimiento;
}
unsigned int containers::Movimiento::getIdMovimiento() const
{
    return this->idMovimiento;
}
void containers::Movimiento::setIbanOrigen(string ibanOrigen)
{
    this->ibanOrigen = ibanOrigen;
}
string containers::Movimiento::getIbanOrigen() const
{
    return this->ibanOrigen;
}
void containers::Movimiento::setIbanDestino(string ibanDestino)
{
    this->ibanDestino = ibanDestino;
}
string containers::Movimiento::getIbanDestino() const
{
    return this->ibanDestino;
}
void containers::Movimiento::setImporte(float importe)
{
    this->importe = importe;
}
float containers::Movimiento::getImporte() const
{
    return this->importe;
}
void containers::Movimiento::setFecha(string fecha)
{
    this->fecha = fecha;
}
string containers::Movimiento::getFecha() const
{
    return this->fecha;
}
void containers::Movimiento::setConcepto(string concepto)
{
    this->concepto = concepto;
}
string containers::Movimiento::getConcepto() const
{
    return this->concepto;
}

//Inversion
containers::Inversion::Inversion()
{
    this->idCompania = NULL;
    this->valorCompra = 0;
    this->cantidad = 0;
    this->fechaCompra = NULL;
}
containers::Inversion::Inversion(const containers::Inversion &o)
{
    this->idCompania = o.getIdCompania();
    this->valorCompra = o.getValorCompra();
    this->cantidad = o.getCantidad();
    this->fechaCompra = o.getFechaCompra();
}
containers::Inversion::Inversion(char *idCompania, float valorCompra, int cantidad, char *fechaCompra)
{
    this->idCompania = idCompania;
    this->valorCompra = valorCompra;
    this->cantidad = cantidad;
    this->fechaCompra = fechaCompra;
}
containers::Inversion::~Inversion()
{
    delete idCompania;
    delete fechaCompra;
}
char *containers::Inversion::getIdCompania() const
{
    return this->idCompania;
}
float containers::Inversion::getValorCompra() const
{
    return this->valorCompra;
}
int containers::Inversion::getCantidad() const
{
    return this->cantidad;
}
char *containers::Inversion::getFechaCompra() const
{
    return this->fechaCompra;
}

//Inversiones
containers::Inversiones::Inversiones(int count)
{
    this->count = count;
    this->inversiones = new containers::Inversion[this->count];
}
containers::Inversiones::~Inversiones()
{
    for (int i = 0; i < this->count; i++)
    {
        delete (this->inversiones + i);
    }
}

containers::Inversion *containers::Inversiones::getInversiones() const
{
    return inversiones;
}
void containers::Inversiones::setInversion(unsigned int index, containers::Inversion *inversion)
{
    this->inversiones[index] = *inversion;
}
int containers::Inversiones::getCount() const
{
    return this->count;
}