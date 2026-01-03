#ifndef CASETA_H
#define CASETA_H

#include "ProdusMuzical.h"
#include <memory>
#include <string>

/**
 * @class Caseta
 * @brief Represents a Cassette Tape product.
 * Inherits from ProdusMuzical and adds tape type information.
 */
class Caseta : public ProdusMuzical {
private:
    std::string tipBanda; // Ex: Normal, CrO2, Metal

public:
    /**
     * @brief Constructor for Caseta.
     * @param titlu Title of the cassette.
     * @param artist Artist name.
     * @param anAparitie Release year.
     * @param gen Genre.
     * @param pret Base price.
     * @param tipBanda Type of the tape (e.g., "Normal", "Metal").
     */
    Caseta(const std::string &titlu, const std::string &artist, int anAparitie, const std::string &gen, double pret,
           const std::string &tipBanda);

    ~Caseta() override = default;

    /**
     * @brief Calculates tax for Caseta.
     * @return Tax amount.
     */
    double calculeazaTaxa() const override;

    void afiseazaDetalii(std::ostream &os) const override;

    std::unique_ptr<ProdusMuzical> clone() const override;

    Caseta(const Caseta &other);

    Caseta &operator=(Caseta other);

private:
    friend void swap(Caseta &first, Caseta &second);
};

#endif // CASETA_H
