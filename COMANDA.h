
#ifndef COMANDA_H
#define COMANDA_H

#include "CLIENT.h"
#include "COS_CUMPARATURI.h" // Essential: Foloseste cosul polimorfic
#include <ostream>
#include <vector>

class Comanda {
private:
    Client client;
    CosCumparaturi cos; // se duce pe CosCumparaturi

public:
    Comanda(const Client& c, CosCumparaturi c_data);
    ~Comanda() = default;


    Comanda(const Comanda& other);
    Comanda& operator=(Comanda other);

    double calculeazaTotalCuTaxe() const;
    int numarProduse() const;

    const Client& getClient() const;
    const CosCumparaturi& getCos() const { return cos; }
    CosCumparaturi& getCos() { return cos; }

    friend std::ostream& operator<<(std::ostream& os, const Comanda& com);
};

#endif


