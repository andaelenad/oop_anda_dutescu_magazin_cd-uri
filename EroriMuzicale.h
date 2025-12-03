#ifndef ERORIMUZICALE_H
#define ERORIMUZICALE_H

#include <stdexcept>
#include <string>

class EroareMuzicala : public std::runtime_error {
public:
    explicit EroareMuzicala(const std::string& msg) : std::runtime_error(msg) {}
};

class EroarePretInvalid : public EroareMuzicala {
public:
    explicit EroarePretInvalid(const std::string& msg) : EroareMuzicala(msg) {}
};

class EroareFormatNecunoscut : public EroareMuzicala {
public:
    explicit  EroareFormatNecunoscut(const std::string& msg) : EroareMuzicala(msg) {}
};

class EroareDateIncomplete : public EroareMuzicala {
public:
    explicit EroareDateIncomplete(const std::string& msg) : EroareMuzicala(msg) {}
};

class EroareLogica : public std::logic_error {
public:
    explicit EroareLogica(const std::string& msg) : std::logic_error(msg) {}
};

#endif // ERORIMUZICALE_H