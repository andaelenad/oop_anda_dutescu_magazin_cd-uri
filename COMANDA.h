#ifndef COMANDA_H
#define COMANDA_H

#include "CLIENT.h"
#include "COS_CUMPARATURI.h"
#include <ostream>
#include <vector>
#include <memory>

class Comanda {
private:
    Client client;
    CosCumparaturi cos;

protected:
    virtual void afiseazaDetaliiComanda(std::ostream& os) const;

public:
    Comanda(const Client& c, CosCumparaturi c_data);
    virtual ~Comanda() = default;

    Comanda(const Comanda& other);

    Comanda& operator=(Comanda other);

    virtual double calculeazaTotalComanda() const;

    virtual std::unique_ptr<Comanda> clone() const;

    int numarProduse() const;

    const Client& getClient() const;
    const CosCumparaturi& getCos() const { return cos; }
    CosCumparaturi& getCos() { return cos; }

    friend std::ostream& operator<<(std::ostream& os, const Comanda& com);
};

#endif


