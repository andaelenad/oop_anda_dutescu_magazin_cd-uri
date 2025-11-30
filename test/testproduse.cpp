// test/testproduse.cpp

#include "gtest/gtest.h"
#include "../CD.h"
#include "../VINIL.h"
#include "../CASETA.h"
#include "../MERCHANDISE.h"
#include "../COS_CUMPARATURI.h"
#include "../COMANDA.h"
#include "../EroriMuzicale.h"
#include <memory>
#include <sstream>

using namespace std;

TEST(ProdusTaxaTest, CalculeazaTaxaCD) {
    CD c("Album CD", "Artist", 2020, "Pop", 100.0, 10);
    ASSERT_NEAR(c.calculeazaTaxa(), 5.0, 0.001);
}

TEST(ProdusTaxaTest, CalculeazaTaxaVinil) {
    Vinil v("Album Vinil", "Artist", 1990, "Rock", 200.0, 33);
    ASSERT_NEAR(v.calculeazaTaxa(), 30.0, 0.001);
}

TEST(ProdusTaxaTest, CalculeazaTaxaCaseta) {
    Caseta k("Album Caseta", "Artist", 1985, "Blues", 50.0, "Crom");
    ASSERT_NEAR(k.calculeazaTaxa(), 5.0, 0.001);
}

TEST(ProdusTaxaTest, CalculeazaTaxaMerchandise) {
    Merchandise m("Tricou", "A", 2024, "M", 50.0, "Negru", "Bumbac");
    ASSERT_NEAR(m.calculeazaTaxa(), 8.0, 0.001);
}

TEST(ExceptiiTest, ConstructorAruncaEroarePretInvalid) {
    ASSERT_THROW({
        CD c("Produs Invalid", "A", 2020, "P", -10.0, 10);
    }, EroarePretInvalid);
}

TEST(ExceptiiTest, MesajEroarePersonalizat) {
    try {
        CD c("Produs Invalid", "A", 2020, "P", -1.0, 10);
        FAIL() << "Exceptia EroarePretInvalid nu a fost aruncata.";
    } catch (const EroarePretInvalid& e) {
        EXPECT_STREQ("Pretul produsului nu poate fi negativ.", e.what());
    }
}

TEST(MemorieTest, ClonareFunctioneazaCorect) {
    Vinil original("Original", "A", 2020, "P", 50.0, 33);
    auto clona = original.clone();

    Vinil* clona_vinil = dynamic_cast<Vinil*>(clona.get());
    ASSERT_NE(clona_vinil, nullptr);

    ASSERT_NE(original.getIdProdus(), clona->getIdProdus());

    ASSERT_EQ(original.getTitlu(), clona->getTitlu());
}

TEST(MemorieTest, CopyConstructorComanda) {
    Client client("Ion Pop", "ion@example.com");
    CosCumparaturi cosOriginal;
    cosOriginal.adaugaProdus(make_unique<CD>("Hit", "B", 2020, "P", 10.0, 1));
    Comanda original(client, std::move(cosOriginal));

    Comanda copie = original;

    ASSERT_EQ(original.getClient().getNume(), copie.getClient().getNume());

    ASSERT_NEAR(original.calculeazaTotalCuTaxe(), copie.calculeazaTotalCuTaxe(), 0.001);
}

TEST(MerchandiseTest, EstePremiumLogic) {
    Merchandise m1("Geaca", "A", 2024, "M", 900.0, "Negru", "Piele");
    ASSERT_TRUE(m1.estePremium());

    Merchandise m2("Tricou", "A", 2024, "M", 50.0, "Alb", "Bumbac");
    ASSERT_FALSE(m2.estePremium());
}

TEST(CasetaTest, GetTipBanda) {
    Caseta k("Album", "A", 1985, "Jazz", 30.0, "Ferro");
    ASSERT_EQ(k.getTipBanda(), "Ferro");
}

TEST(CosCumparaturiTest, CalculeazaTotal) {
    CosCumparaturi cos;
    cos.adaugaProdus(make_unique<CD>("CD_Test", "A", 2020, "P", 50.0, 1));
    cos.adaugaProdus(make_unique<Merchandise>("Merch_Test", "B", 2024, "M", 100.0, "Alb", "Plastic"));

    ASSERT_NEAR(cos.calculeazaTotal(), 160.50, 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}