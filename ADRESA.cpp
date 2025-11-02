#include "ADRESA.h"
#include <iostream>
#include <string>

Adresa::Adresa(const std::string& s, const std::string& n)
    : strada(s), numar(n) {}

std::ostream& operator<<(std::ostream& os, const Adresa& a) {
    os << "Strada " << a.strada << " Nr. " << a.numar;
    return os;
}