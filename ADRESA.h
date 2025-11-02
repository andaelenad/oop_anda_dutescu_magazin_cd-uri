#ifndef ADRESA_H
#define ADRESA_H

#include <string>
#include <ostream>

class Adresa {
private:
    std::string strada;
    std::string numar;
public:
    Adresa(const std::string& s = "", const std::string& n = "");
    Adresa(const Adresa& other); // Declaratie simpla
    Adresa& operator=(const Adresa& other); // Declaratie simpla
    ~Adresa() = default;

    const std::string& getStrada() const { return strada; }
    const std::string& getNumar() const { return numar; }

    friend std::ostream& operator<<(std::ostream& os, const Adresa& a);
};

#endif