#include "COMANDA.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <memory>

Comanda::Comanda(const Client& c, CosCumparaturi c_data)
    : client(c), cos(std::move(c_data)) {}

Comanda::Comanda(const Comanda& other)
    : client(other.client), cos(other.cos) {}

Comanda& Comanda::operator=(Comanda other) {
    std::swap(client, other.client);
    std::swap(cos, other.cos);
    return *this;
}

void Comanda::afiseazaDetaliiComanda(std::ostream& os) const {
}

std::unique_ptr<Comanda> Comanda::clone() const {
    return std::make_unique<Comanda>(*this);
}

double Comanda::calculeazaTotalComanda() const {
    return cos.calculeazaTotalComanda();
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
        p->afiseaza();
    }

    com.afiseazaDetaliiComanda(os);

    os << "  TOTAL FINAL (inclusiv taxe): " << std::fixed << std::setprecision(2) << com.calculeazaTotalComanda() << " RON\n";
    return os;
}