#include "ProdusMuzical.h"
#include "EroriMuzicale.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

size_t ProdusMuzical::nextId = 1;
size_t ProdusMuzical::numarTotalProduse = 0;

ProdusMuzical::ProdusMuzical(const std::string& titlu, const std::string& artist, int anAparitie, const std::string& gen, double pret)
    : titlu(titlu), artist(artist), anAparitie(anAparitie), gen(gen), idProdus(nextId++)
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
      anAparitie(other.anAparitie),
      gen(other.gen),
      pret(other.pret),
      idProdus(nextId++) {
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
    std::cout << "--- Produs #" << idProdus << " ---\n";
    std::cout << "Titlu: " << titlu << "\n";
    std::cout << "Artist: " << artist << "\n";
    std::cout << "An: " << anAparitie << ", Gen: " << gen << "\n";
    std::cout << "Pret de baza: " << std::fixed << std::setprecision(2) << pret << " RON\n";


    afiseazaDetalii(std::cout);

    std::cout << "Taxa aplicata: " << std::fixed << std::setprecision(2) << calculeazaTaxa() << " RON\n";
    std::cout << "Pret final: " << std::fixed << std::setprecision(2) << (pret + calculeazaTaxa()) << " RON\n";
}

void swap(ProdusMuzical& first, ProdusMuzical& second) {
    using std::swap;
    swap(first.titlu, second.titlu);
    swap(first.artist, second.artist);
    swap(first.anAparitie, second.anAparitie);
    swap(first.gen, second.gen);
    swap(first.pret, second.pret);
}