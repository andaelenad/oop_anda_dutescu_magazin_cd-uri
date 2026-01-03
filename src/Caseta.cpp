#include "Caseta.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <memory>
#include <algorithm>

Caseta::Caseta(const std::string& titlu, const std::string& artist, int anAparitie, const std::string& gen, double pret, const std::string& tipBanda)
    : ProdusMuzical(titlu, artist, anAparitie, gen, pret), tipBanda(tipBanda) {}

Caseta::Caseta(const Caseta& other)
    : ProdusMuzical(other), tipBanda(other.tipBanda) {}


void swap(Caseta& first, Caseta& second) {
    using std::swap;

    swap(static_cast<ProdusMuzical&>(first), static_cast<ProdusMuzical&>(second));


    swap(first.tipBanda, second.tipBanda);
}

Caseta& Caseta::operator=(Caseta other) {
    swap(*this, other);
    return *this;
}

std::unique_ptr<ProdusMuzical> Caseta::clone() const {
    return std::make_unique<Caseta>(*this);
}

double Caseta::calculeazaTaxa() const {
    return getPret() * 0.10;
}

void Caseta::afiseazaDetalii(std::ostream& os) const {
    os << "Tip: Caseta | Banda: " << tipBanda << "\n";
}