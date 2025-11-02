#include "ADRESA.h"
#include <iostream>
#include <string>

Adresa::Adresa(const std::string& s, const std::string& n)
    : strada(s), numar(n) {}

Adresa::Adresa(const Adresa& other)
    : strada(other.strada), numar(other.numar) {}

Adresa& Adresa::operator=(const Adresa& other) {
    if (this != &other) {
        this->strada = other.strada;
        this->numar = other.numar;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Adresa& a) {
    os << "Strada " << a.strada << " Nr. " << a.numar;
    return os;
}