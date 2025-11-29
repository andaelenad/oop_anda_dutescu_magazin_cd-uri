#include "CLIENT.h"
#include <iostream>
#include <utility>

Client::Client(const std::string& n, const std::string& e)
    : nume(n), email(e) {}

// GESTIUNE MEMORIE: Swap Helper
void swap(Client& first, Client& second) {
    using std::swap;
    swap(first.nume, second.nume);
    swap(first.email, second.email);
}


Client::Client(const Client& other)
    : nume(other.nume), email(other.email) {}


Client& Client::operator=(Client other) {
    swap(*this, other);
    return *this;
}

const std::string& Client::getNume() const { return nume; }
const std::string& Client::getEmail() const { return email; }

std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << "Client: " << c.getNume() << "\n";
    os << "  Email: " << c.getEmail();
    return os;
}

