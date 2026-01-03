#ifndef VINIL_H
#define VINIL_H

#include "ProdusMuzical.h"
#include <memory>

class Vinil : public ProdusMuzical {
private:
    int rpm;

public:
    // Constructor
    Vinil(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, int rpm);
    ~Vinil() override = default;


    double calculeazaTaxa() const override;


    std::unique_ptr<ProdusMuzical> clone() const override;


    Vinil(const Vinil& other);
    Vinil& operator=(Vinil other);

protected:
    void afiseazaDetalii(std::ostream& os) const override;

private:

    friend void swap(Vinil& first, Vinil& second);
};

#endif // VINIL_H