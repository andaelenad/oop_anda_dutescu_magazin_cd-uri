#ifndef PRODUSFACTORY_H
#define PRODUSFACTORY_H

#include "ProdusMuzical.h"
#include "CD.h"
#include "Vinil.h"
#include "Caseta.h"
#include "Merchandise.h"
#include "EroriMuzicale.h"
#include <memory>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class ProdusFactory {
public:
    static std::unique_ptr<ProdusMuzical> createProdus(const json& item) {
        std::string tip = item.at("tip").get<std::string>();
        std::string titlu = item.at("titlu").get<std::string>();
        std::string artist = item.at("artist").get<std::string>();
        int anAparitie = item.at("anAparitie").get<int>();
        std::string gen = item.at("gen").get<std::string>();
        double pret = item.at("pret").get<double>();

        if (pret <= 0) {
            throw EroarePretInvalid("Pret invalid (" + std::to_string(pret) + ") pentru: " + titlu);
        }

        if (tip == "CD") {
            int nrPiese = item.at("viteza").get<int>();
            return std::make_unique<CD>(titlu, artist, anAparitie, gen, pret, nrPiese);
        } else if (tip == "VINIL") {
            int rpm = item.at("rpm").get<int>();
            return std::make_unique<Vinil>(titlu, artist, anAparitie, gen, pret, rpm);
        } else if (tip == "CASETA") {
            std::string tipBanda = item.at("tip_banda").get<std::string>();
            return std::make_unique<Caseta>(titlu, artist, anAparitie, gen, pret, tipBanda);
        } else if (tip == "MERCHANDISE") {
            std::string culoare = item.at("culoare").get<std::string>();
            std::string material = item.at("material").get<std::string>();
            return std::make_unique<Merchandise>(titlu, artist, anAparitie, gen, pret, culoare, material);
        } else {
            throw EroareFormatNecunoscut("Tip produs necunoscut: " + tip);
        }
    }
};

#endif // PRODUSFACTORY_H