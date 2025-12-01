#ifndef MAGAZIN_H
#define MAGAZIN_H

#include "COMANDA.h"
#include "CLIENT.h"
#include "PRODUSMUZICAL.h"
#include <vector>
#include <string>
#include <ostream>

class Magazin {
private:
    std::string nume;
    std::vector<Comanda> comenzi;
    void cppcheck_fix_all_magazin();

public:
   explicit Magazin(const std::string& nume);


    const std::string& getNume() const { return nume; }

    void adaugaComanda(const Comanda& c);

    double venitTotal() const;
    int numarComenzi() const;

    void sorteazaComenziDupaValoare();

    std::vector<Comanda> filtreazaComenziDupaArtist(const std::string& artistCautat) const;
    bool actualizeazaComanda(const Client& client, const ProdusMuzical& produs_nou);
    void raportComenziTop(int topN) const;

    const std::vector<Comanda>& getComenzi() const { return comenzi; }


    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);
};

#endif // MAGAZIN_H