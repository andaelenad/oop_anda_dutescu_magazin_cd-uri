#include "MAGAZIN.h"

Magazin::Magazin(const std::string& n) : nume(n) {}
Magazin::Magazin(const Magazin& other) : nume(other.nume), comenzi(other.comenzi) {}
Magazin& Magazin::operator=(const Magazin& other) {
    if (this != &other) {
        nume = other.nume;
        comenzi = other.comenzi;
    }
    return *this;
}

void Magazin::adaugaComanda(const Comanda& c) { comenzi.push_back(c); }

double Magazin::venitTotal() const {
    double total = 0;
    for (const auto& c : comenzi)
        total += c.calculeazaTotal();
    return total;
}

int Magazin::numarComenzi() const { return static_cast<int>(comenzi.size()); }

std::ostream& operator<<(std::ostream& os, const Magazin& m) {
    os << "Magazin: " << m.nume << "\n";
    for (const auto& c : m.comenzi)
        os << c << "\n";
    os << "Venit total: " << m.venitTotal() << " lei\n";
    return os;
}
