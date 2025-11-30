#include "MERCHANDISE.h"
#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>

Merchandise::Merchandise(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret,
                         const std::string& culoare, const std::string& material)
    : ProdusMuzical(titlu, artist, an_aparitie, gen, pret), culoare(culoare), material(material) {}

Merchandise::Merchandise(const Merchandise& other)
    : ProdusMuzical(other), culoare(other.culoare), material(other.material) {}

std::unique_ptr<ProdusMuzical> Merchandise::clone() const {
    return std::make_unique<Merchandise>(*this);
}

double Merchandise::calculeazaTaxa() const {
    return 8.0;
}

void Merchandise::afiseazaDetalii(std::ostream& os) const {
    os << "Tip: Merchandise | Culoare: " << culoare << " | Material: " << material << "\n";
}

bool Merchandise::estePremium() const {
    return getPret() > 150.0 && material == "Bumbac";
}

void swap(Merchandise& first, Merchandise& second) {
    using std::swap;
    swap(static_cast<ProdusMuzical&>(first), static_cast<ProdusMuzical&>(second));
    swap(first.culoare, second.culoare);
    swap(first.material, second.material);
}

Merchandise& Merchandise::operator=(Merchandise other) {
    swap(*this, other);
    return *this;
}