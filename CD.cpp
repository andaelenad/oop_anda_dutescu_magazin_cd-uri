#include "CD.h"
#include <iostream>
#include <iomanip>

CD::CD(const std::string& n, const std::string& a, double p)
    : nume(n), artist(a), pret(p) {}

CD::CD(const CD& other)
    : nume(other.nume), artist(other.artist), pret(other.pret) {}

CD& CD::operator=(const CD& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->artist = other.artist;
        this->pret = other.pret;
    }
    return *this;
}

double CD::getPret() const {
    return pret;
}

const std::string& CD::getNume() const {
    return nume;
}

const std::string& CD::getArtist() const {
    return artist;
}

std::ostream& operator<<(std::ostream& os, const CD& cd) {
    os << "  -> Album: " << cd.nume
       << " | Artist: " << cd.artist
       << " | Pret: " << std::fixed << std::setprecision(2) << cd.pret << " RON";
    return os;
}