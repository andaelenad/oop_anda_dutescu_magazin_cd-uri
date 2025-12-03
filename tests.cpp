// tests.cpp

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


#include "PRODUSMUZICAL.h"
#include "CD.h"
#include "VINIL.h"
#include "CASETA.h"
#include "MERCHANDISE.h"
#include "COMANDA.h"
#include "CLIENT.h"
#include "COS_CUMPARATURI.h"
#include "MAGAZIN.h"
#include "EroriMuzicale.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


Comanda createValidTestCommand() {
    Client clientTest("Test POO", "test@poo.com");
    CosCumparaturi cosTest;


    cosTest.adaugaProdus(std::make_unique<CD>("CD Test Original", "Artist A", 2020, "Rock", 50.0, 5));
    cosTest.adaugaProdus(std::make_unique<Vinil>("Vinil Test", "Artist B", 2021, "Jazz", 150.0, 33));
    cosTest.adaugaProdus(std::make_unique<Merchandise>("Tricou Test", "Artist X", 2023, "Pop", 30.0, "Negru", "Bumbac"));

    return Comanda(clientTest, std::move(cosTest));
}

// ----------------------------------------------------
// TESTE POO AVANSATE (Echivalent cu subMeniuTesteAvansate)
// ----------------------------------------------------

TEST_CASE("Test 1: Clonare (Constructor Virtual) & Deep Copy", "[POO_AVANSAT]") {
    // Simulează logica din Case 1 al subMeniuTesteAvansate
    Comanda c = createValidTestCommand();

    // Clonarea unui produs (Produsul 1 este Vinil Test)
    std::unique_ptr<ProdusMuzical> produsOriginal = c.getCos().produse[1]->clone();
    std::unique_ptr<ProdusMuzical> produsClonat = produsOriginal->clone();

    REQUIRE(produsClonat->getTitlu() == produsOriginal->getTitlu());
    // Verifică faptul că obiectele sunt diferite (ID-ul trebuie să fie unic)
    REQUIRE(produsClonat->getIdProdus() != produsOriginal->getIdProdus());
    REQUIRE(dynamic_cast<Vinil*>(produsClonat.get()) != nullptr);
}

TEST_CASE("Test 2: Copy Constructor Comanda (Deep Copy Cos)", "[POO_AVANSAT]") {

    Comanda comandaOriginala = createValidTestCommand();

    Comanda comandaCopie = comandaOriginala;

    REQUIRE(comandaCopie.getCos().produse.size() == comandaOriginala.getCos().produse.size());

    REQUIRE(comandaCopie.getCos().produse[0].get() != comandaOriginala.getCos().produse[0].get());

    REQUIRE(comandaCopie.calculeazaTotalCuTaxe() == comandaOriginala.calculeazaTotalCuTaxe());
}

TEST_CASE("Test 3: Dynamic Cast (Merchandise)", "[POLIMORFISM]") {
    // Test conceptual Dynamic Cast
    Merchandise merchPremium("Hoodie Premium", "Artist Y", 2024, "Pop", 120.0, "Alb", "Lână");

    std::unique_ptr<ProdusMuzical> ptrMerch = std::make_unique<Merchandise>(merchPremium);

    // Verifică dacă ProdusMuzical poate fi convertit la Merchandise
    REQUIRE(dynamic_cast<Merchandise*>(ptrMerch.get()) != nullptr);
}



TEST_CASE("Test 4: EroarePretInvalid (Pret <= 0)", "[EXCEPTII]") {
    // Echivalentul testului din Case 11 al meniuInteractiv
    REQUIRE_THROWS_AS(std::make_unique<CD>("Error CD Negativ", "Artist", 2024, "Pop", -5.0, 1), EroarePretInvalid);
    REQUIRE_THROWS_AS(std::make_unique<Caseta>("Error Caseta Zero", "Artist", 2024, "Pop", 0.0, "Normal"), EroarePretInvalid);
}

TEST_CASE("Test 5: EroareFormatNecunoscut (Constructor Exceptie)", "[EXCEPTII]") {
    REQUIRE_THROWS_AS([]{
        throw EroareFormatNecunoscut("Tip necunoscut: DVD");
    }(), EroareFormatNecunoscut);
}

TEST_CASE("Test 6: EroareDateIncomplete (Constructor Exceptie)", "[EXCEPTII]") {
    REQUIRE_THROWS_AS([]{
        throw EroareDateIncomplete("Fisierul comenzi.json nu a putut fi deschis.");
    }(), EroareDateIncomplete);
}

TEST_CASE("Test 7: EroareLogica (Cos Gol)", "[EXCEPTII]") {
    CosCumparaturi cosGol;

    REQUIRE_NOTHROW(cosGol.calculeazaTotalComanda());
    REQUIRE(cosGol.calculeazaTotalComanda() == 0.0);
}


TEST_CASE("Test 8: Calcul Total Comanda (Fără Approx)", "[FUNCTIONALITATE]") {
    CosCumparaturi cos;

    double pretCD = 10.0;
    double pretVinil = 100.0;
    double pretMerch = 50.0;

    cos.adaugaProdus(std::make_unique<CD>("Test Single", "Artist Test", 2024, "Pop", pretCD, 1));
    cos.adaugaProdus(std::make_unique<Vinil>("Test LP", "Artist Test", 2024, "Rock", pretVinil, 33));
    cos.adaugaProdus(std::make_unique<Merchandise>("Test Tricou", "Artist Test", 2024, "Pop", pretMerch, "Alb", "Bumbac"));

    double totalAsteptat = pretCD + pretVinil + pretMerch;

    // Corecție finală: Utilizarea comparației simple ==, evitând erorile de linking cu Catch::Approx
    REQUIRE(cos.calculeazaTotalComanda() == totalAsteptat);

    REQUIRE(cos.produse.size() == 3);
}

TEST_CASE("Test 9: Adaugare & Eliberare Memorie", "[FUNCTIONALITATE]") {
    CosCumparaturi cos;

    const size_t initialCount = ProdusMuzical::getNumarTotalProduse();

    cos.adaugaProdus(std::make_unique<CD>("A1", "B1", 2020, "R", 10.0, 1));
    cos.adaugaProdus(std::make_unique<Vinil>("A2", "B2", 2020, "R", 20.0, 33));

    REQUIRE(cos.produse.size() == 2);


    REQUIRE(ProdusMuzical::getNumarTotalProduse() == initialCount + 2);
}

