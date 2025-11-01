#ifndef COMANDA_H
#define COMANDA_H

#include "CLIENT.h"
#include "CD.h"
#include <vector>
#include <ostream>

class Comanda {
private:
    Client client;
    std::vector<CD> cduri;

public:
    Comanda(const Client& c, const std::vector<CD>& cds);
    Comanda(const Comanda& other);
    Comanda& operator=(const Comanda& other);
    ~Comanda() = default;

    void adaugaCD(const CD& cd);
    double calculeazaTotal() const;
    int numarCDuri() const;

    const Client& getClient() const;
    const std::vector<CD>& getCDuri() const;

    friend std::ostream& operator<<(std::ostream& os, const Comanda& com);
};

#endif


