//
// Created by Anda on 11/2/2025.
//

#ifndef MAGAZINCDURI_ADRESA_H
#define MAGAZINCDURI_ADRESA_H

#include <string>
#include <ostream>

class Adresa {
private:
    std::string strada;
    std::string numar;
    // Poti adauga oras, cod postal etc.
public:
    Adresa(const std::string& s = "", const std::string& n = "");
    // Adaugam si regula celor 5 pe Adresa, chiar daca nu e obligatoriu pe doua clase
    Adresa(const Adresa& other) = default;
    Adresa& operator=(const Adresa& other) = default;
    ~Adresa() = default;

    // Functii de get simple
    const std::string& getStrada() const { return strada; }
    const std::string& getNumar() const { return numar; }

    friend std::ostream& operator<<(std::ostream& os, const Adresa& a);
};

#endif