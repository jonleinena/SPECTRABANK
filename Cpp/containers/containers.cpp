#include "containers.h"
#include "../../C/utils/structures.h"
#include <string>
#include <iostream>

using namespace containers;
using namespace std;

//ClienteCpp
ClienteCpp::ClienteCpp(string dni, string nombre, string domicilio, string fecNac, string email, unsigned int telf)
{
    this->dni = dni;
    this->nombre = nombre;
    this->domicilio = domicilio;
    this->fecNac = fecNac;
    this->email = email;
    this->telf = telf;
}
ClienteCpp::ClienteCpp(Cliente *cli)
{
    this->dni = string(cli->user->dni);
    this->nombre = string(cli->user->nombreApellidos);
    this->domicilio = string(cli->domicilio);
    this->email = string(cli->user->email);
    this->fecNac = string(cli->user->fechaNacimiento);
    this->telf = cli->user->telf;
}
ClienteCpp::~ClienteCpp()
{
}
string ClienteCpp::getDni() const
{
    return this->dni;
}
string ClienteCpp::getNombre() const
{
    return this->nombre;
}
string ClienteCpp::getDomicilio() const
{
    return this->domicilio;
}
string ClienteCpp::getFecNac() const
{
    return this->fecNac;
}
void ClienteCpp::setDomicilio(string domicilio)
{
    this->domicilio = domicilio;
}
string ClienteCpp::getEmail() const
{
    return this->email;
}
void ClienteCpp::setEmail(string email)
{
    this->email = email;
}
unsigned int ClienteCpp::getTelf() const
{
    return this->telf;
}
void ClienteCpp::setTelf(unsigned int telf)
{
    this->telf = telf;
}

//Cuenta
Cuenta::Cuenta(string dniPropietario, string iban, float saldo, string fecCreacion, Movimiento *movimientos)
{
    this->dniPropietario = dniPropietario : this->iban = iban;
    this->saldo = saldo;
    this->fecCreacion = fecCreacion;
    this->movimientos = movimientos;
}
Cuenta::~Cuenta()
{
    delete[] movimientos;
}
string Cuenta::getDni() const
{
    return this->dni;
}
string Cuenta::getIban() const
{
    return this->iban;
}
float Cuenta::getSaldo() const
{
    return this->saldo;
}
void Cuenta::setSaldo(float saldo)
{
    this->saldo = saldo;
}
string Cuenta::getFecCreacion() const
{
    return this->fecCreacion;
}
Movimiento *Cuenta::getMovimientos() const
{
    return this->movimientos;
}
void Cuenta::setMovimientos(Movimiento *mov)
{
    this->movimientos = mov;
}

//Movimiento
Movimiento::Movimiento(unsigned int idMovimiento, string ibanOrigen, string ibanDestino, float importe, string fecha, string concepto)
{
    this->idMovimiento = idMovimiento;
    this->ibanOrigen = ibanOrigen;
    this->ibanDestino = ibanDestino;
    this->importe = importe;
    this->fecha = fecha;
    this->concepto = concepto;
}
Movimiento::~Movimiento()
{
}
void Movimiento::setIdMovimiento(unsigned int idMovimiento)
{
    this->idMovimiento = idMovimiento;
}
unsigned int Movimiento::getIdMovimiento() const
{
    return this->idMovimiento;
}
void Movimiento::setIbanOrigen(string ibanOrigen)
{
    this->ibanOrigen = ibanOrigen;
}
string Movimiento::getIbanOrigen() const
{
    return this->ibanOrigen;
}
void Movimiento::setIbanDestino(string ibanDestino)
{
    this->ibanDestino = ibanDestino;
}
string Movimiento::getIbanDestino() const
{
    return this->ibanDestino;
}
void Movimiento::setImporte(float importe)
{
    this->importe = importe;
}
float Movimiento::getImporte() const
{
    return this->importe;
}
void Movimiento::setFecha(string fecha)
{
    this->fecha = fecha;
}
string Movimiento::getFecha() const
{
    return this->fecha;
}
void Movimiento::setConcepto(string concepto)
{
    this->concepto = concepto;
}
string Movimiento::getConcepto() const
{
    return this->concepto;
}