#ifndef COMANDA_LIVRARE_H
#define COMANDA_LIVRARE_H

#include "Comanda.h"
#include <string>

class ComandaLivrare : public Comanda {
private:
    std::string adresaLivrare;
    double costBazaLivrare;
    bool esteUrgenta;

protected:
    void afiseazaDetaliiComanda(std::ostream& os) const override;

public:
    ComandaLivrare(const Client& client, CosCumparaturi cos,
                   const std::string& adresa, double costBaza, bool urgent = false);

    ComandaLivrare(const ComandaLivrare& other);
    ComandaLivrare& operator=(const ComandaLivrare& other);
    ComandaLivrare(ComandaLivrare&& other) noexcept = default;
    ComandaLivrare& operator=(ComandaLivrare&& other) noexcept = default;
    ~ComandaLivrare() override = default;

    double calculeazaTotalComanda() const override;

    std::unique_ptr<Comanda> clone() const override;

    const std::string& getAdresaLivrare() const { return adresaLivrare; }

    friend void swap(ComandaLivrare& first, ComandaLivrare& second) noexcept;
};

#endif // COMANDA_LIVRARE_H