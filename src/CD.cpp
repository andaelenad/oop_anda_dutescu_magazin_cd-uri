#include "CD.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <memory>

CD::CD(const std::string &titlu, const std::string &artist, int anAparitie, const std::string &gen, double pret,
       int nrPiese)
    : ProdusMuzical(titlu, artist, anAparitie, gen, pret), nrPiese(nrPiese) {
}

CD::CD(const CD &other)
    : ProdusMuzical(other), nrPiese(other.nrPiese) {
}

void swap(CD &first, CD &second) {
    using std::swap;

    swap(static_cast<ProdusMuzical &>(first), static_cast<ProdusMuzical &>(second));


    swap(first.nrPiese, second.nrPiese);
}

CD &CD::operator=(CD other) {
    swap(*this, other);
    return *this;
}


std::unique_ptr<ProdusMuzical> CD::clone() const {
    return std::make_unique<CD>(*this);
}

double CD::calculeazaTaxa() const {
    return getPret() * 0.05; // Taxa 5%
}

void CD::afiseazaDetalii(std::ostream &os) const {
    os << "Tip: CD | Piese: " << nrPiese;
}
