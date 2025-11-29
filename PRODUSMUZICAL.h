#ifndef PRODUSMUZICAL_H
#define PRODUSMUZICAL_H

#include <string>
#include <ostream>
#include <utility>

class ProdusMuzical {
private:
    std::string titlu;
    std::string artist;
    int an_aparitie;
    std::string gen;
    double pret;
    int id_produs;

    static int next_id;
    static int numarTotalProduse;

protected:
    virtual void afiseazaDetalii(std::ostream& os) const = 0;
    ProdusMuzical(const ProdusMuzical& other);

public:
    ProdusMuzical(const std::string& titlu, const std::string& artist, int an_aparitie, const std::string& gen, double pret);
    virtual ~ProdusMuzical() = default;

    ProdusMuzical& operator=(const ProdusMuzical& other) = delete;
    ProdusMuzical& operator=(ProdusMuzical&& other) = delete;

    virtual double calculeazaTaxa() const = 0;
    virtual ProdusMuzical* clone() const = 0;

    void afiseaza() const;

    double getPret() const { return pret; }
    const std::string& getArtist() const { return artist; }
    int getIdProdus() const { return id_produs; }
    int getAnAparitie() const { return an_aparitie; }
    const std::string& getTitlu() const { return titlu; }
    const std::string& getGen() const { return gen; }

    static int getNumarTotalProduse() { return numarTotalProduse; }

    friend void swap(ProdusMuzical& first, ProdusMuzical& second);
};

#endif // PRODUSMUZICAL_H