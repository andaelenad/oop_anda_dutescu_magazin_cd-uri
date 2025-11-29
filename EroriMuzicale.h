#ifndef ERORIMUZICALE_H
#define ERORIMUZICALE_H

#include <stdexcept>
#include <string>


class EroareMuzicala : public std::runtime_error {
public:

    EroareMuzicala(const std::string& msg) : std::runtime_error(msg) {}
};

// pret negativ sau 0
class EroarePretInvalid : public EroareMuzicala {
public:
    EroarePretInvalid(const std::string& msg) : EroareMuzicala(msg) {}
};

// valori neasteptate pt rpm de ex
class EroareFormatNecunoscut : public EroareMuzicala {
public:
    EroareFormatNecunoscut(const std::string& msg) : EroareMuzicala(msg) {}
};

//date esentiale lipsa/invalide
class EroareDateIncomplete : public EroareMuzicala {
public:
    EroareDateIncomplete(const std::string& msg) : EroareMuzicala(msg) {}
};

#endif // ERORIMUZICALE_H