#ifndef COS_CUMPARATURI_H
#define COS_CUMPARATURI_H

#include "ProdusMuzical.h"
#include <vector>
#include <memory>
#include <utility>

class CosCumparaturi {
public:
    std::vector<std::unique_ptr<ProdusMuzical>> produse;

public:
    CosCumparaturi() = default;
    ~CosCumparaturi() = default;

    void adaugaProdus(std::unique_ptr<ProdusMuzical> p);
    double calculeazaTotalComanda() const;
    void afiseazaDoarViniluri() const;

    CosCumparaturi(const CosCumparaturi& other);
    CosCumparaturi& operator=(CosCumparaturi other);
};

#endif // COS_CUMPARATURI_H