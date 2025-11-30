// test/test_produse.cpp

#include "gtest/gtest.h"
#include "../CD.h"
#include "../VINIL.h"
#include "../MERCHANDISE.h"
#include "../COS_CUMPARATURI.h"
#include "../EroriMuzicale.h"
#include <memory>

using namespace std;

// --- 1. TESTAREA FUNCTIILOR VIRTUALE SI CORECTITUDINEA CALCULUI ---

TEST(ProdusTaxaTest, CalculeazaTaxaCD) {
    // CD-ul are taxa de 5%
    CD c("Album", "Artist", 2020, "Pop", 100.0, 10);
    ASSERT_NEAR(c.calculeazaTaxa(), 5.0, 0.001);
}

TEST(ProdusTaxaTest, CalculeazaTaxaVinil) {
    // Vinilul are taxa de 15%
    Vinil v("Album", "Artist", 1990, "Rock", 200.0, 33);
    ASSERT_NEAR(v.calculeazaTaxa(), 30.0, 0.001);
}

// Merchandise are taxa fixa de 8.0 RON
TEST(ProdusTaxaTest, CalculeazaTaxaMerchandise) {
    Merchandise m("Tricou", "A", 2024, "M", 50.0, "Negru", "Bumbac");
    ASSERT_NEAR(m.calculeazaTaxa(), 8.0, 0.001);

    Merchandise m_scump("Geaca", "A", 2024, "M", 900.0, "Piele", "Piele");
    ASSERT_NEAR(m_scump.calculeazaTaxa(), 8.0, 0.001);
}


// --- 2. TESTAREA IERARHIEI DE EXCEPTII PROPRII ---

TEST(ExceptiiTest, ConstructorAruncaEroarePretInvalid) {
    // Verifica daca constructorul CD-ului arunca EroarePretInvalid
    ASSERT_THROW({
        CD c("Produs Invalid", "A", 2020, "P", -10.0, 10);
    }, EroarePretInvalid);
}

TEST(ExceptiiTest, MesajEroarePersonalizat) {
    try {
        CD c("Produs Invalid", "A", 2020, "P", -1.0, 10);
        FAIL() << "Excepția EroarePretInvalid nu a fost aruncată.";
    } catch (const EroarePretInvalid& e) {
        EXPECT_STREQ("Pretul produsului nu poate fi negativ.", e.what());
    }
}


// --- 3. TESTAREA GESTIONARII MEMORIEI (CLONARE / CONSTRUCTOR VIRTUAL) ---

TEST(ProdusMuzicalTest, ClonareFunctioneazaCorect) {
    CD original("Original", "A", 2020, "P", 50.0, 10);
    auto clona = original.clone();

    // Verifica ca s-a clonat corect (dynamic_cast reusit)
    CD* clona_cd = dynamic_cast<CD*>(clona.get());
    ASSERT_NE(clona_cd, nullptr);

    // Verifica ca s-a facut Deep Copy (ID-uri diferite)
    ASSERT_NE(original.getIdProdus(), clona->getIdProdus());

    // Verifica integritatea datelor
    ASSERT_EQ(original.getTitlu(), clona->getTitlu());
}


// --- 4. TESTAREA LOGICII DE NIVEL INALT (COS CUMPARATURI) ---

TEST(CosCumparaturiTest, CalculeazaTotalCuTaxe) {
    CosCumparaturi cos;
    // CD: 50.0 + 5% = 52.50
    cos.adaugaProdus(make_unique<CD>("CD_Test", "A", 2020, "P", 50.0, 1));
    // Merchandise: 100.0 + 8.0 RON = 108.00
    cos.adaugaProdus(make_unique<Merchandise>("Merch_Test", "B", 2024, "M", 100.0, "Alb", "Plastic"));

    // Total Așteptat: 52.50 + 108.00 = 160.50
    ASSERT_NEAR(cos.calculeazaTotalCuTaxe(), 160.50, 0.001);
}

// Functia main pentru rularea testelor (necesara pentru GoogleTest)
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}