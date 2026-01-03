#include "../headers/ProdusMuzicalDummy.h"
#include <iostream>

ProdusMuzicalDummy::ProdusMuzicalDummy()
    : ProdusMuzical("Album Dummy", "Artist Dummy", 2025, "Gen Dummy", 10.0) {}

void ProdusMuzicalDummy::afiseazaDetalii(std::ostream& os) const {
    os << "[Produs Dummy] " << getTitlu() << " - " << getArtist() << "\n";
}

double ProdusMuzicalDummy::calculeazaTaxa() const {
    return 0.0;
}

std::unique_ptr<ProdusMuzical> ProdusMuzicalDummy::clone() const {
    return std::make_unique<ProdusMuzicalDummy>(*this);
}