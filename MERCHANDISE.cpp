#include "MERCHANDISE.h"
#include <iomanip>
#include <utility>
#include <algorithm>

void swap(Merchandise& first, Merchandise& second) {
    using std::swap;

    swap(first.culoare, second.culoare);
    swap(first.material, second.material);
}


Merchandise::Merchandise(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret,
                         const std::string& culoare, const std::string& material)
    : ProdusMuzical(titlu, artist, an_aparitie, gen, pret), culoare(culoare), material(material) {}


// taxa merchandise (taxa fixa + 5% pentru material premium)
double Merchandise::calculeazaTaxa() const {
    double taxa = 8.0; // taxa
    if (estePremium()) {
        taxa += this->getPret() * 0.05; // 5% taxa suplimentara pentru material premium
    }
    return taxa;
}


bool Merchandise::estePremium() const {
//lana , piele sunt considerate premium
    return (material == "Lana" || material == "Piele");
}



void Merchandise::afiseazaDetalii(std::ostream& os) const {
    os << "Tip: Merchandise (" << material << ")\n";
    os << "  Titlu: " << this->getTitlu() << " | Artist: " << this->getArtist()
       << " | An: " << this->getAnAparitie() << " | Gen: " << this->getGen()
       << "\n  Culoare: " << culoare << " | Material: " << material
       << " | Taxa: " << calculeazaTaxa() << " RON";
}


ProdusMuzical* Merchandise::clone() const {
    return new Merchandise(*this);
}


Merchandise::Merchandise(const Merchandise& other)
    : ProdusMuzical(other), culoare(other.culoare), material(other.material) {}


Merchandise& Merchandise::operator=(Merchandise other) {
    swap(*this, other);
    return *this;
}