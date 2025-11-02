#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <ostream>


class Client {
private:
    std::string nume;

    std::string email;

public:
    explicit Client(const std::string& n, const std::string& e = "");

    Client(const Client& other);
    Client& operator=(const Client& other);
    ~Client() = default;

    const std::string& getNume() const;
    const std::string& getEmail() const;

    friend std::ostream& operator<<(std::ostream& os, const Client& c);
};

#endif
