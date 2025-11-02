#include "CLIENT.h"
#include <iostream>

// Constructor de inițializare (REZOLVĂ EROAREA TA DE COMPILARE)
Client::Client(const std::string& n, const Adresa& a, const std::string& e)
    : nume(n), adresa(a), email(e) {}

// Constructor de copiere (pentru cerința profesorului)
Client::Client(const Client& other)
    : nume(other.nume), adresa(other.adresa), email(other.email) {}

// Operator= (pentru cerința profesorului)
Client& Client::operator=(const Client& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->adresa = other.adresa;
        this->email = other.email;
    }
    return *this;
}

// Funcții get cu const
const std::string& Client::getNume() const { return nume; }
const Adresa& Client::getAdresa() const { return adresa; }
const std::string& Client::getEmail() const { return email; }

// Operator<< (folosește compunere de apeluri)
std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << "Client: " << c.nume << "\n";
    os << "  Adresa: " << c.adresa << "\n"; // Compunere de apeluri: apelează Adresa::operator<<
    os << "  Email: " << c.email;
    return os;
}


