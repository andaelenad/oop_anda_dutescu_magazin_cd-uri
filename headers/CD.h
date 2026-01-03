#ifndef CD_H
#define CD_H

#include "ProdusMuzical.h"
#include <memory>

class CD : public ProdusMuzical {
private:
    int nr_piese;

public:
    CD(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret, int nr_piese);

    CD(const CD& other);


    CD& operator=(CD other);


    std::unique_ptr<ProdusMuzical> clone() const override;

    double calculeazaTaxa() const override;

protected:
    void afiseazaDetalii(std::ostream& os) const override;

private:

    friend void swap(CD& first, CD& second);
};

#endif // CD_H