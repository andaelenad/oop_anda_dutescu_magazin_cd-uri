#include "CASETA.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <memory>
#include <algorithm>

Caseta::Caseta(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, const std::string& tip_banda)
    : ProdusMuzical(titlu, artist, an_aparitie, gen, pret), tip_banda(tip_banda) {}

Caseta::Caseta(const Caseta& other)
    : ProdusMuzical(other), tip_banda(other.tip_banda) {}


void swap(Caseta& first, Caseta& second) {
    using std::swap;

    swap(static_cast<ProdusMuzical&>(first), static_cast<ProdusMuzical&>(second));


    swap(first.tip_banda, second.tip_banda);
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
    os << "Tip: Caseta | Banda: " << tip_banda << "\n";
}