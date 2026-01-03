#ifndef ERORIMUZICALE_H
#define ERORIMUZICALE_H

#include <stdexcept>
#include <string>

/**
 * @class EroareMuzicala
 * @brief Base exception class for all musical product related errors.
 * Inherits from std::runtime_error.
 */
class EroareMuzicala : public std::runtime_error {
public:
    explicit EroareMuzicala(const std::string& msg) : std::runtime_error(msg) {}
};

/**
 * @class EroarePretInvalid
 * @brief Exception thrown when a product price is invalid (e.g., negative).
 */
class EroarePretInvalid : public EroareMuzicala {
public:
    explicit EroarePretInvalid(const std::string& msg) : EroareMuzicala(msg) {}
};

/**
 * @class EroareFormatNecunoscut
 * @brief Exception thrown when parsing an unknown product type from data sources.
 */
class EroareFormatNecunoscut : public EroareMuzicala {
public:
    explicit  EroareFormatNecunoscut(const std::string& msg) : EroareMuzicala(msg) {}
};

/**
 * @class EroareDateIncomplete
 * @brief Exception thrown when required data for an operation is missing.
 */
class EroareDateIncomplete : public EroareMuzicala {
public:
    explicit EroareDateIncomplete(const std::string& msg) : EroareMuzicala(msg) {}
};

/**
 * @class EroareLogica
 * @brief Exception thrown for logical errors in the application flow.
 * Inherits from std::logic_error.
 */
class EroareLogica : public std::logic_error {
public:
    explicit EroareLogica(const std::string& msg) : std::logic_error(msg) {}
};

#endif // ERORIMUZICALE_H