#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


template <typename T>
void aplicaDiscountGeneric(T& item, double procent) {
    double pretVechi = item.getPret();
    double pretNou = pretVechi * (1.0 - procent / 100.0);
    item.setPret(pretNou);
    std::cout << "[Template Discount] Pret redus cu " << procent << "% -> "
              << pretNou << " RON.\n";
}

template <typename T>
class PachetPromotional {
private:
    std::string numePachet;
    std::vector<T> elemente;

public:
    PachetPromotional(const std::string& nume) : numePachet(nume) {}

    void adaugaElement(const T& elem) {
        elemente.push_back(elem);
    }

    void afiseazaContinut() const {
        std::cout << "\n--- Pachet Promotional: " << numePachet << " ---\n";
        std::cout << "Contine " << elemente.size() << " elemente:\n";
        for (const auto& elem : elemente) {
            std::cout << " - " << elem << "\n";
        }
        std::cout << "----------------------------------\n";
    }
};

#endif // TEMPLATES_H