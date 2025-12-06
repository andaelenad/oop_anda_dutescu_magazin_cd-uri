#include "COMANDALIVRARE.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>

ComandaLivrare::ComandaLivrare(const Client& client, CosCumparaturi cos,
                               const std::string& adresa, double costBaza, bool urgent)
    : Comanda(client, std::move(cos)),
      adresaLivrare(adresa),
      costBazaLivrare(costBaza),
      esteUrgenta(urgent)
{}

ComandaLivrare::ComandaLivrare(const ComandaLivrare& other)
    : Comanda(other),
      adresaLivrare(other.adresaLivrare),
      costBazaLivrare(other.costBazaLivrare),
      esteUrgenta(other.esteUrgenta)
{}

void swap(ComandaLivrare& first, ComandaLivrare& second) noexcept {
    using std::swap;
    swap(static_cast<Comanda&>(first), static_cast<Comanda&>(second));
    swap(first.adresaLivrare, second.adresaLivrare);
    swap(first.costBazaLivrare, second.costBazaLivrare);
    swap(first.esteUrgenta, second.esteUrgenta);
}

ComandaLivrare& ComandaLivrare::operator=(const ComandaLivrare& other) {
    if (this != &other) {
        ComandaLivrare temp = other;
        swap(*this, temp);
    }
    return *this;
}


std::unique_ptr<Comanda> ComandaLivrare::clone() const {
    return std::make_unique<ComandaLivrare>(*this);
}

double ComandaLivrare::calculeazaTotalComanda() const {
    double totalBaza = Comanda::calculeazaTotalComanda();

    double costFinalLivrare = costBazaLivrare;

    if (esteUrgenta) {
        costFinalLivrare *= 1.20;
    }

    return totalBaza + costFinalLivrare;
}

void ComandaLivrare::afiseazaDetaliiComanda(std::ostream& os) const {
    os << "\n--- DETALII LIVRARE ---\n";
    os << "  Adresa: " << adresaLivrare << "\n";
    os << "  Cost Livrare Baza: " << std::fixed << std::setprecision(2) << costBazaLivrare << " RON\n";
    os << "  Urgenta: " << (esteUrgenta ? "DA (+20% taxa)" : "NU") << "\n";

    double costFinalLivrare = this->calculeazaTotalComanda() - Comanda::calculeazaTotalComanda();

    os << "  Cost Final Livrare: " << std::fixed << std::setprecision(2)
       << costFinalLivrare << " RON\n";
    os << "-----------------------\n";
}