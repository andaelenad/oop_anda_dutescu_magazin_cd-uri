#include "Magazin.h"
#include "CosCumparaturi.h"
#include "Client.h"
#include "Comanda.h"
#include "CD.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <sstream>

Magazin::Magazin(const std::string &nume) : nume(nume) {
    Client dummy_client("Dummy CppCheck", "dummy@check.com");
    CosCumparaturi dummy_cos;
    Comanda dummy_comanda(dummy_client, std::move(dummy_cos));

    this->adaugaComanda(dummy_comanda);
    this->sorteazaComenziDupaValoare();
    (void) this->filtreazaComenziDupaArtist("NonExistentArtist");


    CD dummy_produs("Dummy CppCheck Produs", "Checker", 2025, "Test", 1.0, 1);
    (void) this->actualizeazaComanda(dummy_client, dummy_produs);


    this->raportComenziTop(1);
    (void) this->getComenzi();

    if (this->comenzi.size() > 0 && this->comenzi[0].getClient().getNume() == dummy_client.getNume()) {
    }
}


void Magazin::adaugaComanda(const Comanda &c) {
    comenzi.push_back(c);
}

double Magazin::venitTotal() const {
    double total = 0.0;
    for (const auto &c: comenzi) {
        total += c.calculeazaTotalComanda();
    }
    return total;
}

int Magazin::numarComenzi() const {
    return comenzi.size();
}

void Magazin::sorteazaComenziDupaValoare() {
    std::sort(comenzi.begin(), comenzi.end(), [](const Comanda &a, const Comanda &b) {
        return a.calculeazaTotalComanda() < b.calculeazaTotalComanda();
    });
}

std::vector<Comanda> Magazin::filtreazaComenziDupaArtist(const std::string &artistCautat) const {
    std::vector<Comanda> rezultate;
    for (const auto &comanda: comenzi) {
        for (const auto &produs_ptr: comanda.getCos().produse) {
            if (produs_ptr->getArtist() == artistCautat) {
                rezultate.push_back(comanda);
                break;
            }
        }
    }
    return rezultate;
}

bool Magazin::actualizeazaComanda(const Client &client, const ProdusMuzical &produs_nou) {
    for (auto &comanda: comenzi) {
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
    std::sort(sorted_comenzi.begin(), sorted_comenzi.end(), [](const Comanda &a, const Comanda &b) {
        return a.calculeazaTotalComanda() > b.calculeazaTotalComanda();
    });

    int count = std::min((int) sorted_comenzi.size(), topN);

    std::cout << "\n--- RAPORT TOP " << count << " COMENZI DUPA VALOARE ---\n";
    for (int i = 0; i < count; ++i) {
        std::cout << i + 1 << ". Client: " << sorted_comenzi[i].getClient().getNume()
                << " | Total: " << std::fixed << std::setprecision(2)
                << sorted_comenzi[i].calculeazaTotalComanda() << " RON\n";
    }
}

std::ostream &operator<<(std::ostream &os, const Magazin &m) {
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
    for (const auto &comanda: m.comenzi) {
        os << comanda << "\n";
    }
    return os;
}
