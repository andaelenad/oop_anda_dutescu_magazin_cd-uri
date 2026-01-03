#ifndef COMANDA_H
#define COMANDA_H

#include "Client.h"
#include "CosCumparaturi.h"
#include <ostream>
#include <vector>
#include <memory>

/**
 * @class Comanda
 * @brief Represents a base order placed by a client containing a shopping cart.
 */
class Comanda {
private:
    Client client;
    CosCumparaturi cos;

protected:
    /**
     * @brief Helper to display specific details of the order.
     * Can be overridden by derived classes (e.g., delivery info).
     * @param os Output stream.
     */
    virtual void afiseazaDetaliiComanda(std::ostream &os) const;

public:
    /**
     * @brief Constructor for Comanda.
     * @param c The client placing the order.
     * @param c_data The shopping cart associated with the order.
     */
    Comanda(const Client &c, CosCumparaturi c_data);

    virtual ~Comanda() = default;

    Comanda(const Comanda &other);

    Comanda &operator=(Comanda other);

    /**
     * @brief Calculates the total value of the order.
     * @return Total value.
     */
    virtual double calculeazaTotalComanda() const;

    /**
     * @brief Creates a deep copy of the order (polymorphic clone).
     * @return Unique pointer to the new order.
     */
    virtual std::unique_ptr<Comanda> clone() const;

    int numarProduse() const;

    const Client &getClient() const;

    const CosCumparaturi &getCos() const { return cos; }
    CosCumparaturi &getCos() { return cos; }

    friend std::ostream &operator<<(std::ostream &os, const Comanda &com);
};

#endif
