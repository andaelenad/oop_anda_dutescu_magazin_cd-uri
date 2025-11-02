#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <ostream>
#include "ADRESA.h"

class Client {
private:
    std::string nume;
    Adresa adresa;
    std::string email;

public:
    Client(const std::string& n, const Adresa& a, const std::string& e = "");

    Client(const Client& other);
    Client& operator=(const Client& other);
    ~Client() = default;

    const std::string& getNume() const;
    const Adresa& getAdresa() const;
    const std::string& getEmail() const;

    friend std::ostream& operator<<(std::ostream& os, const Client& c);
};

#endif
