#ifndef CD_H
#define CD_H

#include "PRODUSMUZICAL.h"

class CD : public ProdusMuzical {
private:
    int nr_piese;

public:
    CD(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, int nr_piese);
    CD(const CD& other);

    CD& operator=(CD other);

    ProdusMuzical* clone() const override;

    double calculeazaTaxa() const override;

protected:
    void afiseazaDetalii(std::ostream& os) const override;

private:

    friend void swap(CD& first, CD& second);
};

#endif // CD_H