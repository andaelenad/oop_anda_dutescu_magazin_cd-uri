#include "VINIL.h"
#include <iomanip>
#include <utility>
#include <memory>
#include <algorithm>
#include "EroriMuzicale.h"

Vinil::Vinil(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, int rpm)
    : ProdusMuzical(titlu, artist, an_aparitie, gen, pret), rpm(rpm) {
    if (rpm != 33 && rpm != 45 && rpm != 78) {
        throw EroareFormatNecunoscut("RPM invalid pentru Vinil: " + std::to_string(rpm));
    }
}

Vinil::Vinil(const Vinil& other) : ProdusMuzical(other), rpm(other.rpm) {}

double Vinil::calculeazaTaxa() const {
    return this->getPret() * 0.10 + 5.0;
}

std::unique_ptr<ProdusMuzical> Vinil::clone() const {
    return std::make_unique<Vinil>(*this);
}

void Vinil::afiseazaDetalii(std::ostream& os) const {
    os << "Tip: Vinil | RPM: " << rpm << "\n";
}

void swap(Vinil& first, Vinil& second) {
    using std::swap;
    swap(static_cast<ProdusMuzical&>(first), static_cast<ProdusMuzical&>(second));
    swap(first.rpm, second.rpm);
}

Vinil& Vinil::operator=(Vinil other) {
    swap(*this, other);
    return *this;
}