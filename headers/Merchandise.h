#ifndef MERCHANDISE_H
#define MERCHANDISE_H

#include "ProdusMuzical.h"
#include <string>
#include <memory>

class Merchandise : public ProdusMuzical {
private:
    std::string culoare;
    std::string material;

public:
    Merchandise(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret,
                const std::string& culoare, const std::string& material);
    ~Merchandise() override = default;

    double calculeazaTaxa() const override;
    void afiseazaDetalii(std::ostream& os) const override;
    std::unique_ptr<ProdusMuzical> clone() const override;

    Merchandise(const Merchandise& other);
    Merchandise& operator=(Merchandise other);

    bool estePremium() const;

private:
    friend void swap(Merchandise& first, Merchandise& second);
};

#endif // MERCHANDISE_H