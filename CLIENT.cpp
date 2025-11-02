#include "CLIENT.h"
#include <iostream>

Client::Client(const std::string& n, const std::string& e)
    : nume(n), email(e) {}

Client::Client(const Client& other)
    : nume(other.nume), email(other.email) {}

Client& Client::operator=(const Client& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->email = other.email;
    }
    return *this;
}

const std::string& Client::getNume() const { return nume; }

const std::string& Client::getEmail() const { return email; } // Lăsată așa

std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << "Client: " << c.getNume() << "\n";
    os << "  Email: " << c.getEmail();
    return os;
}

