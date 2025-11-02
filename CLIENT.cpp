#include "CLIENT.h"
#include <iostream>

Client::Client(const std::string& n, const Adresa& a, const std::string& e)
    : nume(n), adresa(a), email(e) {}

Client::Client(const Client& other)
    : nume(other.nume), adresa(other.adresa), email(other.email) {}

Client& Client::operator=(const Client& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->adresa = other.adresa;
        this->email = other.email;
    }
    return *this;
}

const std::string& Client::getNume() const { return nume; }
const Adresa& Client::getAdresa() const { return adresa; }
const std::string& Client::getEmail() const { return email; }

std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << "Client: " << c.nume << "\n";
    os << "  Adresa: " << c.adresa << "\n";
    os << "  Email: " << c.email;
    return os;
}


