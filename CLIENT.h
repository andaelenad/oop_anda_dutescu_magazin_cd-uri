#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <ostream>
#include "ADRESA.h" // NOU

class Client {
private:
    std::string nume;
    Adresa adresa; // FOLOSIM CLASA PROPRIE PENTRU COMPUNERE
    std::string email; // Email-ul poate ramane ca membru suplimentar

public:
    // Constructor de initializare cu parametri
    Client(const std::string& n, const Adresa& a, const std::string& e = "");

    // Regula celor 5 (pastram pe Client conform cerintei)
    Client(const Client& other);
    Client& operator=(const Client& other);
    ~Client() = default;

    const std::string& getNume() const;
    const Adresa& getAdresa() const; // Modificat
    const std::string& getEmail() const;

    friend std::ostream& operator<<(std::ostream& os, const Client& c);
};

#endif
