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
    explicit Magazin(const std::string& n);
    Magazin(const Magazin& other);
    Magazin& operator=(const Magazin& other);
    ~Magazin() = default;

    void adaugaComanda(const Comanda& c);
    double venitTotal() const;
    int numarComenzi() const;

    std::vector<Comanda>& getComenzi() { return comenzi; }
    const std::vector<Comanda>& getComenzi() const { return comenzi; }

    bool actualizeazaComanda(const Client& client, const CD& cd_nou);

    void raportClientiTop(int topN) const;
    std::vector<Comanda> filtreazaComenziDupaArtist(const std::string& artistCautat) const;

    void sorteazaComenziDupaValoare();
    std::string getTopArtist() const;

    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);
};

#endif