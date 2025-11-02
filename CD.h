#ifndef CD_H
#define CD_H

#include <string>
#include <ostream>

class CD {
private:
    std::string nume;
    std::string artist;
    double pret;

    static int numarTotalCDuriVandute;

public:
    CD(const std::string& n, const std::string& a, double p);
    CD(const CD& other);
    CD& operator=(const CD& other);
    ~CD() = default;

    double getPret() const;
    const std::string& getNume() const;
    const std::string& getArtist() const;

    static int getNumarTotalCDuri();
    bool operator>(const CD& other) const;

    friend std::ostream& operator<<(std::ostream& os, const CD& cd);
};

#endif