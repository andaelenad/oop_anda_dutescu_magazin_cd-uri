#ifndef CASETA_H
#define CASETA_H

#include "ProdusMuzical.h"
#include <memory>
#include <string>

class Caseta : public ProdusMuzical {
private:
    std::string tipBanda; // Ex: Normal, CrO2, Metal

public:
    Caseta(const std::string &titlu, const std::string &artist, int anAparitie, const std::string &gen, double pret,
           const std::string &tipBanda);

    ~Caseta() override = default;

    double calculeazaTaxa() const override;

    void afiseazaDetalii(std::ostream &os) const override;

    std::unique_ptr<ProdusMuzical> clone() const override;

    Caseta(const Caseta &other);

    Caseta &operator=(Caseta other);

private:
    friend void swap(Caseta &first, Caseta &second);
};

#endif // CASETA_H
