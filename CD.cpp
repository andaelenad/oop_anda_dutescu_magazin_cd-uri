#include "CD.h"

CD::CD(const std::string& n, const std::string& a, double p) : nume(n), artist(a), pret(p) {}

CD::CD(const CD& other) : nume(other.nume), artist(other.artist), pret(other.pret) {}

CD& CD::operator=(const CD& other) {
    if (this != &other) {
        nume = other.nume;
        artist = other.artist;
        pret = other.pret;
    }
    return *this;
}

double CD::getPret() const { return pret; }
const std::string& CD::getNume() const { return nume; }
const std::string& CD::getArtist() const { return artist; }

std::ostream& operator<<(std::ostream& os, const CD& cd) {
    os << cd.nume << " - " << cd.artist << " (" << cd.pret << " lei)";
    return os;
}
