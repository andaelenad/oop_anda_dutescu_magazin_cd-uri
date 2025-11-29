#include "VINIL.h"
#include <iomanip>
#include "EroriMuzicale.h"

// constructor derivat care apeleaza constructorul de baza
Vinil::Vinil(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, int rpm)
    : ProdusMuzical(titlu, artist, an_aparitie, gen, pret), rpm(rpm) {
    if (rpm != 33 && rpm != 45 && rpm != 78) {
        throw EroareFormatNecunoscut("RPM invalid pentru Vinil: " + std::to_string(rpm));
    }
}

// taxa Vinil (10% + taxa fixa)
double Vinil::calculeazaTaxa() const {
    return this->getPret() * 0.10 + 5.0; // 10% + taxa fixa 5 RON
}


void Vinil::afiseazaDetalii(std::ostream& os) const {
    os << "Tip: Vinil (Disponibil in stoc)\n";
    os << "  Titlu: " << this->getTitlu() << " | Artist: " << this->getArtist()
       << " | An: " << this->getAnAparitie() << " | Gen: " << this->getGen()
       << "\n  Pret: " << std::fixed << std::setprecision(2) << this->getPret() << " RON"
       << " | RPM: " << rpm << " | Taxa: " << calculeazaTaxa() << " RON";
}

ProdusMuzical* Vinil::clone() const {
    return new Vinil(*this);
}

Vinil::Vinil(const Vinil& other) : ProdusMuzical(other), rpm(other.rpm) {}

Vinil& Vinil::operator=(Vinil other) {
    swap(*this, other);
    return *this;
}