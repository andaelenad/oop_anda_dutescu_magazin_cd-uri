#include "CD.h"
#include "CLIENT.h"
#include "COMANDA.h"
#include "MAGAZIN.h"
#include "ADRESA.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

void citesteComanda(std::ifstream& fin, Magazin& magazin) {
    std::string line;

    if (!std::getline(fin, line)) return;
    std::string numeClient = line;

    if (!std::getline(fin, line)) return;
    std::string adresaStr = line;

    Adresa adr(adresaStr, "N/A");

    int n = 0;
    if (!(fin >> n)) return;
    fin.ignore();

    std::vector<CD> cduri;

    for (int i = 0; i < n; i++) {
        if (!std::getline(fin, line)) break;
        if (line.empty()) continue;

        std::string album, artist;
        double pret = 0.0;

        try {
            size_t lastSpace = line.find_last_of(' ');
            if (lastSpace == std::string::npos || lastSpace == line.length() - 1) {
                throw std::invalid_argument("Linie CD fara pret sau format incorect.");
            }

            std::string pret_str = line.substr(lastSpace + 1);
            pret = std::stod(pret_str);

            std::string rest = line.substr(0, lastSpace);
            size_t mid = rest.find_last_of(' ');

            if (mid == std::string::npos) {
                album = rest;
                artist = "Necunoscut";
            } else {
                album = rest.substr(0, mid);
                artist = rest.substr(mid + 1);
            }

            cduri.emplace_back(album, artist, pret);

        } catch (const std::invalid_argument&) {
            std::cerr << "AVERTISMENT: Pret invalid pentru CD in linia: " << line << " (Ignorat)\n";
        } catch (const std::out_of_range&) {
            std::cerr << "AVERTISMENT: Pret prea mare pentru CD in linia: " << line << " (Ignorat)\n";
        }
    }

    Client client(numeClient, adr, "");
    Comanda com(client, cduri);
    magazin.adaugaComanda(com);
}

int main() {
    std::ifstream fin("tastatura.txt");
    if (!fin) {
        std::cerr << "EROARE: Nu am putut deschide tastatura.txt. Asigurati-va ca este in directorul corect.\n";
        return 1;
    }

    Magazin magazin("Magazin CD-uri OOP");

    std::cout << ">>> Incarcare date din tastatura.txt...\n";
    while (!fin.eof()) {
        citesteComanda(fin, magazin);
        std::string emptyLine;
        std::getline(fin, emptyLine);
    }
    fin.close();

    std::cout << "\n>>> SCENARIU DE UTILIZARE A TUTUROR FUNCTIILOR <<<\n";

    std::cout << magazin;

    std::cout << "\n[Functii Simple]\n";
    std::cout << "Numar total comenzi: " << magazin.numarComenzi() << "\n";
    std::cout << "Venit total magazin: " << std::fixed << std::setprecision(2) << magazin.venitTotal() << " RON\n";

    magazin.raportClientiTop(3);

    std::string artistCautat = "Specii";
    std::vector<Comanda> comenziFiltrate = magazin.filtreazaComenziDupaArtist(artistCautat);

    std::cout << "\n--- COMENZI FILTRATE DUPA ARTISTUL '" << artistCautat << "' ---\n";
    if (comenziFiltrate.empty()) {
        std::cout << "Nu s-au gasit comenzi pentru acest artist.\n";
    } else {
        std::cout << "S-au gasit " << comenziFiltrate.size() << " comenzi:\n";
        for (const auto& comanda : comenziFiltrate) {
            std::cout << "  - Client: " << comanda.getClient().getNume() << "\n";
        }
    }

    Client clientOriginal("Test Client", Adresa("Strada Testului", "1"), "test@email.com");
    Client clientCopie = clientOriginal;
    Client altClient("Altul", Adresa("Altundeva", "0"), "altul@email.com");
    altClient = clientOriginal;

    std::cout << "\n[Test Regula Celor 5]\n";
    std::cout << "Client Original: " << clientOriginal.getNume() << "\n";
    std::cout << "Client Copie (Op=): " << altClient.getNume() << "\n";

    return 0;
}




