namespace containers
{
    class Cliente
    {
    private:
        const char *dni;
        const char *nombre;
        char *domicilio;
        char *email;
        const char *fecNac;
        unsigned int telf;

    public:
        Cliente();
        ~Cliente();
        char *getDni() const;
        char *getNombre() const;
        char *getDomicilio() const;
        char *getFecNac() const;
        void setDomicilio(char *domicilio);
        char *getEmail() const;
        void setEmail(char *email);
        unsigned int getTelf() const;
        void setTelf(unsigned int telf);
    };

    class Cuenta
    {
    private:
        const char *dniPropietario;
        const char *iban;
        float saldo;
        const char *fecCreacion;
        Movimiento[] movimientos;

    public:
        Cuenta();
        ~Cuenta();
        char *getDni() const;
        char *getIban() const;
        float getSaldo() const;
        void setSaldo(floar saldo);
        char *getFecCreacion() const;
        Movimiento[] getMovimientos() const;
        void setMovimientos(Movimiento mov);
    };

    class Movimiento
    {
    private:
        unsigned int idMovimiento;
        char *ibanOrigen;
        char *ibanDestino;
        float importe;
        char *fecha;
        char *concepto;

    public:
        Movimiento();
        ~Movimiento();
    };

};