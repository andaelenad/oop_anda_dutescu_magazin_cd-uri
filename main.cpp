#include "PRODUSMUZICAL.h"
#include "CD.h"
#include "VINIL.h"
#include "CASETA.h"
#include "MERCHANDISE.h"
#include "CLIENT.h"
#include "COS_CUMPARATURI.h"
#include "COMANDA.h"
#include "MAGAZIN.h"
#include "EroriMuzicale.h"

// Librarii Standard
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <memory>
#include <sstream>
#include <algorithm>
#include <utility>

// Biblioteca Externa JSON
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// Functie de utilitate pentru a crea un produs dintr-un obiect JSON
unique_ptr<ProdusMuzical> createProdusFromJSON(const json& item) {
    // Extragerea atributelor comune
    string tip = item.at("tip").get<string>();
    string titlu = item.at("titlu").get<string>();
    string artist = item.at("artist").get<string>();
    int anAparitie = item.at("an_aparitie").get<int>();
    string gen = item.at("gen").get<string>();
    double pret = item.at("pret").get<double>();

    // Logica polimorfica de creare a obiectelor
    if (tip == "CD") {
        int nrPiese = item.at("viteza").get<int>();
        return make_unique<CD>(titlu, artist, anAparitie, gen, pret, nrPiese);
    }
    else if (tip == "VINIL") {
        int rpm = item.at("rpm").get<int>();
        return make_unique<Vinil>(titlu, artist, anAparitie, gen, pret, rpm);
    }
    else if (tip == "CASETA") {
        string tipBanda = item.at("tip_banda").get<string>();
        return make_unique<Caseta>(titlu, artist, anAparitie, gen, pret, tipBanda);
    }
    else if (tip == "MERCHANDISE") {
        string culoare = item.at("culoare").get<string>();
        string material = item.at("material").get<string>();
        return make_unique<Merchandise>(titlu, artist, anAparitie, gen, pret, culoare, material);
    }
    else {
        throw EroareFormatNecunoscut("Tip de produs JSON necunoscut: " + tip);
    }
}

// Functie de Nivel Inalt (Citire Comenzi) - Utilizeaza Biblioteca Externa JSON
void citesteComenziDinJSON(const std::string& numeFisier, Magazin& magazin) {
    std::ifstream f(numeFisier);

    if (!f.is_open()) {
        throw EroareDateIncomplete("Fisierul JSON nu a putut fi deschis. Verificati calea.");
    }

    try {
        json comenziJSON = json::parse(f);

        if (!comenziJSON.is_array()) {
             throw EroareDateIncomplete("Fisierul JSON nu contine un array de comenzi.");
        }

        for (const auto& comandaItem : comenziJSON) {

            string numeClient = comandaItem.at("client").at("nume").get<string>();
            string emailClient = comandaItem.at("client").at("email").get<string>();
            Client client(numeClient, emailClient);

            CosCumparaturi cosComanda;

            for (const auto& produsItem : comandaItem.at("produse")) {
                try {
                    cosComanda.adaugaProdus(createProdusFromJSON(produsItem));
                }
                catch (const EroarePretInvalid& e) {
                     cerr << "AVERTISMENT la citire (Exceptie Pret Invalid): " << e.what()
                          << " pentru clientul " << numeClient << ". (Produs ignorat)\n";
                }
                catch (const EroareMuzicala& e) {
                     cerr << "AVERTISMENT la citire (Exceptie Muzicala Generica): " << e.what()
                          << " (Produs ignorat)\n";
                }
            }

            if (!cosComanda.produse.empty()) {
                Comanda comanda(client, std::move(cosComanda));
                magazin.adaugaComanda(comanda);
            }
        }
    }
    catch (const json::exception& e) {
        throw EroareDateIncomplete("Eroare la parsarea datelor JSON: " + std::string(e.what()));
    }
    catch (const exception& e) {
        throw EroareDateIncomplete("Eroare neasteptata la citirea comenzilor: " + std::string(e.what()));
    }
}


int main() {
    Magazin magazin("Magazin Muzical Polimorfic");
    const string FISIER_JSON = "comenzi.json";

    cout << ">>> Incarcare date din " << FISIER_JSON << " (Biblioteca Externa JSON)...\n";
    cout << "----------------------------------------------------------------------\n";

    try {
        citesteComenziDinJSON(FISIER_JSON, magazin);
    } catch (const exception& e) {
        cerr << "\n[EROARE FATALA LA CITIRE]: " << e.what() << "\n";
        return 1;
    }

    cout << "\n>>> SCENARIU DE UTILIZARE A TUTUROR FUNCTIILOR <<<\n";
    cout << "----------------------------------------------------\n";

    cout << magazin;

    cout << "----------------------------------------------------\n";

    cout << "\n[Functii de Nivel Inalt & Static]\n";
    cout << "Numar total comenzi: " << magazin.numarComenzi() << "\n";
    cout << "Venit total magazin: " << fixed << setprecision(2) << magazin.venitTotal() << " RON\n";
    cout << "Total produse muzicale create (Static): " << ProdusMuzical::getNumarTotalProduse() << "\n";

    string artistCautat = "Cheloo";
    vector<Comanda> comenziFiltrate = magazin.filtreazaComenziDupaArtist(artistCautat);

    cout << "\n--- COMENZI FILTRATE DUPA ARTISTUL '" << artistCautat << "' ---\n";
    cout << "S-au gasit " << comenziFiltrate.size() << " comenzi.\n";
    for (const auto& comanda : comenziFiltrate) {
        cout << "  - Client: " << comanda.getClient().getNume() << "\n";
    }

    if (magazin.numarComenzi() > 0) {
        magazin.sorteazaComenziDupaValoare();
        cout << "\n--- TEST SORTARE COMENZI ---\n";
        const vector<Comanda>& comenziSortate = magazin.getComenzi();
        cout << "Comenzile au fost sortate. Prima comanda: "
                  << comenziSortate[0].getClient().getNume()
                  << " (" << fixed << setprecision(2) << comenziSortate[0].calculeazaTotalCuTaxe() << " RON)\n";

        // CORECTIE AICI: Folosim indexul [1] pentru o comanda care contine Vinil (dupa sortare)
        cout << "\n--- TEST DYNAMIC_CAST (AFISARE VINILURI) ---\n";
        cout << "Comanda folosita pentru dynamic_cast: " << comenziSortate[1].getClient().getNume() << "\n";
        comenziSortate[1].getCos().afiseazaDoarViniluri();

        cout << "\n[Test 4 clase derivate & Apelare Getters Produs Muzical]\n";
        for (const auto& p : magazin.getComenzi()[0].getCos().produse) {
            cout << "  -> Produs: " << p->getTitlu() << ", Artist: " << p->getArtist()
                 << ", An: " << p->getAnAparitie() << ", Gen: " << p->getGen()
                 << ", Pret ID: " << p->getIdProdus() << "\n";

            if (const Merchandise* m = dynamic_cast<const Merchandise*>(p.get())) {
                cout << "  -> Tip Merch: " << m->getTitlu() << " | Este Premium: " << (m->estePremium() ? "DA" : "NU") << "\n";
            }
        }

        unique_ptr<ProdusMuzical> produsClonat = magazin.getComenzi()[0].getCos().produse[0]->clone();
        cout << "\n--- TEST CLONARE (VIRTUAL CONSTRUCTOR) ---\n";
        cout << "Produs Original ID: " << magazin.getComenzi()[0].getCos().produse[0]->getIdProdus() << "\n";
        cout << "Produs Clonat ID: " << produsClonat->getIdProdus() << "\n";

        Client clientTarget("Anda Dutescu", "anda.dutescu@gmail.com");
        CD cd_nou("Update Test", "Artist Nou", 2025, "Pop", 100.00, 15);
        bool actualizat = magazin.actualizeazaComanda(clientTarget, cd_nou);
        cout << "\n--- TEST actualizeazaComanda (Magazin) ---\n";
        cout << "Comanda clientului " << clientTarget.getNume() << " a fost actualizata: " << (actualizat ? "DA" : "NU") << "\n";

        Comanda comandaCopie = comenziSortate[0];
        cout << "\n--- TEST COPY CONSTRUCTOR (COMANDA) ---\n";
        cout << "Comanda Copie (Client): " << comandaCopie.getClient().getNume()
             << ", Total: " << fixed << setprecision(2) << comandaCopie.calculeazaTotalCuTaxe() << " RON\n";
    }

    magazin.raportComenziTop(3);

    return 0;
}