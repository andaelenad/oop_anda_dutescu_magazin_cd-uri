#include "COMANDA.h"
#include <iostream>
#include <iomanip>

Comanda::Comanda(const Client& c, const std::vector<CD>& cds)
    : client(c), cduri(cds) {}

Comanda::Comanda(const Comanda& other)
    : client(other.client), cduri(other.cduri) {}

Comanda& Comanda::operator=(const Comanda& other) {
    if (this != &other) {
        this->client = other.client;
        this->cduri = other.cduri;
    }
    return *this;
}

double Comanda::calculeazaTotal() const {
    double total = 0.0;
    for (const auto& cd : cduri) {
        total += cd.getPret();
    }
    return total;
}

void Comanda::adaugaCD(const CD& cd) {
    cduri.push_back(cd);
}

int Comanda::numarCDuri() const {
    return cduri.size();
}

const Client& Comanda::getClient() const {
    return client;
}

const std::vector<CD>& Comanda::getCDuri() const {
    return cduri;
}

std::ostream& operator<<(std::ostream& os, const Comanda& com) {
    os << "--- Detalii Comanda ---\n";
    os << com.client;
    os << "\n  Produse (Total " << com.numarCDuri() << "):\n";

    for (const auto& cd : com.cduri) {
        os << cd << "\n";
    }

    os << "  TOTAL COMANDA: " << std::fixed << std::setprecision(2) << com.calculeazaTotal() << " RON\n";
    return os;
}