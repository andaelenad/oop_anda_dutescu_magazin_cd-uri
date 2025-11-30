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

using namespace std;

unique_ptr<ProdusMuzical> parseProdus(const string& line) {
    if (line.empty()) {
        throw invalid_argument("Linie produs goala.");
    }

    stringstream ss(line);
    string tipProdus;
    ss >> tipProdus;

    if (tipProdus.empty()) {
        throw invalid_argument("Nu s-a putut identifica tipul produsului.");
    }

    string restulLiniei;
    getline(ss >> ws, restulLiniei);

    if (restulLiniei.empty()) {
        throw EroareDateIncomplete("Date lipsa dupa tipul produsului.");
    }

    size_t posPret = restulLiniei.find('.');
    if (posPret == string::npos) {
        throw EroareDateIncomplete("Nu s-a putut găsi prețul (format numeric cu .).");
    }

    size_t posStartPretToken = restulLiniei.rfind(' ', posPret);
    if (posStartPretToken == string::npos) {
        throw EroareDateIncomplete("Format invalid in jurul pretului.");
    }

    string titluArtistRaw = restulLiniei.substr(0, posStartPretToken);
    string parametriRaw = restulLiniei.substr(posStartPretToken + 1);

    string titlu, artist;
    stringstream ssTitluArtist(titluArtistRaw);

    vector<string> titluArtistTokens;
    string token;
    while (ssTitluArtist >> token) {
        titluArtistTokens.push_back(token);
    }

    if (titluArtistTokens.size() < 2) {
        throw EroareDateIncomplete("Titlu sau Artist lipsa.");
    }

    artist = titluArtistTokens.back();
    titluArtistTokens.pop_back();

    titlu = titluArtistTokens[0];
    for (size_t i = 1; i < titluArtistTokens.size(); ++i) {
        titlu += " " + titluArtistTokens[i];
    }

    try {
        stringstream ssPret(parametriRaw);
        string pretStr;
        if (!(ssPret >> pretStr)) throw EroareDateIncomplete("Pretul nu a putut fi citit ca prim token.");
        double pret = stod(pretStr);

        string restulParametri;
        getline(ssPret >> ws, restulParametri);

        stringstream ssRestul(restulParametri);
        vector<string> parametriTokens;
        while (ssRestul >> token) {
            parametriTokens.push_back(token);
        }

        if (parametriTokens.size() < 2) {
            throw EroareDateIncomplete("Lipsesc Anul sau Genul.");
        }

        string gen = parametriTokens.back(); parametriTokens.pop_back();
        int anAparitie = stoi(parametriTokens.back()); parametriTokens.pop_back();

        vector<string> paramSpecifici = parametriTokens;

        if (tipProdus == "CD") {
            if (paramSpecifici.size() < 1) throw EroareDateIncomplete("Lipseste numarul de piese CD.");
            int nrPiese = stoi(paramSpecifici[0]);
            return make_unique<CD>(titlu, artist, anAparitie, gen, pret, nrPiese);
        }
        else if (tipProdus == "VINIL") {
            if (paramSpecifici.size() < 1) throw EroareDateIncomplete("Lipseste RPM Vinil.");
            int rpm = stoi(paramSpecifici[0]);
            return make_unique<Vinil>(titlu, artist, anAparitie, gen, pret, rpm);
        }
        else if (tipProdus == "CASETA") {
            if (paramSpecifici.size() < 1) throw EroareDateIncomplete("Lipseste tipul de banda Caseta.");
            string tipBanda = paramSpecifici[0];
            return make_unique<Caseta>(titlu, artist, anAparitie, gen, pret, tipBanda);
        }
        else if (tipProdus == "MERCHANDISE") {
            if (paramSpecifici.size() < 2) throw EroareDateIncomplete("Lipsesc culoarea si materialul Merchandise.");
            string culoare = paramSpecifici[0];
            string material = paramSpecifici[1];
            return make_unique<Merchandise>(titlu, artist, anAparitie, gen, pret, culoare, material);
        }
        else {
            throw EroareFormatNecunoscut("Tip de produs necunoscut: " + tipProdus);
        }
    } catch (const EroareMuzicala&) {
        throw;
    } catch (const exception& e) {
        throw EroareDateIncomplete("Eroare la conversia finala/parametri pentru produs: " + string(e.what()));
    }
}


void citesteComanda(ifstream& fin, Magazin& magazin) {
    string line;

    if (!getline(fin, line) || line.empty() || line.starts_with("#")) return;
    string numeClient = line;

    if (!getline(fin, line) || line.empty() || line.starts_with("#")) return;
    string emailClient = line;

    int n = 0;
    if (!(fin >> n)) return;
    fin.ignore();

    CosCumparaturi cosComanda;

    for (int i = 0; i < n; i++) {
        if (!getline(fin, line)) break;
        if (line.empty() || line.starts_with("#")) continue;

        try {
            cosComanda.adaugaProdus(parseProdus(line));
        } catch (const EroareMuzicala& e) {
            cerr << "AVERTISMENT la citire (Exceptie Muzicala): " << e.what() << " in linia: " << line << " (Ignorat)\n";
        } catch (const exception& e) {
            cerr << "AVERTISMENT la citire (Eroare Generica): " << e.what() << " in linia: " << line << " (Ignorat)\n";
        }
    }

    getline(fin, line);

    if (!cosComanda.produse.empty()) {
        Client client(numeClient, emailClient);
        Comanda comanda(client, move(cosComanda));
        magazin.adaugaComanda(comanda);
    }
}

int main() {
    ifstream fin("tastatura.txt");
    if (!fin) {
        cerr << "EROARE: Nu am putut deschide tastatura.txt.\n";
        return 1;
    }

    Magazin magazin("Magazin Muzical Polimorfic");

    cout << ">>> Incarcare date din tastatura.txt (Citire polimorfica)...\n";

    try {
        while (fin.peek() != EOF) {
            citesteComanda(fin, magazin);
        }
    } catch (const exception& e) {
        cerr << "\n[EROARE FATALA LA CITIRE]: " << e.what() << "\n";
        fin.close();
        return 1;
    }
    fin.close();

    cout << "\n>>> SCENARIU DE UTILIZARE A TUTUROR FUNCTIILOR <<<\n";
    cout << "----------------------------------------------------\n";

    cout << magazin;

    cout << "----------------------------------------------------\n";

    cout << "\n[Functii de Nivel Inalt & Static]\n";
    cout << "Numar total comenzi: " << magazin.numarComenzi() << "\n";
    cout << "Venit total magazin: " << fixed << setprecision(2) << magazin.venitTotal() << " RON\n";
    cout << "Total produse muzicale create (Static): " << ProdusMuzical::getNumarTotalProduse() << "\n";

    string artistCautat = "Pink Floyd";
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

        cout << "\n--- TEST DYNAMIC_CAST (AFISARE VINILURI) ---\n";
        magazin.getComenzi()[0].getCos().afiseazaDoarViniluri();

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

        Client clientTarget(magazin.getComenzi()[0].getClient().getNume(), magazin.getComenzi()[0].getClient().getEmail());
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