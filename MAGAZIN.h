#ifndef MAGAZIN_H
#define MAGAZIN_H

#include "COMANDA.h"
#include <vector>
#include <ostream>
#include <string>

class Magazin {
private:
    std::string nume;
    std::vector<Comanda> comenzi;

public:
    Magazin(const std::string& n);
    Magazin(const Magazin& other);
    Magazin& operator=(const Magazin& other);
    ~Magazin() = default;

    void adaugaComanda(const Comanda& c);
    double venitTotal() const;
    int numarComenzi() const;

    // functiile complexe
    void raportClientiTop(int topN) const;
    std::vector<Comanda> filtreazaComenziDupaArtist(const std::string& artistCautat) const;

    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);
};

#endif
