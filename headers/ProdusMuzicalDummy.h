#ifndef PRODUSMUZICALDUMMY_H
#define PRODUSMUZICALDUMMY_H

#include "ProdusMuzical.h"

/**
 * @class ProdusMuzicalDummy
 * @brief A concrete implementation of ProdusMuzical used strictly for testing purposes.
 * * This class allows instantiation of the abstract ProdusMuzical base class
 * to facilitate unit testing of logic that depends on musical products
 * without requiring complex derived classes like CD or Vinil.
 */
class ProdusMuzicalDummy : public ProdusMuzical {
public:
    /**
     * @brief Default constructor for ProdusMuzicalDummy.
     * Initializes the dummy product with placeholder data.
     */
    ProdusMuzicalDummy();

    /**
     * @brief Displays details specific to the dummy product.
     * @param os The output stream.
     */
    void afiseazaDetalii(std::ostream &os) const override;

    /**
     * @brief Calculates a dummy tax (usually 0.0 or a fixed small value).
     * @return The calculated tax.
     */
    double calculeazaTaxa() const override;

    /**
     * @brief Creates a copy of this dummy product.
     * @return A unique_ptr containing the cloned object.
     */
    std::unique_ptr<ProdusMuzical> clone() const override;
};

#endif // PRODUSMUZICALDUMMY_H
