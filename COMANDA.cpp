#include "COMANDA.h"
#include <iostream>
#include <iomanip>
#include <utility>

Comanda::Comanda(const Client& c, CosCumparaturi c_data)
    : client(c), cos(std::move(c_data)) {}

Comanda::Comanda(const Comanda& other)
    : client(other.client), cos(other.cos) {}

Comanda& Comanda::operator=(Comanda other) {
    std::swap(client, other.client);
    std::swap(cos, other.cos);
    return *this;
}

double Comanda::calculeazaTotalCuTaxe() const {
    return cos.calculeazaTotalComanda(); // polimorfism pe CosCumparaturi
}

int Comanda::numarProduse() const {
    return cos.produse.size();
}

const Client& Comanda::getClient() const {
    return client;
}

std::ostream& operator<<(std::ostream& os, const Comanda& com) {
    os << "--- Detalii Comanda ---\n";
    os << com.client;
    os << "\n  Produse (Total " << com.numarProduse() << " articole):\n";

    for (const auto& p : com.cos.produse) {
        p->afiseaza(); // polimorfie
    }

    os << "  TOTAL FINAL (inclusiv taxe): " << std::fixed << std::setprecision(2) << com.calculeazaTotalCuTaxe() << " RON\n";
    return os;
}