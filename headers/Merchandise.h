#ifndef MERCHANDISE_H
#define MERCHANDISE_H

#include "ProdusMuzical.h"
#include <string>
#include <memory>

/**
 * @class Merchandise
 * @brief Represents non-musical items like t-shirts or accessories.
 * Inherits from ProdusMuzical and includes color and material details.
 */
class Merchandise : public ProdusMuzical {
private:
    std::string culoare;
    std::string material;

public:
    /**
     * @brief Constructor for Merchandise.
     * @param titlu Item name.
     * @param artist Related artist.
     * @param anAparitie Release year.
     * @param gen Associated genre.
     * @param pret Base price.
     * @param culoare Item color.
     * @param material Material (e.g., "Cotton", "Leather").
     */
    Merchandise(const std::string &titlu, const std::string &artist, int anAparitie, const std::string &gen,
                double pret,
                const std::string &culoare, const std::string &material);

    ~Merchandise() override = default;

    /**
     * @brief Calculates tax for Merchandise. Higher tax for premium materials.
     * @return Tax amount.
     */
    double calculeazaTaxa() const override;

    void afiseazaDetalii(std::ostream &os) const override;

    std::unique_ptr<ProdusMuzical> clone() const override;

    Merchandise(const Merchandise &other);

    Merchandise &operator=(Merchandise other);

    /**
     * @brief Checks if the merchandise is considered premium based on material.
     * @return True if material is premium (e.g., Leather, Wool), false otherwise.
     */
    bool estePremium() const;

private:
    friend void swap(Merchandise &first, Merchandise &second);
};

#endif // MERCHANDISE_H
