#ifndef PRODUSMUZICALDUMMY_H
#define PRODUSMUZICALDUMMY_H

#include "ProdusMuzical.h"

/**
 * @class ProdusMuzicalDummy
 * @brief A dummy class used for testing purposes.
 */
class ProdusMuzicalDummy : public ProdusMuzical {
public:
    ProdusMuzicalDummy();
    void afiseazaDetalii(std::ostream& os) const override;
    double calculeazaTaxa() const override;
    std::unique_ptr<ProdusMuzical> clone() const override;
};

#endif // PRODUSMUZICALDUMMY_H