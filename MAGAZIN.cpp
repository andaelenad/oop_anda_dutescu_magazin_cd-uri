#include "MAGAZIN.h"
#include <algorithm>
#include <iomanip>
#include <map>
#include <string>
#include <iostream>

Magazin::Magazin(const std::string& n) : nume(n) {}

Magazin::Magazin(const Magazin& other)
    : nume(other.nume), comenzi(other.comenzi) {}

Magazin& Magazin::operator=(const Magazin& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->comenzi = other.comenzi;
    }
    return *this;
}

void Magazin::adaugaComanda(const Comanda& c) {
    comenzi.push_back(c);
}

double Magazin::venitTotal() const {
    double total = 0.0;
    for (const auto& comanda : comenzi) {
        total += comanda.calculeazaTotal();
    }
    return total;
}

int Magazin::numarComenzi() const {
    return static_cast<int>(comenzi.size());
}

bool Magazin::actualizeazaComanda(const Client& client, const CD& cd_nou) {
    auto it = std::find_if(comenzi.begin(), comenzi.end(),
        [&client](const Comanda& c) {
            return c.getClient().getNume() == client.getNume();
        });

    if (it != comenzi.end()) {
        it->adaugaCD(cd_nou);
        return true;
    }
    return false;
}

void Magazin::raportClientiTop(int topN) const {
    std::cout << "\n--- RAPORT TOP " << topN << " CLIENTI (Nr. CD-uri cumparate) ---\n";
    std::map<std::string, int> clientCDCounts;

    for (const auto& comanda : comenzi) {
        clientCDCounts[comanda.getClient().getNume()] += comanda.numarCDuri();
    }

    std::vector<std::pair<std::string, int>> sortedClients(clientCDCounts.begin(), clientCDCounts.end());

    std::sort(sortedClients.begin(), sortedClients.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    for (size_t i = 0; i < static_cast<size_t>(topN) && i < sortedClients.size(); ++i) {
        std::cout << (i + 1) << ". " << sortedClients[i].first
                  << " (CD-uri: " << sortedClients[i].second << ")\n";
    }
}

std::vector<Comanda> Magazin::filtreazaComenziDupaArtist(const std::string& artistCautat) const {
    std::vector<Comanda> comenziGasite;
    std::string lowerArtistCautat = artistCautat;
    std::transform(lowerArtistCautat.begin(), lowerArtistCautat.end(), lowerArtistCautat.begin(), ::tolower);

    for (const auto& comanda : comenzi) {
        bool gasit = false;
        for (const auto& cd : comanda.getCDuri()) {
            std::string lowerArtistCD = cd.getArtist();
            std::transform(lowerArtistCD.begin(), lowerArtistCD.end(), lowerArtistCD.begin(), ::tolower);

            if (lowerArtistCD.find(lowerArtistCautat) != std::string::npos) {
                gasit = true;
                break;
            }
        }
        if (gasit) {
            comenziGasite.push_back(comanda);
        }
    }

    return comenziGasite;
}

std::ostream& operator<<(std::ostream& os, const Magazin& m) {
    os << "\n========================================\n";
    os << "MAGAZIN: " << m.nume << "\n";
    os << "Numar total de comenzi: " << m.numarComenzi() << "\n";
    os << "Venit total generat: " << std::fixed << std::setprecision(2) << m.venitTotal() << " RON\n";
    os << "========================================\n";

    for (const auto& comanda : m.comenzi) {
        os << comanda;
    }
    return os;
}

