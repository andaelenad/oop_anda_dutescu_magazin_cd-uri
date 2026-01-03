#ifndef VINIL_H
#define VINIL_H

#include "ProdusMuzical.h"
#include <memory>

/**
 * @class Vinil
 * @brief Represents a Vinyl Record musical product.
 * Inherits from ProdusMuzical and adds RPM (Revolutions Per Minute) specific details.
 */
class Vinil : public ProdusMuzical {
private:
    int rpm;

public:
    /**
     * @brief Constructor for Vinil.
     * @param titlu Title of the vinyl record.
     * @param artist Artist name.
     * @param anAparitie Year of release.
     * @param gen Music genre.
     * @param pret Base price.
     * @param rpm Rotation speed (e.g., 33, 45, 78).
     */
    Vinil(const std::string &titlu, const std::string &artist, int anAparitie, const std::string &gen, double pret,
          int rpm);

    ~Vinil() override = default;

    /**
     * @brief Calculates tax for Vinil.
     * Typically includes a vintage tax or fragile item tax.
     * @return Tax amount.
     */
    double calculeazaTaxa() const override;

    /**
     * @brief Creates a deep copy of the vinyl object.
     * @return Unique pointer to the cloned object.
     */
    std::unique_ptr<ProdusMuzical> clone() const override;

    Vinil(const Vinil &other);

    Vinil &operator=(Vinil other);

protected:
    void afiseazaDetalii(std::ostream &os) const override;

private:
    friend void swap(Vinil &first, Vinil &second);
};

#endif // VINIL_H
