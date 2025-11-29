#ifndef VINIL_H
#define VINIL_H
#include "PRODUSMUZICAL.h"

class Vinil : public ProdusMuzical {
private:
    int rpm;
public:
    // constructori 5 de baza unul specific
    Vinil(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, int rpm);
    ~Vinil() override = default;


    double calculeazaTaxa() const override;
    void afiseazaDetalii(std::ostream& os) const override;
    ProdusMuzical* clone() const override;


    Vinil(const Vinil& other);
    Vinil& operator=(Vinil other);
};
#endif