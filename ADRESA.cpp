//
// Created by Anda on 11/2/2025.
//

#include "ADRESA.h"
#include <iostream>

Adresa::Adresa(const std::string& s, const std::string& n)
    : strada(s), numar(n) {}

std::ostream& operator<<(std::ostream& os, const Adresa& a) {
    os << a.strada << " Nr. " << a.numar;
    return os;
}