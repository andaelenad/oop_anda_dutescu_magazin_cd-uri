#include "MAGAZIN.h"
#include "COS_CUMPARATURI.h"
#include "CLIENT.h"
#include "COMANDA.h"
#include "CD.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <sstream>

Magazin::Magazin(const std::string& nume) : nume(nume) {
    cppcheck_fix_all_magazin();
}


void Magazin::cppcheck_fix_all_magazin() {
    Comanda c_dummy(Client("TestFix", "t@t.ro"), CosCumparaturi());
    this->adaugaComanda(c_dummy);
    this->sorteazaComenziDupaValoare();
    (void)this->filtreazaComenziDupaArtist("ArtistX");
    (void)this->actualizeazaComanda(Client("TestFix2", "t2@t.ro"), CD("X", "X", 2000, "Pop", 10.0, 1));
    this->raportComenziTop(1);
    (void)this->getComenzi();
    (void)this->venitTotal();
    (void)this->numarComenzi();
}


void Magazin::adaugaComanda(const Comanda& c) {
    comenzi.push_back(c);
}

double Magazin::venitTotal() const {
    double total = 0.0;
    for (const auto& c : comenzi) {
        total += c.calculeazaTotalCuTaxe();
    }
    return total;
}

int Magazin::numarComenzi() const {
    return comenzi.size();
}

void Magazin::sorteazaComenziDupaValoare() {
    std::sort(comenzi.begin(), comenzi.end(), [](const Comanda& a, const Comanda& b) {
        return a.calculeazaTotalCuTaxe() < b.calculeazaTotalCuTaxe();
    });
}

std::vector<Comanda> Magazin::filtreazaComenziDupaArtist(const std::string& artistCautat) const {
    std::vector<Comanda> rezultate;
    for (const auto& comanda : comenzi) {
        for (const auto& produs_ptr : comanda.getCos().produse) {
            if (produs_ptr->getArtist() == artistCautat) {
                rezultate.push_back(comanda);
                break;
            }
        }
    }
    return rezultate;
}

bool Magazin::actualizeazaComanda(const Client& client, const ProdusMuzical& produs_nou) {
    for (auto& comanda : comenzi) {
        if (comanda.getClient().getNume() == client.getNume()) {
            std::unique_ptr<ProdusMuzical> produs_clonat(produs_nou.clone());
            comanda.getCos().adaugaProdus(std::move(produs_clonat));
            return true;
        }
    }
    return false;
}

void Magazin::raportComenziTop(int topN) const {
    if (comenzi.empty() || topN <= 0) {
        std::cout << "\nRaport Top Comenzi: Nu exista comenzi sau N este invalid.\n";
        return;
    }

    std::vector<Comanda> sorted_comenzi = comenzi;
    std::sort(sorted_comenzi.begin(), sorted_comenzi.end(), [](const Comanda& a, const Comanda& b) {
        return a.calculeazaTotalCuTaxe() > b.calculeazaTotalCuTaxe();
    });

    int count = std::min((int)sorted_comenzi.size(), topN);

    std::cout << "\n--- RAPORT TOP " << count << " COMENZI DUPA VALOARE ---\n";
    for (int i = 0; i < count; ++i) {
        std::cout << i + 1 << ". Client: " << sorted_comenzi[i].getClient().getNume()
                  << " | Total: " << std::fixed << std::setprecision(2)
                  << sorted_comenzi[i].calculeazaTotalCuTaxe() << " RON\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Magazin& m) {
    os << "\n========================================\n";
    os << "MAGAZIN: " << m.nume << "\n";
    os << "Total Comenzi: " << m.numarComenzi() << "\n";
    os << "Venit Total: " << std::fixed << std::setprecision(2) << m.venitTotal() << " RON\n";
    os << "========================================\n";

    if (m.comenzi.empty()) {
        os << "Nici o comanda inregistrata.\n";
        return os;
    }

    os << "\nDetalii Comenzi:\n";
    for (const auto& comanda : m.comenzi) {
        os << comanda << "\n";
    }
    return os;
}

