#include "ProdusMuzical.h"
#include "EroriMuzicale.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

size_t ProdusMuzical::next_id = 1;
size_t ProdusMuzical::numarTotalProduse = 0;

ProdusMuzical::ProdusMuzical(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret)
    : titlu(titlu), artist(artist), an_aparitie(an_aparitie), gen(gen), id_produs(next_id++)
{

    if (pret <= 0.0) {
        throw EroarePretInvalid("Pretul produsului trebuie sa fie strict pozitiv.");
    }
    this->pret = pret;
    numarTotalProduse++;
}

ProdusMuzical::ProdusMuzical(const ProdusMuzical& other)
    : titlu(other.titlu),
      artist(other.artist),
      an_aparitie(other.an_aparitie),
      gen(other.gen),
      pret(other.pret),
      id_produs(next_id++) {
    numarTotalProduse++;
    (void)other.getIdProdus();
    (void)other.getAnAparitie();
    (void)other.getTitlu();
    (void)other.getGen();
    (void)getNumarTotalProduse();
}

ProdusMuzical::~ProdusMuzical() {
    numarTotalProduse--;
}

void ProdusMuzical::afiseaza() const {
    std::cout << "--- Produs #" << id_produs << " ---\n";
    std::cout << "Titlu: " << titlu << "\n";
    std::cout << "Artist: " << artist << "\n";
    std::cout << "An: " << an_aparitie << ", Gen: " << gen << "\n";
    std::cout << "Pret de baza: " << std::fixed << std::setprecision(2) << pret << " RON\n";


    afiseazaDetalii(std::cout);

    std::cout << "Taxa aplicata: " << std::fixed << std::setprecision(2) << calculeazaTaxa() << " RON\n";
    std::cout << "Pret final: " << std::fixed << std::setprecision(2) << (pret + calculeazaTaxa()) << " RON\n";
}

void swap(ProdusMuzical& first, ProdusMuzical& second) {
    using std::swap;
    swap(first.titlu, second.titlu);
    swap(first.artist, second.artist);
    swap(first.an_aparitie, second.an_aparitie);
    swap(first.gen, second.gen);
    swap(first.pret, second.pret);
}