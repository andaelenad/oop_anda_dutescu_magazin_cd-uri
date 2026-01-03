
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <ostream>
#include <utility>

class Client {
private:
    std::string nume;
    std::string email;

public:
    explicit Client(const std::string& n, const std::string& e = "");
    ~Client() = default;

    // Copy and Swap
    Client(const Client& other);
    Client& operator=(Client other);
    friend void swap(Client& first, Client& second); // Functia swap necesara

    const std::string& getNume() const;
    const std::string& getEmail() const;

    friend std::ostream& operator<<(std::ostream& os, const Client& c);
};

#endif
