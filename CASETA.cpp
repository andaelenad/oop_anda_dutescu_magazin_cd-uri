#include "CASETA.h"
#include <iomanip>


Caseta::Caseta(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, const std::string& tip_banda)
    : ProdusMuzical(titlu, artist, an_aparitie, gen, pret), tip_banda(tip_banda) {}

// taxa Caseta (2%)
double Caseta::calculeazaTaxa() const {
    return this->getPret() * 0.02; // 2% taxa
}


void Caseta::afiseazaDetalii(std::ostream& os) const {
    os << "Tip: Caseta\n";
    os << "  Titlu: " << this->getTitlu() << " | Artist: " << this->getArtist()
       << " | An: " << this->getAnAparitie() << " | Gen: " << this->getGen()
       << "\n  Pret: " << std::fixed << std::setprecision(2) << this->getPret() << " RON"
       << " | Banda: " << tip_banda << " | Taxa: " << calculeazaTaxa() << " RON";
}

ProdusMuzical* Caseta::clone() const {
    return new Caseta(*this);
}


Caseta::Caseta(const Caseta& other) : ProdusMuzical(other), tip_banda(other.tip_banda) {}

Caseta& Caseta::operator=(Caseta other) {
    swap(*this, other);
    return *this;
}