#include "COMANDA.h"

Comanda::Comanda(const Client& c, const std::vector<CD>& cds) : client(c), cduri(cds) {}
Comanda::Comanda(const Comanda& other) : client(other.client), cduri(other.cduri) {}

Comanda& Comanda::operator=(const Comanda& other) {
    if (this != &other) {
        client = other.client;
        cduri = other.cduri;
    }
    return *this;
}

void Comanda::adaugaCD(const CD& cd) { cduri.push_back(cd); }

double Comanda::calculeazaTotal() const {
    double total = 0;
    for (const auto& cd : cduri)
        total += cd.getPret();
    return total;
}

int Comanda::numarCDuri() const { return static_cast<int>(cduri.size()); }

const Client& Comanda::getClient() const { return client; }
const std::vector<CD>& Comanda::getCDuri() const { return cduri; }

std::ostream& operator<<(std::ostream& os, const Comanda& com) {
    os << "Comanda pentru: " << com.client << "\nCD-uri:\n";
    for (const auto& cd : com.cduri)
        os << "  " << cd << "\n";
    os << "Total: " << com.calculeazaTotal() << " lei\n";
    return os;
}
