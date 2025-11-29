#ifndef CASETA_H
#define CASETA_H
#include "PRODUSMUZICAL.h"

class Caseta : public ProdusMuzical {
private:
    std::string tip_banda; // Ex: Normal, CrO2, Metal
public:
    // Constructorul primeste 5 parametri de baza + 1 specific
    Caseta(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, const std::string& tip_banda);
    ~Caseta() override = default;

    // Implementari functii virtuale
    double calculeazaTaxa() const override;
    void afiseazaDetalii(std::ostream& os) const override;
    ProdusMuzical* clone() const override;

    // GESTIUNE MEMORIE: Copy and Swap
    Caseta(const Caseta& other);
    Caseta& operator=(Caseta other);
};
#endif