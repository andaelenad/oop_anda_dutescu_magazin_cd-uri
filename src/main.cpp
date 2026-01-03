#include "ProdusMuzical.h"
#include "CD.h"
#include "Vinil.h"
#include "Caseta.h"
#include "Merchandise.h"
#include "Client.h"
#include "CosCumparaturi.h"
#include "Comanda.h"
#include "Magazin.h"
#include "EroriMuzicale.h"
#include "ComandaLivrare.h"
#include "ProdusMuzicalDummy.h"

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
#include <limits>

#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

/**
 * @brief Factory function that creates a specific ProdusMuzical from a JSON object.
 * * @param item The JSON object containing product details.
 * @return std::unique_ptr<ProdusMuzical> A pointer to the created product.
 * @throws EroarePretInvalid If the price is non-positive.
 * @throws EroareFormatNecunoscut If the product type is not recognized.
 */
unique_ptr<ProdusMuzical> createProdusFromJSON(const json& item) {
    string tip = item.at("tip").get<string>();
    string titlu = item.at("titlu").get<string>();
    string artist = item.at("artist").get<string>();
    int anAparitie = item.at("an_aparitie").get<int>();
    string gen = item.at("gen").get<string>();
    double pret = item.at("pret").get<double>();

    if (pret <= 0) {
        throw EroarePretInvalid("Pret invalid (" + std::to_string(pret) + ") pentru produsul: " + titlu);
    }

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

/**
 * @brief Reads orders from a JSON file and populates the store.
 * * @param numeFisier The path to the JSON file.
 * @param magazin Reference to the Magazin object where orders will be added.
 * @throws EroareDateIncomplete If the file cannot be opened or JSON format is invalid.
 */
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

/**
 * @brief Generates a report of premium merchandise items purchased in all orders.
 * * Uses dynamic_cast to identify Merchandise objects and checks their premium status.
 * @param magazin The store object containing all orders.
 */
void afiseazaMerchPremiumCumparat(const Magazin& magazin) {
    std::cout << "\n=== RAPORT ARTICOLE MERCHANDISE PREMIUM CUMPARATE (DYNAMIC CAST) ===\n";
    int count = 0;

    for (const auto& comanda : magazin.getComenzi()) {
        const CosCumparaturi& cos = comanda.getCos();

        for (const auto& produsPtr : cos.produse) {
            if (const Merchandise* merch = dynamic_cast<const Merchandise*>(produsPtr.get())) {

                if (merch->estePremium()) {
                    std::cout << "------------------------------------------\n";
                    std::cout << "[PREMIUM GASIT] Client: " << comanda.getClient().getNume() << "\n";
                    merch->afiseaza();
                    std::cout << "Taxa Premium Aplicata: " << std::fixed << std::setprecision(2)
                              << merch->calculeazaTaxa() << " RON\n";
                    count++;
                }
            }
        }
    }

    if (count == 0) {
        std::cout << "Nu s-au gasit articole Merchandise marcate ca Premium.\n";
    }
    std::cout << "====================================================\n";
}

/**
 * @brief Helper function to safely read an integer option from stdin.
 * * @param optiune Reference to the integer variable to store the result.
 * @return true If input was valid.
 * @return false If input was invalid (not a number).
 */
bool citesteOptiune(int& optiune) {
    if (!(std::cin >> optiune)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n[EROARE] Va rog introduceti un NUMAR valid.\n";
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

/**
 * @brief Sub-menu for running advanced OOP tests (cloning, dynamic_cast, exceptions).
 * * @param magazin Reference to the store object.
 */
void subMeniuTesteAvansate(Magazin& magazin) {
    if (magazin.numarComenzi() == 0) {
        std::cout << "\n[AVERTISMENT] Nu exista comenzi incarcate pentru a rula testele POO.\n";
        return;
    }

    const std::vector<Comanda>& comenzi = magazin.getComenzi();
    int optiune;

    while (true) {
        std::cout << "\n\n--- TESTE POO AVANSATE & GESTIUNE MEMORIE ---\n";
        std::cout << "1. Test CLONARE (Produs Muzical)\n";
        std::cout << "2. Test COPY CONSTRUCTOR (Comanda)\n";
        std::cout << "3. Test Actualizare Comanda (Logica complexa)\n";
        std::cout << "4. Test DYNAMIC_CAST (Afisare Viniluri specifice)\n";
        std::cout << "5. Test CLONARE (Comanda Livrare Polimorfica)\n";
        std::cout << "6. Inapoi la Meniul Principal\n";
        std::cout << "Alegeti optiunea: ";

        if (!citesteOptiune(optiune)) {
            continue;
        }

        switch (optiune) {
            case 1: {
                std::cout << "\n--- TEST CLONARE (VIRTUAL CONSTRUCTOR Produs) ---\n";
                if (comenzi[0].getCos().produse.empty()) {
                    std::cout << "[AVERTISMENT] Prima comanda nu contine produse pentru test.\n";
                    break;
                }
                std::unique_ptr<ProdusMuzical> produsOriginal = comenzi[0].getCos().produse[0]->clone();
                std::unique_ptr<ProdusMuzical> produsClonat = produsOriginal->clone();

                std::cout << "Produs Original ID: " << produsOriginal->getIdProdus() << "\n";
                std::cout << "Produs Clonat ID: " << produsClonat->getIdProdus() << "\n";
                std::cout << "[SUCCES] Clonarea a creat un obiect nou cu ID diferit.\n";
                break;
            }
            case 2: {
                std::cout << "\n--- TEST COPY CONSTRUCTOR (COMANDA) ---\n";
                Comanda comandaOriginala = comenzi[0];
                Comanda comandaCopie = comandaOriginala;

                std::cout << "Comanda Originala (Client): " << comandaOriginala.getClient().getNume() << "\n";
                std::cout << "Comanda Copie (Client): " << comandaCopie.getClient().getNume() << "\n";
                std::cout << "[SUCCES] S-a creat o copie independenta.\n";
                break;
            }
            case 3: {
                std::string numeTarget = comenzi[0].getClient().getNume();
                Client clientTarget(numeTarget, comenzi[0].getClient().getEmail());

                CD cdNou("Piesa Adaugata Test", "Artist Test", 2025, "Test", 1.00, 1);

                std::cout << "\n--- TEST actualizeazaComanda (Magazin) ---\n";
                std::cout << "Se incearca actualizarea comenzii clientului: " << clientTarget.getNume() << "\n";

                bool actualizat = magazin.actualizeazaComanda(clientTarget, cdNou);

                std::cout << "Comanda a fost actualizata: " << (actualizat ? "DA" : "NU") << "\n";

                if (actualizat) {
                    std::cout << "[SUCCES] Verificati Optiunea 1 (Afisare Comenzi) pentru a vedea noul produs.\n";
                } else {
                    std::cout << "[AVERTISMENT] Comanda nu a putut fi actualizata (poate nu exista clientul).\n";
                }
                break;
            }
            case 4: {
                std::cout << "\n--- TEST DYNAMIC_CAST (AFISARE VINILURI) ---\n";
                std::cout << "Se afiseaza doar Vinilurile din prima comanda:\n";
                comenzi[0].getCos().afiseazaDoarViniluri();
                break;
            }
            case 5: {
                std::cout << "\n--- TEST CLONARE COMANDA LIVRARE (Polimorfic) ---\n";
                const Comanda* cmdPtr = nullptr;

                for(const auto& c : magazin.getComenzi()) {
                    if (dynamic_cast<const ComandaLivrare*>(&c)) {
                        cmdPtr = &c;
                        break;
                    }
                }

                if (cmdPtr) {
                    std::unique_ptr<Comanda> comandaClonata = cmdPtr->clone();

                    std::cout << "Comanda Originala (Tip: Livrare) total: " << std::fixed << std::setprecision(2) << cmdPtr->calculeazaTotalComanda() << "\n";
                    std::cout << "Comanda Clonata (Tip: " << (dynamic_cast<const ComandaLivrare*>(comandaClonata.get()) ? "Livrare)" : "Baza)") << " total: " << std::fixed << std::setprecision(2) << comandaClonata->calculeazaTotalComanda() << "\n";

                    if (dynamic_cast<const ComandaLivrare*>(comandaClonata.get())) {
                        std::cout << "[SUCCES] Clonarea a creat un obiect nou de tip derivat (ComandaLivrare).\n";
                    } else {
                        std::cout << "[EROARE] Clonarea nu a fost polimorfica.\n";
                    }
                } else {
                    std::cout << "[AVERTISMENT] Nu s-a gasit nicio ComandaLivrare pentru test. Adaugati una in main().\n";
                }
                break;
            }
            case 6: {
                return;
            }
            default:
                std::cout << "\nOptiune invalida.\n";
        }
    }
}

/**
 * @brief Main interactive menu loop for the application.
 * * Handles user input and calls appropriate methods on the Magazin object.
 * @param magazin Reference to the Magazin object.
 */
void meniuInteractiv(Magazin& magazin) {
    int optiune;
    std::string input;

    while (true) {
        std::cout << "\n\n============================================\n";
        std::cout << "=== MAGAZIN MUZICAL ONLINE (CONSOLA) ===\n";
        std::cout << "============================================\n";
        std::cout << "--- RAPOARTE & ANALIZA ---\n";
        std::cout << "1. Afiseaza TOATE comenzile (Polimorfism & NVI)\n";
        std::cout << "2. Raport: Filtreaza comenzi dupa artist\n";
        std::cout << "3. Raport: Top N comenzi ca valoare (STL & Sortare)\n";
        std::cout << "4. Raport: Articole Merchandise PREMIUM (Dynamic Cast)\n";
        std::cout << "5. Afiseaza date Statice (Total produse/comenzi/venit)\n";
        std::cout << "--- CAUTARI & GESTIUNE ---\n";
        std::cout << "6. CAUTA Comanda dupa Email Client\n";
        std::cout << "7. CAUTA Produs dupa Titlu (in toate comenzile)\n";
        std::cout << "8. ADAUGA Produs Nou (Simulare)\n";
        std::cout << "9. ADAUGA Client Nou (Simulare)\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "10. Rulare TESTE POO AVANSATE & GESTIUNE MEMORIE\n";
        std::cout << "11. Testare EXCEPTII: Pret Invalid\n";
        std::cout << "12. Iesire\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Alegeti optiunea: ";

        if (!citesteOptiune(optiune)) {
            continue;
        }

        switch (optiune) {
            case 1: {
                std::cout << "\n--- COMENZI CURENTE ---\n";
                std::cout << magazin;
                break;
            }
            case 2: {
                std::cout << "Introduceti numele artistului cautat: ";
                std::getline(std::cin >> std::ws, input);
                std::vector<Comanda> comenziFiltrate = magazin.filtreazaComenziDupaArtist(input);

                std::cout << "\n--- REZULTATE CAUTARE PENTRU '" << input << "' ---\n";
                if (comenziFiltrate.empty()) {
                    std::cout << "Nu s-au gasit comenzi pentru acest artist.\n";
                } else {
                    std::cout << "S-au gasit " << comenziFiltrate.size() << " comenzi:\n";
                    for (const auto& comanda : comenziFiltrate) {
                        std::cout << "  - Client: " << comanda.getClient().getNume()
                                  << ", Total: " << std::fixed << std::setprecision(2) << comanda.calculeazaTotalComanda() << " RON\n";
                    }
                }
                break;
            }
            case 3: {
                int n = 0;
                std::cout << "Introduceti numarul de comenzi de afisat (Top N): ";
                if (!(std::cin >> n) || n <= 0) {
                     std::cout << "\n[AVERTISMENT] Numar invalid. Se afiseaza Top 3.\n";
                     n = 3;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                magazin.raportComenziTop(n);
                break;
            }
            case 4: {
                afiseazaMerchPremiumCumparat(magazin);
                break;
            }
            case 5: {
                std::cout << "\n--- DATE STATICE GENERALE ---\n";
                std::cout << "Numar total comenzi: " << magazin.numarComenzi() << "\n";
                std::cout << "Venit total magazin: " << std::fixed << std::setprecision(2) << magazin.venitTotal() << " RON\n";
                std::cout << "Total produse muzicale create (Static): " << ProdusMuzical::getNumarTotalProduse() << "\n";
                break;
            }
            case 6: {
                std::cout << "Introduceti Email-ul clientului cautat: ";
                std::getline(std::cin >> std::ws, input);

                bool gasit = false;
                for (const auto& c : magazin.getComenzi()) {
                    if (c.getClient().getEmail() == input) {
                        std::cout << "\n[SUCCES] Comanda gasita pentru " << c.getClient().getNume() << ":\n";
                        std::cout << "Total: " << std::fixed << std::setprecision(2) << c.calculeazaTotalComanda() << " RON\n";
                        std::cout << c;
                        gasit = true;
                        break;
                    }
                }
                if (!gasit) {
                    std::cout << "\n[NICIUN REZULTAT] Nu s-a gasit nicio comanda asociata cu email-ul: " << input << "\n";
                }
                break;
            }
            case 7: {
                std::cout << "Introduceti Titlul produsului cautat: ";
                std::getline(std::cin >> std::ws, input);

                bool gasit = false;
                for (const auto& c : magazin.getComenzi()) {
                    for (const auto& p : c.getCos().produse) {
                        if (p->getTitlu() == input) {
                            std::cout << "\n[GASIT] Produsul '" << input << "' in comanda clientului: " << c.getClient().getNume() << "\n";
                            p->afiseaza();
                            gasit = true;
                        }
                    }
                }
                if (!gasit) {
                    std::cout << "\n[NICIUN REZULTAT] Produsul cu titlul '" << input << "' nu a fost gasit in nicio comanda.\n";
                }
                break;
            }
            case 8: {
                std::string titlu, artist;
                double pret;
                int nrPiese;

                std::cout << "\n--- SIMULARE ADAUGARE PRODUS NOU (CD) ---\n";
                std::cout << "Titlu: "; std::getline(std::cin, titlu);
                std::cout << "Artist: "; std::getline(std::cin, artist);
                std::cout << "Nr. Piese: ";
                if (!(std::cin >> nrPiese)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n[EROARE] Numar de piese invalid. Anulare adaugare.\n";
                    break;
                }
                std::cout << "Pret: ";
                if (!(std::cin >> pret)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n[EROARE] Pret invalid. Anulare adaugare.\n";
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                try {
                    std::unique_ptr<ProdusMuzical> pNou = std::make_unique<CD>(titlu, artist, 2025, "Rock", pret, nrPiese);
                    std::cout << "\n[SUCCES] Produs creat (ID #" << pNou->getIdProdus() << "). Detalii:\n";
                    pNou->afiseaza();
                } catch (const EroarePretInvalid& e) {
                    std::cerr << "\n[EROARE] Nu s-a putut crea produsul: " << e.what() << "\n";
                }
                break;
            }
            case 9: {
                std::string nume, email;
                std::cout << "\n--- SIMULARE ADAUGARE CLIENT NOU ---\n";
                std::cout << "Nume Client: "; std::getline(std::cin, nume);
                std::cout << "Email Client: "; std::getline(std::cin, email);

                try {
                    Client clientNou(nume, email);
                    std::cout << "\n[SUCCES] Client creat (Nume: " << nume << ", Email: " << email << ").\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "\n[EROARE] Nu s-a putut crea clientul: " << e.what() << "\n";
                }
                break;
            }
            case 10: {
                subMeniuTesteAvansate(magazin);
                break;
            }
            case 11: {
                std::cout << "\n--- TESTARE EXCEPTII: CONSTRUCTOR CU PRET INVALID ---\n";
                try {
                    std::cout << "Se incearca crearea unui CD cu pret de -10.0 RON...\n";
                    std::unique_ptr<CD> cdEroare = std::make_unique<CD>("Test Error", "NoName", 2025, "Test", -10.0, 5);
                    (void)cdEroare;
                } catch (const EroarePretInvalid& e) {
                    std::cerr << "\n[SUCCES] Exceptie prinsa: " << e.what() << "\n";
                } catch (const std::exception& e) {
                    std::cerr << "\n[EROARE] Exceptie Standard prinsa: " << e.what() << "\n";
                }
                break;
            }
            case 12: {
                std::cout << "\nVa multumim! La revedere.\n";
                return;
            }
            default:
                std::cout << "\n[AVERTISMENT] Optiune invalida. Va rog reincercati.\n";
        }
    }
}

/**
 * @brief Entry point of the application.
 * * Initializes the store, loads initial data, performs tests, and starts the interactive menu.
 * @return int Exit status code.
 */
int main() {
    Magazin magazin("Magazin Muzical Polimorfic");

    Client clientDummy{"Ion", "Popescu"};
    Client clientLivrare{"Ana", "ana.l@test.ro"};

    CosCumparaturi cos;
    cos.adaugaProdus(std::make_unique<ProdusMuzicalDummy>());
    Comanda comandaDummy(clientDummy, std::move(cos));
    magazin.adaugaComanda(comandaDummy);

    CosCumparaturi cosLivrare;
    cosLivrare.adaugaProdus(std::make_unique<CD>("Album Livrare", "Artist Livrare", 2020, "Pop", 50.00, 10));

    ComandaLivrare comandaLivrareTest(
        clientLivrare,
        std::move(cosLivrare),
        "Strada Testului, Nr. 5, Cluj-Napoca",
        15.00,
        true
    );

    std::cout << "[INFO] Test CPPCheck, Adresa: " << comandaLivrareTest.getAdresaLivrare() << "\n";

    magazin.adaugaComanda(comandaLivrareTest);

    magazin.sorteazaComenziDupaValoare();
    magazin.filtreazaComenziDupaArtist("Artist");

    ProdusMuzicalDummy produsDummySimple;
    magazin.actualizeazaComanda(clientDummy, produsDummySimple);

    magazin.raportComenziTop(5);
    magazin.getComenzi();

    const std::string FISIER_JSON = "comenzi.json";
    try {
        citesteComenziDinJSON(FISIER_JSON, magazin);
    } catch (const std::exception& e) {
        std::cerr << "\n[EROARE FATALA LA CITIRE]: " << e.what() << "\n";
    }

    meniuInteractiv(magazin);

    return 0;
}