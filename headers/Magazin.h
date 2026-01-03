#ifndef MAGAZIN_H
#define MAGAZIN_H

#include "Comanda.h"
#include "Client.h"
#include "ProdusMuzical.h"
#include <vector>
#include <string>
#include <ostream>

/**
 * @class Magazin
 * @brief Main class managing the music store.
 * Handles orders, reports, and filtering operations.
 */
class Magazin {
private:
    std::string nume;
    std::vector<Comanda> comenzi;

public:
    explicit Magazin(const std::string &nume);

    const std::string &getNume() const { return nume; }

    /**
     * @brief Adds a new order to the store's records.
     * @param c The order object to add.
     */
    void adaugaComanda(const Comanda &c);

    /**
     * @brief Calculates the total revenue from all orders.
     * @return Total revenue.
     */
    double venitTotal() const;

    int numarComenzi() const;

    /**
     * @brief Sorts internal orders list by total value (ascending).
     */
    void sorteazaComenziDupaValoare();

    /**
     * @brief Filters orders that contain products from a specific artist.
     * @param artistCautat Name of the artist to search for.
     * @return A vector of orders matching the criteria.
     */
    std::vector<Comanda> filtreazaComenziDupaArtist(const std::string &artistCautat) const;

    /**
     * @brief Updates an existing client's order by adding a new product.
     * @param client The client to search for.
     * @param produs_nou The product to add to their cart.
     * @return True if update succeeded, False otherwise.
     */
    bool actualizeazaComanda(const Client &client, const ProdusMuzical &produs_nou);

    /**
     * @brief Prints a report of the top N most valuable orders.
     * @param topN Number of top orders to display.
     */
    void raportComenziTop(int topN) const;

    const std::vector<Comanda> &getComenzi() const { return comenzi; }

    friend std::ostream &operator<<(std::ostream &os, const Magazin &m);
};

#endif // MAGAZIN_H
