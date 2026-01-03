#ifndef COS_CUMPARATURI_H
#define COS_CUMPARATURI_H

#include "ProdusMuzical.h"
#include <vector>
#include <memory>
#include <utility>

/**
 * @class CosCumparaturi
 * @brief Manages a collection of musical products selected by a client.
 * Uses smart pointers to manage the lifecycle of products.
 */
class CosCumparaturi {
public:
    std::vector<std::unique_ptr<ProdusMuzical> > produse;

public:
    CosCumparaturi() = default;

    ~CosCumparaturi() = default;

    /**
     * @brief Adds a product to the cart.
     * @param p Unique pointer to the product to add.
     */
    void adaugaProdus(std::unique_ptr<ProdusMuzical> p);

    /**
     * @brief Calculates the sum of prices of all products in the cart.
     * @return Total price.
     */
    double calculeazaTotalComanda() const;

    /**
     * @brief Filters and displays only products of type Vinil using dynamic_cast.
     */
    void afiseazaDoarViniluri() const;

    CosCumparaturi(const CosCumparaturi &other);

    CosCumparaturi &operator=(CosCumparaturi other);
};

#endif // COS_CUMPARATURI_H
