#include "PRODUSMUZICAL.h"
#include "EroriMuzicale.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <iomanip>

int ProdusMuzical::numarTotalProduse = 0;
int ProdusMuzical::next_id = 1;

ProdusMuzical::ProdusMuzical(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret)
    : titlu(titlu), artist(artist), an_aparitie(an_aparitie), gen(gen), pret(pret) {

    if (pret <= 0) {
        throw EroarePretInvalid("Pretul trebuie sa fie pozitiv.");
    }
    if (titlu.empty() || artist.empty()) {
        throw EroareDateIncomplete("Titlu si Artist sunt campuri obligatorii.");
    }

    this->id_produs = next_id++;
    numarTotalProduse++;
}

ProdusMuzical::ProdusMuzical(const ProdusMuzical& other)
    : titlu(other.titlu), artist(other.artist), an_aparitie(other.an_aparitie), gen(other.gen), pret(other.pret), id_produs(other.id_produs) {}

void swap(ProdusMuzical& first, ProdusMuzical& second) {
    using std::swap;
    swap(first.titlu, second.titlu);
    swap(first.artist, second.artist);
    swap(first.an_aparitie, second.an_aparitie);
    swap(first.gen, second.gen);
    swap(first.pret, second.pret);
    swap(first.id_produs, second.id_produs);
}

void ProdusMuzical::afiseaza() const {
    std::cout << "  [ID: " << id_produs << "] ";
    afiseazaDetalii(std::cout);
    std::cout << " | Pret: " << std::fixed << std::setprecision(2) << pret << " RON";
    std::cout << " | Taxa: " << std::fixed << std::setprecision(2) << calculeazaTaxa() << " RON";
    std::cout << " | Total: " << std::fixed << std::setprecision(2) << pret + calculeazaTaxa() << " RON";
    std::cout << "\n";
}