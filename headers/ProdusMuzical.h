#ifndef PRODUSMUZICAL_H
#define PRODUSMUZICAL_H

#include <string>
#include <ostream>
#include <utility>
#include <memory>

/**
 * @class ProdusMuzical
 * @brief Abstract base class representing a generic musical product.
 *
 * This class defines the common interface and properties for all products
 * sold in the store (CD, Vinyl, Cassette, Merchandise).
 */
class ProdusMuzical {
private:
    std::string titlu;
    std::string artist;
    int anAparitie;
    std::string gen;
    double pret;
    int idProdus;

    static size_t nextId; ///< Static counter for generating unique IDs.
    static size_t numarTotalProduse; ///< Static counter for tracking total active products.

protected:
    /**
     * @brief Helper function to print specific details of the derived class.
     * @param os The output stream.
     */
    virtual void afiseazaDetalii(std::ostream &os) const = 0;

    /**
     * @brief Copy constructor (protected to prevent slicing).
     * @param other The object to copy from.
     */
    ProdusMuzical(const ProdusMuzical &other);

public:
    /**
     * @brief Constructor for ProdusMuzical.
     * @param titlu The title of the product.
     * @param artist The artist or band name.
     * @param anAparitie Year of release.
     * @param gen Music genre.
     * @param pret Base price of the product.
     * @throws EroarePretInvalid If the price is negative or zero.
     */
    ProdusMuzical(const std::string &titlu, const std::string &artist, int anAparitie, const std::string &gen,
                  double pret);


    virtual ~ProdusMuzical();

    // Disable assignment operator to enforce immutability of ID or force clone usage.
    ProdusMuzical &operator=(const ProdusMuzical &other) = delete;

    ProdusMuzical &operator=(ProdusMuzical &&other) = delete;

    /**
     * @brief Calculates the tax specific to the product type.
     * @return The calculated tax amount.
     */
    virtual double calculeazaTaxa() const = 0;

    /**
     * @brief Creates a deep copy of the product using the Virtual Constructor Idiom.
     * @return A unique_ptr to the cloned object.
     */
    virtual std::unique_ptr<ProdusMuzical> clone() const = 0;

    /**
     * @brief Displays full details of the product to the standard output.
     */
    void afiseaza() const;

    // Getters
    double getPret() const { return pret; }
    const std::string &getArtist() const { return artist; }
    int getIdProdus() const { return idProdus; }
    int getAnAparitie() const { return anAparitie; }
    const std::string &getTitlu() const { return titlu; }
    const std::string &getGen() const { return gen; }

    static size_t getNumarTotalProduse() { return numarTotalProduse; }

    friend void swap(ProdusMuzical &first, ProdusMuzical &second);
};

#endif // PRODUSMUZICAL_H
