#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <ostream>
#include <utility>

/**
 * @class Client
 * @brief Represents a store customer.
 * Manages customer details like name and email using RAII and Copy-and-Swap idiom.
 */
class Client {
private:
    std::string nume;
    std::string email;

public:
    /**
     * @brief Constructor for Client.
     * @param n Name of the client.
     * @param e Email of the client (optional).
     */
    explicit Client(const std::string &n, const std::string &e = "");

    ~Client() = default;

    // Copy and Swap
    Client(const Client &other);

    Client &operator=(Client other);

    /**
     * @brief Swaps the contents of two Client objects.
     * @param first First client.
     * @param second Second client.
     */
    friend void swap(Client &first, Client &second);

    const std::string &getNume() const;

    const std::string &getEmail() const;

    friend std::ostream &operator<<(std::ostream &os, const Client &c);
};

#endif
