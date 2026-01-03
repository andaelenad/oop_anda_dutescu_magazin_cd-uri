#include "CD.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <memory>

CD::CD(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, int nr_piese)
    : ProdusMuzical(titlu, artist, an_aparitie, gen, pret), nr_piese(nr_piese) {
}

CD::CD(const CD& other)
    : ProdusMuzical(other), nr_piese(other.nr_piese) {
}

void swap(CD& first, CD& second) {
    using std::swap;

    swap(static_cast<ProdusMuzical&>(first), static_cast<ProdusMuzical&>(second));


    swap(first.nr_piese, second.nr_piese);
}

CD& CD::operator=(CD other) {
    swap(*this, other);
    return *this;
}


std::unique_ptr<ProdusMuzical> CD::clone() const {
    return std::make_unique<CD>(*this);
}

double CD::calculeazaTaxa() const {
    return getPret() * 0.05; // Taxa 5%
}

void CD::afiseazaDetalii(std::ostream& os) const {
    os << "Tip: CD | Piese: " << nr_piese;
}