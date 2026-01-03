#ifndef CD_H
#define CD_H

#include "ProdusMuzical.h"
#include <memory>

/**
 * @class CD
 * @brief Represents a Compact Disc product.
 * Inherits from ProdusMuzical and adds track count information.
 */
class CD : public ProdusMuzical {
private:
    int nrPiese;

public:
    /**
     * @brief Constructor for CD.
     * @param titlu Title of the CD.
     * @param artist Name of the artist.
     * @param anAparitie Release year.
     * @param gen Music genre.
     * @param pret Base price.
     * @param nrPiese Number of tracks on the CD.
     */
    CD(const std::string &titlu, const std::string &artist, int anAparitie, const std::string &gen, double pret,
       int nrPiese);

    CD(const CD &other);

    CD &operator=(CD other);

    std::unique_ptr<ProdusMuzical> clone() const override;

    /**
     * @brief Calculates tax for CD (e.g., 5% of base price).
     * @return Tax amount.
     */
    double calculeazaTaxa() const override;

protected:
    void afiseazaDetalii(std::ostream &os) const override;

private:
    friend void swap(CD &first, CD &second);
};

#endif // CD_H
