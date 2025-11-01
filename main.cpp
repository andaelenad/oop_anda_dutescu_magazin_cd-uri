#include "CD.h"
#include "CLIENT.h"
#include "COMANDA.h"
#include "MAGAZIN.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

int main() {
    std::ifstream fin("tastatura.txt");
    if (!fin) {
        std::cerr << "Nu am putut deschide tastatura.txt\n";
        return 1;
    }

    Magazin magazin("Magazin CD-uri");
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        // Nume client (prima linie)
        std::string numeClient = line;

        // Citim adresa
        std::getline(fin, line);
        std::string adresa = line;

        // Număr CD-uri
        int n;
        fin >> n;
        fin.ignore();

        std::vector<CD> cduri;

        for (int i = 0; i < n; i++) {
            std::getline(fin, line);
            std::string album, artist;
            double pret;

            // extragem pretul de la sfarsit
            size_t lastSpace = line.find_last_of(' ');
            pret = std::stod(line.substr(lastSpace + 1));

            // restul liniei fără pret
            std::string rest = line.substr(0, lastSpace);

            // împărțim albumul de artist
            size_t mid = rest.find_last_of(' ');
            album = rest.substr(0, mid);
            artist = rest.substr(mid + 1);

            cduri.emplace_back(album, artist, pret);
        }

        Client c(numeClient, "");
        Comanda com(c, cduri);
        magazin.adaugaComanda(com);
    }

    std::cout << magazin;

    return 0;
}




