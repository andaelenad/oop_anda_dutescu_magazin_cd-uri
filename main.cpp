#include "ProdusMuzical.h"
#include "CD.h"
#include "VINIL.h"
#include "CASETA.h"
#include "CLIENT.h"
#include "COS_CUMPARATURI.h"
#include "COMANDA.h"
#include "MAGAZIN.h"
#include "EroriMuzicale.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <memory>
#include <sstream>
#include <tuple>
#include <algorithm>

using namespace std;

tuple<string, string, double, int> parseCDLine(const string& line) {
    if (line.empty()) throw std::invalid_argument("Linie goala.");

    stringstream ss(line);
    string token;
    vector<string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() < 4) {
        throw std::invalid_argument("Linie CD fara minim 4 componente (Titlu, Artist, Pret, Piese).");
    }

    try {
        int nrPiese = std::stoi(tokens.back());
        tokens.pop_back();

        double pret = std::stod(tokens.back());
        tokens.pop_back();

        string artist = tokens.back();
        tokens.pop_back();

        string album;
        for (const auto& t : tokens) {
            album += t + " ";
        }
        if (!album.empty()) album.pop_back();

        return make_tuple(album, artist, pret, nrPiese);

    } catch (const std::exception&) {
        throw std::invalid_argument("Pret sau Piese invalide.");
    }
}

void citesteComanda(std::ifstream& fin, Magazin& magazin) {
    std::string line;

    if (!std::getline(fin, line)) return;
    std::string numeClient = line;

    if (!std::getline(fin, line)) return;
    std::string emailClient = line;

    int n = 0;
    if (!(fin >> n)) return;
    fin.ignore();

    CosCumparaturi cosComanda;

    for (int i = 0; i < n; i++) {
        if (!std::getline(fin, line)) break;
        if (line.empty()) continue;

        try {
            string album, artist;
            double pret;
            int nrPiese;

            tie(album, artist, pret, nrPiese) = parseCDLine(line);

            // Anul de aparitie si Genul sunt necunoscute din fisier, folosim default
            cosComanda.adaugaProdus(make_unique<CD>(album, artist, 2023, "Necunoscut", pret, nrPiese));

        } catch (const std::exception& e) {
            std::cerr << "AVERTISMENT la citire: " << e.what() << " in linia: " << line << " (Ignorat)\n";
        }
    }

    if (!cosComanda.produse.empty()) {
        Client client(numeClient, emailClient);
        Comanda comanda(client, std::move(cosComanda));
        magazin.adaugaComanda(comanda);
    }

    std::getline(fin, line);
}

int main() {
    std::ifstream fin("tastatura.txt");
    if (!fin) {
        std::cerr << "EROARE: Nu am putut deschide tastatura.txt. Asigurati-va ca este in directorul corect.\n";
        std::ofstream fout("tastatura.txt");
        if (fout) {
            fout << "Ion Popescu\n";
            fout << "ion@email.com\n";
            fout << "2\n";
            fout << "Dark Side of the Moon Pink Floyd 59.90 10\n";
            fout << "Thriller Michael Jackson 125.00 12\n";
            fout << "\n";
            fout << "Andrei Vasilescu\n";
            fout << "andrei@email.com\n";
            fout << "1\n";
            fout << "Subcultura Raku 30.00 15\n";
            fout.close();
            std::cerr << "ATENTIE: Am creat un fisier 'tastatura.txt' de exemplu. Rulati din nou.\n";
        }
        return 1;
    }

    Magazin magazin("Magazin Muzical OOP");

    std::cout << ">>> Incarcare date din tastatura.txt...\n";

    while (fin.peek() != EOF) {
        citesteComanda(fin, magazin);
    }
    fin.close();

    std::cout << "\n>>> SCENARIU DE UTILIZARE A TUTUROR FUNCTIILOR <<<\n";
    std::cout << magazin;

    std::cout << "\n[Functii Simple]\n";
    std::cout << "Numar total comenzi: " << magazin.numarComenzi() << "\n";
    std::cout << "Venit total magazin: " << std::fixed << std::setprecision(2) << magazin.venitTotal() << " RON\n";

    magazin.raportComenziTop(3);

    std::string artistCautat = "Pink Floyd";
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


    std::cout << "\n[Utilizare Functii Suplimentare]\n";

    std::cout << "Total produse muzicale create in sistem (Static): " << ProdusMuzical::getNumarTotalProduse() << "\n";

    magazin.sorteazaComenziDupaValoare();
    std::cout << "\n--- TEST SORTARE COMENZI ---\n";
    if (magazin.numarComenzi() > 0) {
        const std::vector<Comanda>& comenziSortate = magazin.getComenzi();
        std::cout << "Comenzile au fost sortate. Prima comanda (cea mai mica valoare): "
                  << comenziSortate[0].getClient().getNume()
                  << " cu totalul de " << std::fixed << std::setprecision(2)
                  << comenziSortate[0].calculeazaTotalCuTaxe() << " RON\n";
    }


    if (magazin.numarComenzi() > 0) {
        // Cream un CD de adaugat. Folosim ProdusMuzical& pentru a testa polimorfismul.
        CD cdDeAdaugat("Noutate 2025", "B.U.G. Mafia", 2025, "Hip-Hop", 75.0, 14);

        const Client& clientDeActualizat = magazin.getComenzi()[0].getClient();

        bool succes = magazin.actualizeazaComanda(clientDeActualizat, cdDeAdaugat);

        if (succes) {
            std::cout << "\nComanda clientului '" << clientDeActualizat.getNume()
                      << "' a fost actualizata cu un produs suplimentar.\n";
        }
    }

    return 0;
}


