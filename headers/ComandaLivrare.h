#ifndef COMANDA_LIVRARE_H
#define COMANDA_LIVRARE_H

#include "Comanda.h"
#include <string>

/**
 * @class ComandaLivrare
 * @brief Extends Comanda to include delivery details.
 * Adds delivery address, base shipping cost, and urgency handling.
 */
class ComandaLivrare : public Comanda {
private:
    std::string adresaLivrare;
    double costBazaLivrare;
    bool esteUrgenta;

protected:
    void afiseazaDetaliiComanda(std::ostream &os) const override;

public:
    /**
     * @brief Constructor for ComandaLivrare.
     * @param client Client placing the order.
     * @param cos Shopping cart.
     * @param adresa Delivery address.
     * @param costBaza Base cost for shipping.
     * @param urgent Flag indicating if the order is urgent (adds surcharge).
     */
    ComandaLivrare(const Client &client, CosCumparaturi cos,
                   const std::string &adresa, double costBaza, bool urgent = false);

    ComandaLivrare(const ComandaLivrare &other);

    ComandaLivrare &operator=(const ComandaLivrare &other);

    // Move semantics
    ComandaLivrare(ComandaLivrare &&other) noexcept = default;

    ComandaLivrare &operator=(ComandaLivrare &&other) noexcept = default;

    ~ComandaLivrare() override = default;

    /**
     * @brief Calculates total including shipping and urgency fees.
     * @return Total order value.
     */
    double calculeazaTotalComanda() const override;

    std::unique_ptr<Comanda> clone() const override;

    const std::string &getAdresaLivrare() const { return adresaLivrare; }

    friend void swap(ComandaLivrare &first, ComandaLivrare &second) noexcept;
};

#endif // COMANDA_LIVRARE_H
