#include "COS_CUMPARATURI.h"
#include "VINIL.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>

void CosCumparaturi::adaugaProdus(std::unique_ptr<ProdusMuzical> p) {
    if (p) {
        produse.push_back(std::move(p));
    }
}

double CosCumparaturi::calculeazaTotalComanda() const {
    double total = 0.0;
    for (const auto& p : produse) {
        total += p->getPret();
        total += p->calculeazaTaxa();
    }
    return total;
}

void CosCumparaturi::afiseazaDoarViniluri() const {
    std::cout << "--- Afisare Viniluri (Dynamic Cast) ---\n";
    for (const auto& p : produse) {
        if (const Vinil* v = dynamic_cast<const Vinil*>(p.get())) { {
            std::cout << "  [GASIT VINIL] ";
            v->afiseaza();
        }
        }
    }
}

CosCumparaturi::CosCumparaturi(const CosCumparaturi& other) {
    for (const auto& p : other.produse) {
        produse.push_back(std::unique_ptr<ProdusMuzical>(p->clone()));
    }
}

CosCumparaturi& CosCumparaturi::operator=(CosCumparaturi other) {
    std::swap(produse, other.produse);
    return *this;
}